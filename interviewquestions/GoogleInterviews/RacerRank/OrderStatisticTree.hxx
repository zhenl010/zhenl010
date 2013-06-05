#ifndef ORDER_STATISTIC_TREE_IMPL__
#define ORDER_STATISTIC_TREE_IMPL__

template<typename T, bool (&CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::Insert(const T& x) {
  Insert(x, &root_);
  if(root_->color==RedBlack::RED) { root_->color=RedBlack::BLACK; }
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::Erase(const T& x) {
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::Clear() {
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
int OrderStatisticTree<T, CompareFunction>::Rank(const T&) {
  return 0;
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::RedBlack
OrderStatisticTree<T, CompareFunction>::Flip(RedBlack c) {
  return c==RedBlack::BLACK ? RedBlack::RED : RedBlack::BLACK;
};

template<typename T, bool (&CompareFunction)(const T&, const T&)>
bool OrderStatisticTree<T, CompareFunction>::IsRed(const Node* p) {
  return p==nullptr ? false : p->color==RedBlack::RED;
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
OrderStatisticTree<T, CompareFunction>::CreateNode(const T& t) {
  return new Node(t); ///@TODO: use allocator?
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::ColorFlip(Node* rt) {
  rt->color = Flip(rt->color);
  rt->l_->color = Flip(rt->l_->color);
  rt->r_->color = Flip(rt->r_->color);
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::FixUp(Node** rt) {
  if (IsRed((*rt)->r_)) { RotateLeft(rt); } // fix right-leaning
  if (IsRed((*rt)->l_) && IsRed((*rt)->l_->l_)) { RotateRight(rt); } // fix red-red
  if (IsRed((*rt)->l_) && IsRed((*rt)->r_)) { ColorFlip(*rt); } // split 4-nodes
}

template<typename T, bool (&CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::Insert(const T& t, Node** rt) {
  if (*rt == nullptr) { *rt = CreateNode(t); return; }

  if (CompareFunction(t, (*rt)->val)) {
    Insert(t, &((*rt)->l_));
  } else if (CompareFunction((*rt)->val, t)) {
    Insert(t, &((*rt)->r_));
  } // equal value skipped

  FixUp(rt);
}

#endif