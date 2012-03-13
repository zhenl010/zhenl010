#ifndef AUG_TREE_NODE_H_
#define AUG_TREE_NODE_H_

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

// Assuming size_type is some integer type!!!
template <typename KeyType, typename size_type>
class AugTreeNode
{
public:
    AugTreeNode(KeyType);
    ~AugTreeNode();

    KeyType keyData_;
    int num_;

    AugTreeNode<KeyType, size_type>* leftChild_;
    AugTreeNode<KeyType, size_type>* rightChild_;

private:
    // explicitly disables
    AugTreeNode();
    AugTreeNode(const AugTreeNode&);
    AugTreeNode& operator=(const AugTreeNode&);
};

template <typename KeyType, typename size_type>
AugTreeNode<KeyType, size_type>::AugTreeNode(KeyType key)
    : keyData_(key), leftChild_(NULL), rightChild_(NULL), num_(1)
{
}

template <typename KeyType, typename size_type>
AugTreeNode<KeyType, size_type>::~AugTreeNode()
{
}

//////////////////////////////////////////////////////////////////////////
}

#endif