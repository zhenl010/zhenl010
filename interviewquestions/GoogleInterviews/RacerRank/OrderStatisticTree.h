#ifndef ORDER_STATISTIC_TREE_H__
#define ORDER_STATISTIC_TREE_H__

// Order Statistics Tree implemented as augmented left lean red black tree
template<typename T, bool (&CompareFunction)(const T&, const T&)>
class OrderStatisticTree {
public:
  // Constructor
  explicit OrderStatisticTree(): cnt_(0), root_(nullptr) {}
  // Destructor
  ~OrderStatisticTree() { Clear(); }
  // Capacity
  int Size() const { return cnt_; }
  // Modifier
  void Insert(const T& x);
  void Erase(const T& x);
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

  static RedBlack Flip(RedBlack c);
  static bool IsRed(const Node* p);
  static Node* CreateNode(const T& t);

  // pre-condition: (*p)->r_->color == RedBlack::RED
  void RotateLeft(Node** p) {
    Node* tmp = (*p)->r_;
    (*p)->r_ = tmp->l_;
    tmp->l_ = (*p);
    tmp->color = (*p)->color;
    (*p)->color = RedBlack::RED; // via precondition
    (*p) = tmp;
  }

  // pre-condition: (*q)->l_->color == RedBlack::RED
  void RotateRight(Node** q) {
    Node* tmp = (*q)->l_;
    (*q)->l_ = tmp->r_;
    tmp->r_ = (*q);
    tmp->color = (*q)->color;
    (*q)->color = RedBlack::RED;  // via precondition
    (*q) = tmp;
  }

  void ColorFlip(Node* rt);
  void FixUp(Node** rt);
  void Insert(const T& t, Node** rt);

  int cnt_;
  Node* root_;
};

#include "OrderStatisticTree.hxx"

#endif