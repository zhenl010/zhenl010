#ifndef LEFT_LEAN_RED_BLACK_TREE_H__
#define LEFT_LEAN_RED_BLACK_TREE_H__

#define RBLL_TREE_DEBUG

#ifdef RBLL_TREE_DEBUG
#include <iostream>
#include <iomanip>
#endif // RBLL_TREE_DEBUG

template<typename T>
class LeftLeanRedBlackTree {
public:
    // Constructors
    LeftLeanRedBlackTree(): root_(nullptr) {}
    LeftLeanRedBlackTree(const T& x) { root_ = new Node(x); }
    // Capacity
    bool isEmpty() const { return root_==nullptr || isRed(root_); }
    int size() const;
    // Modifier
    void insert(const T& t) {
        insert(t, &root_);
        if(root_->color==RedBlack::RED) { root_->color=RedBlack::BLACK; }
    }
    void erase(const T&);
    void clear();
    // query
    bool find(const T&);

private:
    // used C++11 enum class (size defined) and nullptr
    enum class RedBlack: bool { RED = true, BLACK = false };
    RedBlack flip(RedBlack c) { return c==RedBlack::BLACK ? RedBlack::RED : RedBlack::BLACK; };

    struct Node {
        RedBlack color;
        T x;
        Node* l_;
        Node* r_;
        Node(const T& t):color(RedBlack::RED), x(t), l_(nullptr), r_(nullptr) {}
    };

    static bool isRed(const Node* p) { return p==nullptr ? false : p->color==RedBlack::RED; }
    static Node* CreateNode(const T& t) {
        return new Node(t); ///@TODO: use allocator?
    }

    // pre-condition: (*p)->r_->color == RedBlack::RED
    void rotateLeft(Node** p) {
        Node* tmp = (*p)->r_;
        (*p)->r_ = tmp->l_;
        tmp->l_ = (*p);
        tmp->color = (*p)->color;
        (*p)->color = RedBlack::RED; // via precondition
        (*p) = tmp;
    }

    // pre-condition: (*q)->l_->color == RedBlack::RED
    void rotateRight(Node** q) {
        Node* tmp = (*q)->l_;
        (*q)->l_ = tmp->r_;
        tmp->r_ = (*q);
        tmp->color = (*q)->color;
        (*q)->color = RedBlack::RED;  // via precondition
        (*q) = tmp;
    }

    void colorFlip(Node* rt) {
        rt->color = flip(rt->color);
        rt->l_->color = flip(rt->l_->color);
        rt->r_->color = flip(rt->r_->color);
    }

    void fixUp(Node** rt) {
        if (isRed((*rt)->r_)) { rotateLeft(rt); } // fix right-leaning
        if (isRed((*rt)->l_) && isRed((*rt)->l_->l_)) { rotateRight(rt); } // fix red-red
        if (isRed((*rt)->l_) && isRed((*rt)->r_)) { colorFlip(*rt); } // split 4-nodes
    }

    void insert(const T& t, Node** rt) {
        // recursion terminates when reach the bottom
        if (*rt == nullptr) { *rt = CreateNode(t); return; }

        // recursion down
        if (t < (*rt)->x) {
            insert(t, &((*rt)->l_));
        } else if ((*rt)->x < t) {
            insert(t, &((*rt)->r_));
        } else { // equal
            ///@TODO: ?
        }

        // fix-up after insertion
        fixUp(rt);
    }

    Node* root_;

public:
#ifdef RBLL_TREE_DEBUG
    void inorderTraversal() {
        std::cout << std::endl;
        inorderTraversal(root_);
        std::cout << std::endl;
    }

    void inorderTraversal(Node* node) {
        if (node==nullptr) return;
        inorderTraversal(node->l_);
        CoutNode(node);
        inorderTraversal(node->r_);
    }

    void CoutNode(Node* node) {
        static const int width = 8;
        std::cout << " { ";
        if (isRed(node)) {
            std::cout << "  RED, ";
        } else {
            std::cout << "BLACK, ";
        }
        std::cout << std::setw(width) << node->x << ", ";
        if (node->l_==nullptr) {
            std::cout << "    NULL, ";
        } else {
            std::cout << std::setw(width) << node->l_->x << ", ";
        }
        if (node->r_==nullptr) {
            std::cout << "    NULL ";
        } else {
            std::cout << std::setw(width) << node->r_->x << " ";
        }
        std::cout << " } " << std::endl;
    }
#endif // RBLL_TREE_DEBUG
};

#endif