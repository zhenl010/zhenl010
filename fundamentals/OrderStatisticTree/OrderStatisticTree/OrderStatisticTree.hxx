#ifndef ORDER_STATISTIC_TREE_IMPL__
#define ORDER_STATISTIC_TREE_IMPL__

template<typename T, bool (*CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::Insert(const T& x) {
  root_ = Insert(x, root_);
  if(IsRed(root_)) { root_->color=RedBlack::BLACK; }
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::Delete(const T& x) {
  root_ = Delete(x, root_);
  if(IsRed(root_)) { root_->color=RedBlack::BLACK; }
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::Clear() {
  root_ = Clear(root_);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
int OrderStatisticTree<T, CompareFunction>::Rank(const T& x) {
  return Rank(x, root_);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
T OrderStatisticTree<T, CompareFunction>::Select(int k) {
  return Select(k, root_);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::RedBlack
  OrderStatisticTree<T, CompareFunction>::Flip(RedBlack c) {
    return c==RedBlack::BLACK ? RedBlack::RED : RedBlack::BLACK;
};

template<typename T, bool (*CompareFunction)(const T&, const T&)>
bool OrderStatisticTree<T, CompareFunction>::IsRed(const Node* p) {
  return p==nullptr ? false : p->color==RedBlack::RED;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
int OrderStatisticTree<T, CompareFunction>::Size(const Node* p) {
  return p==nullptr ? 0 : p->n;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
const T& OrderStatisticTree<T, CompareFunction>::GetMin(const Node* p) {
  while (p->l_ != nullptr) { p = p->l_; }
  return p->val;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
void OrderStatisticTree<T, CompareFunction>::ColorFlip(Node* rt) {
  rt->color = Flip(rt->color);
  rt->l_->color = Flip(rt->l_->color);
  rt->r_->color = Flip(rt->r_->color);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
  OrderStatisticTree<T, CompareFunction>::FixUp(Node* rt) {
    if (IsRed(rt->r_)) { rt = RotateLeft(rt); } // fix right-leaning
    if (IsRed(rt->l_) && IsRed(rt->l_->l_)) { rt = RotateRight(rt); } // fix red-red
    if (IsRed(rt->l_) && IsRed(rt->r_)) { ColorFlip(rt); } // split 4-nodes
    return rt;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
  OrderStatisticTree<T, CompareFunction>::MoveRedLeft(Node* rt) {
    ColorFlip(rt);
    if (IsRed(rt->r_->l_)) {
      rt->r_ = RotateRight(rt->r_);
      rt = RotateLeft(rt);
      ColorFlip(rt);
    }
    return rt;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
  OrderStatisticTree<T, CompareFunction>::MoveRedRight(Node* rt) {
    ColorFlip(rt);
    if (IsRed(rt->l_->l_)) {
      rt = RotateRight(rt);
      ColorFlip(rt);
    }
    return rt;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
  OrderStatisticTree<T, CompareFunction>::DeleteMin(Node* rt) {
    if (rt->l_ == nullptr) return DeleteNode(rt);

    --(rt->n);
    if (!IsRed(rt->l_) && !IsRed(rt->l_->l_)) {
      rt = MoveRedLeft(rt);
    }
    rt->l_ = DeleteMin(rt->l_);
    return FixUp(rt);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
  OrderStatisticTree<T, CompareFunction>::Insert(const T& x, Node* rt) {
    if (rt == nullptr) return CreateNode(x);

    if (CompareFunction(x, rt->val)) {
      rt->l_ = Insert(x, (rt->l_));
      ++(rt->n);
    } else if (CompareFunction(rt->val, x)) {
      rt->r_ = Insert(x, (rt->r_));
      ++(rt->n);
    } // equal value skipped

    return FixUp(rt);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
  OrderStatisticTree<T, CompareFunction>::Delete(const T& x, Node* rt) {
    --(rt->n);
    if (CompareFunction(x, rt->val)) {
      if (!IsRed(rt->l_) && !IsRed(rt->l_->l_)) {
        rt = MoveRedLeft(rt);
      }
      rt->l_ = Delete(x, rt->l_);
    } else  {
      if (IsRed(rt->l_)) { rt = RotateRight(rt); }
      if (rt->r_==nullptr &&
        !CompareFunction(x, rt->val) && !CompareFunction(rt->val, x)) {
          return DeleteNode(rt);
      }
      if (!IsRed(rt->r_) && !IsRed(rt->r_->l_)) {
        rt = MoveRedRight(rt);
      }
      if (!CompareFunction(x, rt->val) && !CompareFunction(rt->val, x)) {
        rt->val = GetMin(rt->r_);
        rt->r_ = DeleteMin(rt->r_);
      } else {
        rt->r_ = Delete(x, rt->r_);
      }
    }
    return FixUp(rt);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
bool OrderStatisticTree<T, CompareFunction>::Exist(const T& x, Node* rt) {
  if (rt == nullptr) return false;
  if (CompareFunction(x, rt->val)) {
    return Exist(x, rt->l_);
  } else if (CompareFunction(rt->val, x)) {
    return Exist(x, rt->r_);
  }
  return true;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
int OrderStatisticTree<T, CompareFunction>::Rank(const T& x, Node* rt) {
  if (rt == nullptr) return 0;
  if (CompareFunction(x, rt->val)) {
    return Rank(x, rt->l_);
  } else if (CompareFunction(rt->val, x)) {
    return Size(rt->l_) + 1 + Rank(x, rt->r_);
  }
  return Size(rt)-Size(rt->r_);
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
T OrderStatisticTree<T, CompareFunction>::Select(int k, Node* rt) {
  if (k <= Size(rt->l_)) {
    return Select(k, rt->l_);
  } else if ((Size(rt->l_)+1) < k) {
    return Select(k-(Size(rt->l_)+1), rt->r_);
  }
  return rt->val;
}

template<typename T, bool (*CompareFunction)(const T&, const T&)>
typename OrderStatisticTree<T, CompareFunction>::Node*
  OrderStatisticTree<T, CompareFunction>::Clear(Node* rt) {
    if (rt==nullptr) return nullptr;
    rt->l_ = Clear(rt->l_);
    rt->r_ = Clear(rt->r_);
    return DeleteNode(rt);
}

#endif