#ifndef BINARY_TREE_NODE_H_
#define BINARY_TREE_NODE_H_

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template<typename T>
struct BinaryTreeNode {
    BinaryTreeNode();
    BinaryTreeNode(const T&);

    bool IsLeaf();

    T val_;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;
};

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode()
: left(NULL), right(NULL) {
}

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& val)
: val_(val), left(NULL), right(NULL) {
}

template<typename T>
bool BinaryTreeNode<T>::IsLeaf() {
    return (left==NULL && right==NULL);
}

//////////////////////////////////////////////////////////////////////////
}

#endif