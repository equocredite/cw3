#include <iostream>

#include "validation.hpp"
#include "config.hpp"

void AssertDebug(bool condition, const char* msg) {
    if constexpr (config::DEBUG) {
        if (!condition) {
            if (msg != nullptr) {
                std::cerr << msg << std::endl;
            }
            //quick_exit(1);
        }
    }
}

void AssertDebug(bool condition, std::string&& msg) {
    AssertDebug(condition, msg.c_str());
}

std::pair<bool, std::vector<int>> TreeValidationUtil::ValidateStructureAndCollectKeys(const Tree& tree) {
    std::vector<int> keys;
    bool result = ValidateStructureAndCollectKeys(tree.root_, keys);
    return {result, keys};
}

bool TreeValidationUtil::ValidateStructureAndCollectKeys(Node* node, std::vector<int>& keys) {
    if (node == nullptr) {
        return true;
    }
    bool result = ValidateLocalInvariants(node);
    if (node->IsInternal()) {
        result &= ValidateStructureAndCollectKeys(node->Left(), keys);
        result &= ValidateStructureAndCollectKeys(node->Right(), keys);
    } else {
        keys.push_back(node->Key());
    }
    return result;
}

bool TreeValidationUtil::ValidateLocalInvariants(const Node* node) {
    bool has_left = (node->Left() != nullptr);
    bool has_right = (node->Right() != nullptr);
    if (node->IsInternal()) {
        AssertDebug(has_left,node->GetTextDescription() + " has a null left child.");
        AssertDebug(has_right, node->GetTextDescription() + " has a null right child.");
        return node->Left()->Key() < node->Key() && node->Key() <= node->Right()->Key();
    }
    AssertDebug(!has_left,
                node->GetTextDescription() + " has a non-null left child " + node->Left()->GetTextDescription());
    AssertDebug(!has_right,
                node->GetTextDescription() + " has a non-null left child " + node->Right()->GetTextDescription());
    return true;
}


void TreeValidationUtil::PrettyPrint(const Node* node, const std::string& prefix = "", bool is_left = false,
                                     std::ostream& os = std::cout) {
    if (node == nullptr) {
        return;
    }
    os << prefix;
    os << (is_left ? "|--" : "L--");
    os << node->Key() << std::endl;
    PrettyPrint(node->Right(), prefix + (is_left ? "|   " : "    "), true, os);
    PrettyPrint(node->Left(), prefix + (is_left ? "|   " : "    "), false, os);
}

void TreeValidationUtil::PrettyPrint(const Tree& tree, std::ostream& os = std::cout) {
    PrettyPrint(tree.root_);
}
