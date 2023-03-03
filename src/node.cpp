#include "validation.hpp"
#include "node.hpp"

Node::Node(int key, Node::Type type) : key_(key), type_(type) {}

int Node::Key() const { return key_; }

Node* Node::Left() const { return left_; }

Node* Node::Right() const { return right_; }

bool Node::IsLeaf() const { return type_ == Type::LEAF; }

bool Node::IsInternal() const { return type_ == Type::INTERNAL; }

void Node::Lock() const { lock.Lock(); }

void Node::Unlock() const { lock.Unlock(); }

Node* Node::SelectChildByKey(int key) const {
    return (key < key_) ? left_ : right_;
}

Node* Node::GetSibling(Node* node) const {
    return (node == left_ ? right_ : left_);
}

std::string Node::GetTextDescription() const {
    return (IsInternal() ? "[Internal node " : "Leaf ") + std::to_string(key_) + "]";
}

void Node::MutateToInternal(Node* left, Node* right) {
    AssertDebug(left != nullptr && right != nullptr, "Node::MutateToInternal: received nullptr.");
    type_ = Type::INTERNAL;
    left_ = left;
    right_ = right;
}

void Node::Clone(Node* node) {
    AssertDebug(node != nullptr, "Node::CopyKeyAndChildren: received nullptr.");
    type_ = node->type_;
    key_ = node->key_;
    left_ = node->left_;
    right_ = node->right_;
}

