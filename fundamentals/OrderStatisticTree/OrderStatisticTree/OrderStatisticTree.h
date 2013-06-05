#ifndef ORDER_STATISTIC_TREE_H__
#define ORDER_STATISTIC_TREE_H__

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

  // helper functions
  static Node* RotateLeft(Node* p);
  static Node* RotateRight(Node* q);
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

#include "OrderStatisticTree.hxx"

#endif