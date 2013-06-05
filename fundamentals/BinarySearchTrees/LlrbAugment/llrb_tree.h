#ifndef LEFT_LEAN_RED_BLACK_TREE_H__
#define LEFT_LEAN_RED_BLACK_TREE_H__

//////////////////////////////////////////////////////////////////////////
// All prototype implementations are intentionally kept sample and compact
// potentially used in very time limited coding competition or interviews
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>

#define RBLL_TREE_DEBUG

typedef int ValueType;
const ValueType kDefaultValue = 0;

class LlrbTree {
public:
  LlrbTree(): root_(nullptr) {}
  void Insert(const ValueType& x);
  void Remove(const ValueType& x); // assume x exits!

private:
  enum class RedBlack: bool { kRed = true, kBlack = false };
  struct Node {
    ValueType x;
    RedBlack color;
    // augment data goes here:

    Node* l_; Node* r_;
    Node(const ValueType& x=kDefaultValue)
      : x(x), color(RedBlack::kRed), l_(nullptr), r_(nullptr) {}
  };

  static RedBlack Flip(const RedBlack& c);
  static Node* NewNode(const ValueType& x);
  static bool IsRed(const Node *p);
  static ValueType GetMin(Node* node);

  // PreCondition: node->r_ is RED!
  static Node* RotateLeft(Node* node) {
    Node* tmp = node->r_;
    node->r_ = tmp->l_;
    tmp->l_ = node;
    tmp->color = node->color;
    node->color = RedBlack::kRed;
    return tmp;
  }

  // PreCondition: node->l_ is RED!
  static Node* RotateRight(Node* node) {
    Node* tmp = node->l_;
    node->l_ = tmp->r_;
    tmp->r_ = node;
    tmp->color = node->color;
    node->color = RedBlack::kRed;
    return tmp;
  }

  static Node* ColorFlip(Node* node);
  static Node* FixUp(Node* node);
  static Node* MoveRedRight(Node* node);
  static Node* MoveRedLeft(Node* node);
  static Node* Insert(const ValueType& x, Node* node);
  static Node* RemoveMin(Node* node);
  static Node* Remove(const ValueType& x, Node* node);

  Node* root_;
#ifdef RBLL_TREE_DEBUG
public:
  void InorderTraversal() {
    std::cout << std::endl;
    InorderTraversal(root_);
    std::cout << std::endl;
  }

  void InorderTraversal(Node* node) {
    if (node==nullptr) return;
    InorderTraversal(node->l_);
    CoutNode(node);
    InorderTraversal(node->r_);
  }

  void CoutNode(Node* node) {
    static const int width = 8;
    std::cout << " { ";
    if (IsRed(node)) {
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

#include "llrb_tree.hpp"

#endif