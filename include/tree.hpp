#ifndef CW3_TREE_HPP
#define CW3_TREE_HPP

#include "spinlock.hpp"
#include "node.hpp"

class Tree {
    using lock_t = Node::lock_t;
    friend class TreeValidationUtil;

  public:
    bool Contains(int key);

    bool Insert(int key);

    bool Erase(int key);

  private:
    // if the tree is empty, locks the global tree lock and returns a pair of nullptrs;
    // if the tree consists of a single node, returns it, retaining the node's lock and optionally the tree lock;
    // otherwise, returns the unique (locked) leaf found by traversal using given key_,
    // optionally together with its (locked) parent
    std::pair<Node*, Node*> TraverseByKeyAndLock(int key, bool with_parent = false);

    void UnlockParent(Node* parent);

    Node* root_ = nullptr;
    mutable lock_t tree_lock_;
};



#endif //CW3_TREE_HPP
