#ifndef PARALGO_HW3_VALIDATION_HPP
#define PARALGO_HW3_VALIDATION_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include "node.hpp"
#include "tree.hpp"

void AssertDebug(bool condition, const char* msg = nullptr);

void AssertDebug(bool condition, std::string&& msg);

class TreeValidationUtil {
  public:
    static std::pair<bool, std::vector<int>> ValidateStructureAndCollectKeys(const Tree& tree);

    static void PrettyPrint(const Tree& tree, std::ostream& os);

  private:
    static bool ValidateStructureAndCollectKeys(Node* node, std::vector<int>& keys);

    static void PrettyPrint(const Node* node, const std::string& prefix, bool is_left, std::ostream& os);

    static bool ValidateLocalInvariants(const Node* node);
};



#endif //PARALGO_HW3_VALIDATION_HPP