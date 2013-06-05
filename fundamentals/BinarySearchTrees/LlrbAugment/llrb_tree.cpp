#include "llrb_tree.h"

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

//////////////////////////////////////////////////////////////////////////
}

void LlrbTree::Insert(const ValueType& x) {
  root_ = Insert(x, root_);
  if (IsRed(root_)) { root_->color = RedBlack::kBlack; }
}

void LlrbTree::Remove(const ValueType& x) { // assume x exits!
  // assert(Find(x, root_) != nullptr);
  root_ = Remove(x, root_);
  if (root_!=nullptr && IsRed(root_)) { root_->color = RedBlack::kBlack; }
}

// PreCondition: node is a FOUR-NODE!!!!
LlrbTree::Node* LlrbTree::ColorFlip(Node* node) {
  node->color = Flip(node->color);
  node->l_->color = Flip(node->l_->color);
  node->r_->color = Flip(node->r_->color);
  return node;
}

LlrbTree::Node* LlrbTree::FixUp(LlrbTree::Node* node) {
  if (IsRed(node->r_)) { node=RotateLeft(node); }
  if (IsRed(node->l_) && IsRed(node->l_->l_)) { node=RotateRight(node); }
  if (IsRed(node->l_) && IsRed(node->r_)) { node=ColorFlip(node);}
  return node;
}

LlrbTree::Node* LlrbTree::MoveRedRight(Node* node) {
  node = ColorFlip(node);
  if (IsRed(node->l_->l_)) {
    node = ColorFlip(RotateRight(node));
  }
  return node;
}

LlrbTree::Node* LlrbTree::MoveRedLeft(Node* node) {
  node = ColorFlip(node);
  if (IsRed(node->r_->l_)) {
    node->r_ = RotateRight(node->r_);
    node = ColorFlip(RotateLeft(node));
  }
  return node;
}

LlrbTree::Node* LlrbTree::Insert(const ValueType& x, LlrbTree::Node* node) {
  if (node==nullptr) return NewNode(x);

  if (x < node->x) {
    node->l_ = Insert(x, node->l_);
  } else if (node->x < x) {
    node->r_ = Insert(x, node->r_);
  } else {
    // do nothing
  }

  return FixUp(node);
}

LlrbTree::Node* LlrbTree::RemoveMin(LlrbTree::Node* node) {
  if (node->l_ == nullptr) return nullptr;
  if (!IsRed(node->l_) && !IsRed(node->l_->l_)) {
    node = MoveRedLeft(node);
  }
  node->l_ = RemoveMin(node->l_);
  return FixUp(node);
}

LlrbTree::Node* LlrbTree::Remove(const ValueType& x, LlrbTree::Node* node) {
  if (x < node->x) {
    if (!IsRed(node->l_) && !IsRed(node->l_->l_)) {
      node = MoveRedLeft(node);
    }
    node->l_ = Remove(x, node->l_);
  } else  {
    if (IsRed(node->l_)) { node = RotateRight(node); }
    if (x==node->x && node->r_==nullptr) return nullptr;
    if (!IsRed(node->r_)&&!IsRed(node->r_->l_)) { node = MoveRedRight(node); }
    if (x == node->x) {
      node->x = GetMin(node->r_);
      node->r_ = RemoveMin(node->r_);
    } else {
      node->r_ = Remove(x, node->r_);
    }
  }

  return FixUp(node);
}