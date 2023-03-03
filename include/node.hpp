#ifndef CW3_NODE_HPP
#define CW3_NODE_HPP

#include "spinlock.hpp"
#include <mutex>

class Node {
  public:
    using lock_t = SpinLock;
    enum class Type { INTERNAL, LEAF };

    explicit Node(int key, Type type = Type::LEAF);

    int Key() const;

    Node* Left() const;

    Node* Right() const;

    bool IsLeaf() const;

    bool IsInternal() const;;

    void Lock() const;

    void Unlock() const;

    Node* SelectChildByKey(int key) const;

    Node* GetSibling(Node* node) const;

    void MutateToInternal(Node* left, Node* right);

    void Clone(Node* node);

    std::string GetTextDescription() const;

  private:
    int key_;
    Type type_ = Type::LEAF;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    mutable lock_t lock;
};

#endif //CW3_NODE_HPP
