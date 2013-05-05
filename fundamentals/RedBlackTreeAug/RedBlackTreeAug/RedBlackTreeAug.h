#ifndef RED_BLACK_TREE_AUG_H__
#define RED_BLACK_TREE_AUG_H__

template<typename T>
class RedBlackTree {
public:
    // Constructors
    RedBlackTree(): root_(nullptr) {}
    RedBlackTree(const T& x) { root_ = new Node(x); }
    // Capacity
    bool isEmpty() const { return root_==nullptr || isRed(root_); }
    int size() const;
    // Modifier
    void insert(const T&);
    void erase(const T&);
    void clear();
    // query
    bool find(const T&);

private:
    // used C++11 enum class (size defined) and nullptr
    enum class RedBlack: bool { RED = true, BLACK = false };
    struct Node {
        RedBlack color;
        T x;
        Node* left;
        Node* right;
        Node(const T& y):color(RedBlack::RED), x(y), left(nullptr), right(nullptr) {}
    };

    static bool isRed(const Node* p) { return p==nullptr ? true : p->color==RedBlack::RED; }

    Node* root_;
};

#endif