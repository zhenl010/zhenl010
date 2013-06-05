#include <cstdio>
#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

template<typename T>
bool Less(const T& a, const T& b) {
  return a < b;
}

// Order Statistics Tree implemented as augmented left lean red black tree
template<typename T, bool (*CompareFunction)(const T&, const T&) = &Less<T> >
class OrderStatisticTree {
public:
  // Constructor
  explicit OrderStatisticTree(): cnt_(0), root_(nullptr) {}
  // Destructor
  ~OrderStatisticTree() { Clear(); }
  // Capacity
  int Size() const { return Size(root_); }
  // Modifier
  void Insert(const T& x);
  void Delete(const T& x);
  void Clear();
  // Query
  bool Exist(const T& x);
  // Order statistic operations
  int Rank(const T& x); // starts from 1, return -1 if non-exist
  T Select(int k); // find the kth smallest element

private:
  enum class RedBlack: bool { RED = true, BLACK = false };
  struct Node {
    RedBlack color; T val; int n;
    Node* l_; Node* r_;
    Node(const T& t)
      : color(RedBlack::RED), val(t), n(1), l_(nullptr), r_(nullptr) {}
  };

  static Node* CreateNode(const T& x) {
    return new Node(x);
  }

  static Node* DeleteNode(Node* p) {
    delete p;
    return nullptr;
  }

  // pre-condition: p->r_->color == RedBlack::RED
  static Node* RotateLeft(Node* p) {
    Node* tmp = p->r_;
    p->r_ = tmp->l_;
    tmp->l_ = p;
    tmp->color = p->color;
    tmp->n = p->n;
    p->color = RedBlack::RED; // via precondition
    p->n = Size(p->l_) + 1 + Size(p->r_);
    return tmp;
  }

  // pre-condition: q->l_->color == RedBlack::RED
  static Node* RotateRight(Node* q) {
    Node* tmp = q->l_;
    q->l_ = tmp->r_;
    tmp->r_ = q;
    tmp->color = q->color;
    tmp->n = q->n;
    q->color = RedBlack::RED;  // via precondition
    q->n = Size(q->l_) + 1 + Size(q->r_);
    return tmp;
  }

  // helper functions
  static RedBlack Flip(RedBlack c);
  static bool IsRed(const Node* p);
  static int Size(const Node* p);
  static const T& GetMin(const Node* p);
  static void ColorFlip(Node* rt);
  static Node* FixUp(Node* rt);
  static Node* MoveRedLeft(Node* rt);
  static Node* MoveRedRight(Node* rt);
  static Node* DeleteMin(Node* rt);

  // Implementation via root pointer
  static Node* Insert(const T& x, Node* rt);
  static Node* Delete(const T& x, Node* rt);
  static bool Exist(const T& x, Node* rt);
  static int Rank(const T& x, Node* rt);
  static T Select(int k, Node* rt);
  static Node* Clear(Node* rt);

  int cnt_;
  Node* root_;
};

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

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int n, k;
  cin >> n >> k;

  // while (true) {
//     n = rand() % 10 + 10;
//     k = rand() % 5 + 5;

    OrderStatisticTree<int> ostree;
    for (int i=1; i<=n; ++i) {
      ostree.Insert(i);
    }

    int rank = 0;
    while (0 < ostree.Size()) {
      rank = (--rank + k) % ostree.Size() + 1;
      int id = ostree.Select(rank--);
      printf("%d ", id);
      ostree.Delete(id);
    }
    printf("\n");
  // }

  return 0;
}