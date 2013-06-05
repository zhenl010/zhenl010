inline LlrbTree::RedBlack LlrbTree::Flip(const RedBlack& c) {
  return c==RedBlack::kBlack ? RedBlack::kRed : RedBlack::kBlack;
};

inline LlrbTree::Node* LlrbTree::NewNode(const ValueType& x) {
  return new Node(x);
}

inline bool LlrbTree::IsRed(const LlrbTree::Node *p) {
  return p==nullptr ? false : p->color==RedBlack::kRed;
}

inline ValueType LlrbTree::GetMin(Node* node) {
  while (node->l_ != nullptr) { node=node->l_; }
  return node->x;
}