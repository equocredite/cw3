#include <iostream>

#include "tree.hpp"

bool Tree::Contains(int key) {
    auto [leaf, _] = TraverseByKeyAndLock(key);
    if (leaf == nullptr) {
        return false;
    }
    bool result = (key == leaf->Key());
    leaf->Unlock();
    return result;
}

bool Tree::Insert(int key) {
    auto [leaf, _] = TraverseByKeyAndLock(key);
    if (leaf == nullptr) {
        root_ = new Node{key};
        tree_lock_.Unlock();
        return true;
    }
    if (key == leaf->Key()) {
        leaf->Unlock();
        return false;
    }
    Node* left = new Node{key};
    Node* right = new Node{leaf->Key()};
    if (key > leaf->Key()) {
        std::swap(left, right);
    }
    leaf->MutateToInternal(left, right);
    leaf->Unlock();
    return true;
}

bool Tree::Erase(int key) {
    auto [leaf, parent] = TraverseByKeyAndLock(key, true);
    if (leaf == nullptr) {
        tree_lock_.Unlock();
        return false;
    }
    if (key != leaf->Key()) {
        leaf->Unlock();
        UnlockParent(parent);
        return false;
    }
    if (parent == nullptr) {
        root_ = nullptr;
        leaf->Unlock();
        delete leaf;
        tree_lock_.Unlock();
    } else {
        Node* sibling = parent->GetSibling(leaf);
        sibling->Lock();
        parent->Clone(sibling);
        sibling->Unlock();
        delete sibling;
        leaf->Unlock();
        delete leaf;
        UnlockParent(parent);
    }
    return true;
}

std::pair<Node*, Node*> Tree::TraverseByKeyAndLock(int key, bool with_parent) {
    tree_lock_.Lock();
    if (root_ == nullptr) {
        return {nullptr, nullptr};
    }
    root_->Lock();
    Node* node = root_;
    Node* parent = nullptr;
    while (true) {
        if (node->IsLeaf()) {
            if (!with_parent) {
                UnlockParent(parent);
            }
            return {node, with_parent ? parent : nullptr};
        }
        UnlockParent(parent);
        parent = node;
        node = node->SelectChildByKey(key);
        node->Lock();
    }
}

void Tree::UnlockParent(Node* parent) {
    if (parent == nullptr) {
        tree_lock_.Unlock();
        return;
    }
    parent->Unlock();
}

