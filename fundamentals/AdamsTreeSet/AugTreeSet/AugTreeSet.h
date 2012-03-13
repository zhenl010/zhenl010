//////////////////////////////////////////////////////////////////////////
// Adam's tree or "Binary search trees of bounded balance"
// originally by J. Nievergelt and E. M. Reingold	
// with improvements by Adam, Milan, YOICHI HIRAI, and others
//////////////////////////////////////////////////////////////////////////
#ifndef AUG_TREE_SET_H_
#define AUG_TREE_SET_H_

#include "AugTreeNode.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template <typename KeyType>
class AugTreeSet
{
public:
    // size_type is assumed to be some integer type
    typedef int size_type;
    static const size_type WBT_OMEGA = 3;
    static const size_type WBT_ALPHA = 2;

    AugTreeSet();
    ~AugTreeSet();

    bool Insert( KeyType );
    bool Contains( KeyType ) const;
    bool GetNthItm( size_type, KeyType& ) const;
    bool Remove( KeyType );
    bool IsEmpty() const;
    size_type Size() const;
    void Clear();

private:
    // Explicitly disallow copy operations
    AugTreeSet(const AugTreeSet&);
    AugTreeSet& operator=(const AugTreeSet&);

    // helper functions
    bool IsBalanced(AugTreeNode<KeyType, size_type>*, AugTreeNode<KeyType, size_type>*) const;
    bool DoSingle(AugTreeNode<KeyType, size_type>*, AugTreeNode<KeyType, size_type>*) const;
    bool InsertTo(KeyType, AugTreeNode<KeyType, size_type>* &node);
    bool RemoveFrom(KeyType, AugTreeNode<KeyType, size_type>* &node);
    // It's caller's responsibility to make sure node is not NULL
    void RebalanceAt(AugTreeNode<KeyType, size_type>* &node);
    void LeftRotateOne(AugTreeNode<KeyType, size_type>* &node);
    void LeftRotateTwo(AugTreeNode<KeyType, size_type>* &node);
    void RightRotateOne(AugTreeNode<KeyType, size_type>* &node);
    void RightRotateTwo(AugTreeNode<KeyType, size_type>* &node);
    AugTreeNode<KeyType, size_type>* ExtractMin(AugTreeNode<KeyType, size_type>* &node)
    {
        if (node->leftChild_ == NULL)
        {
            AugTreeNode<KeyType, size_type>* minNode = node;
            node = node->rightChild_;
            return minNode;
        } 
        else
        {
            AugTreeNode<KeyType, size_type>* minNode = ExtractMin(node->leftChild_);
            --node->num_;
            RebalanceAt(node);
            return minNode;
        }
    }
    AugTreeNode<KeyType, size_type>* ExtractMax(AugTreeNode<KeyType, size_type>* &node)
    {
        if (node->rightChild_ == NULL)
        {
            AugTreeNode<KeyType, size_type>* maxNode = node;
            node = node->leftChild_;
            return maxNode;
        } 
        else
        {
            AugTreeNode<KeyType, size_type>* maxNode = ExtractMax(node->rightChild_);
            --node->num_;
            RebalanceAt(node);
            return maxNode;
        }
    }
    void ClearAll(AugTreeNode<KeyType, size_type>*);

    // root node
    AugTreeNode<KeyType, size_type>* root_;
};

template <typename KeyType>
AugTreeSet<KeyType>::AugTreeSet()
{
    root_ = NULL;
}

template <typename KeyType>
AugTreeSet<KeyType>::~AugTreeSet()
{
    // clear up
    Clear();
}

template <typename KeyType>
bool AugTreeSet<KeyType>::Insert( KeyType key )
{
    return InsertTo(key, root_);
}

template <typename KeyType>
bool AugTreeSet<KeyType>::Contains( KeyType key ) const
{
    AugTreeNode<KeyType, size_type>* node = root_;

    while(node != NULL)
    {
        if (key < node->keyData_)
        {
            node = node->leftChild_;
        }
        else if (node->keyData_ < key)
        {
            node = node->rightChild_;
        }
        else
        {
            return true;
        }
    }

    return false;
}

template <typename KeyType>
bool AugTreeSet<KeyType>::GetNthItm( size_type n, KeyType& key ) const
{
    AugTreeNode<KeyType, size_type>* node = root_;

    size_type probeNum = n;
    size_type leftNum = 0;
    while( node != NULL && probeNum < (node->num_+1) )
    {
        if (node->leftChild_ == NULL)
        {
            leftNum = 0;
        } 
        else
        {
            leftNum = node->leftChild_->num_;
        }

        if (probeNum < (leftNum + 1))
        {
            node = node->leftChild_;
        } 
        else if ( (leftNum + 1) < probeNum )
        {
            node = node->rightChild_;
            probeNum = probeNum - (leftNum + 1);
        }
        else
        {
            key = node->keyData_;
            return true;
        }
    }

    return false;
}

template <typename KeyType>
bool AugTreeSet<KeyType>::Remove( KeyType key )
{
    return RemoveFrom(key, root_);
}

template <typename KeyType>
bool AugTreeSet<KeyType>::IsEmpty() const
{
    return root_ == NULL;
}

template <typename KeyType>
typename AugTreeSet<KeyType>::size_type AugTreeSet<KeyType>::Size() const
{
    return root_->num_;
}

template <typename KeyType>
void AugTreeSet<KeyType>::Clear()
{
    ///@Todo: rewrite to non-recursive version
    ClearAll(root_);
}

template <typename KeyType>
bool AugTreeSet<KeyType>::IsBalanced( AugTreeNode<KeyType, size_type>* smallSubTree
                                    , AugTreeNode<KeyType, size_type>* largeSubTree ) const
{
    // neither subTreeX nor subTreeY is NULL
    return largeSubTree->num_ < WBT_OMEGA * smallSubTree->num_;
}

template <typename KeyType>
bool AugTreeSet<KeyType>::DoSingle( AugTreeNode<KeyType, size_type>* subTreeX
                                    , AugTreeNode<KeyType, size_type>* subTreeY ) const
{
    // neither subTreeX nor subTreeY is NULL
    return  subTreeX->num_ < WBT_ALPHA * subTreeY->num_;
}

template <typename KeyType>
bool AugTreeSet<KeyType>::InsertTo(KeyType key, AugTreeNode<KeyType, size_type>* &node)
{
    if (node == NULL)
    {
        node = new AugTreeNode<KeyType, size_type>(key);
        return true;
    } 
    else
    {
        if (key < node->keyData_ && InsertTo(key, node->leftChild_))
        {
            ++(node->num_);
            RebalanceAt(node);
            return true;
        } 
        else if (node->keyData_ < key && InsertTo(key, node->rightChild_))
        {
            ++(node->num_);
            RebalanceAt(node);
            return true;
        }
        else
        {
            // duplicate keyes!!!
            return false;
        }
    }
}

template <typename KeyType>
bool AugTreeSet<KeyType>::RemoveFrom(KeyType key, AugTreeNode<KeyType, size_type>* &node)
{
    if (node == NULL)
    {
        // nothing to do ...
        return false;
    } 
    else
    {
        if (key < node->keyData_)
        {
            if (RemoveFrom(key, node->leftChild_))
            {
                --(node->num_);
                RebalanceAt(node);
                return true;
            } 
            else
            {
                return false;
            }
        } 
        else if (node->keyData_ < key)
        {
            if (RemoveFrom(key, node->rightChild_))
            {
                --(node->num_);
                RebalanceAt(node);
                return true;
            } 
            else
            {
                return false;
            }
        }
        else
        {
            // remove the current node and fix the tree
            if (node->leftChild_ == NULL)
            {
                AugTreeNode<KeyType, size_type>* remNode = node;
                node = node->rightChild_;
                delete remNode;
            } 
            else if (node->rightChild_ == NULL)
            {
                AugTreeNode<KeyType, size_type>* remNode = node;
                node = node->leftChild_;
                delete remNode;
            }
            else
            {
                AugTreeNode<KeyType, size_type>* remNode = node;
                if (node->leftChild_->num_ < node->rightChild_->num_)
                {
                    node = ExtractMin(node->leftChild_);
                } 
                else
                {
                    node = ExtractMax(node->rightChild_);
                }
                node->leftChild_ = remNode->leftChild_;
                node->rightChild_ = remNode->rightChild_;
                node->num_ = (--remNode->num_);
                delete remNode;
                RebalanceAt(node);
            }
            return true;
        }
    }

    // should never reach here
    throw("Aug Tree deletion op failed");
}

template <typename KeyType>
void AugTreeSet<KeyType>::RebalanceAt(AugTreeNode<KeyType, size_type>* &node)
{
    // It's caller's responsibility to make sure node is not NULL
    if (node->num_ > 2)
    {
        if (node->leftChild_ == NULL)
        {
            // Left Rotation
            LeftRotateOne(node);
            return;
        }
        else if (node->rightChild_ == NULL)
        {
            // Right Rotation
            RightRotateOne(node);
            return;
        }
        else
        {
            // now both child nodes are not NULL
            if (node->leftChild_->num_ < node->rightChild_->num_)
            {
                // Left Rotations
                if (IsBalanced(node->leftChild_, node->rightChild_) == false)
                {
                    if (DoSingle(node->leftChild_, node->rightChild_))
                    {
                        LeftRotateOne(node);
                    } 
                    else
                    {
                        LeftRotateTwo(node);
                    }
                }
            } 
            else
            {
                // Right Rotations
                if (IsBalanced(node->rightChild_, node->leftChild_) == false)
                {
                    if (DoSingle(node->rightChild_, node->leftChild_))
                    {
                        RightRotateOne(node);
                    } 
                    else
                    {
                        RightRotateTwo(node);
                    }
                }
            }
        }
    }
}

template <typename KeyType>
void AugTreeSet<KeyType>::LeftRotateOne(AugTreeNode<KeyType, size_type>* &node)
{
    AugTreeNode<KeyType, size_type>* nodeN = node->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeM = node->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeX = nodeM->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeY = nodeM->rightChild_;

    node->rightChild_ = nodeX;
    nodeM->leftChild_ = node;
    node = nodeM;

    // Fix number counts
    node->leftChild_->num_ = 1 + ( (nodeN==NULL) ? 0 : nodeN->num_ )
                               + ( (nodeX==NULL) ? 0 : nodeX->num_ );
    node->num_ = 1 + node->leftChild_->num_ + ( (nodeY==NULL) ? 0 : nodeY->num_ );
}

template <typename KeyType>
void AugTreeSet<KeyType>::LeftRotateTwo(AugTreeNode<KeyType, size_type>* &node)
{
    AugTreeNode<KeyType, size_type>* nodeN = node->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeM = node->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeX = nodeM->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeY = nodeM->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeS = nodeX->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeT = nodeX->rightChild_;

    node->rightChild_ = nodeS;
    nodeM->leftChild_ = nodeT;
    nodeX->leftChild_ = node;
    nodeX->rightChild_ = nodeM;
    node = nodeX;

    // Fix number counts
    node->leftChild_->num_ = 1 + ( (nodeN==NULL) ? 0 : nodeN->num_ )
                               + ( (nodeS==NULL) ? 0 : nodeS->num_ );
    node->rightChild_->num_ = 1 + ( (nodeT==NULL) ? 0 : nodeT->num_ )
                                + ( (nodeY==NULL) ? 0 : nodeY->num_ );
    node->num_ = 1 + node->leftChild_->num_ + node->rightChild_->num_;
}

template <typename KeyType>
void AugTreeSet<KeyType>::RightRotateOne(AugTreeNode<KeyType, size_type>* &node)
{
    AugTreeNode<KeyType, size_type>* nodeN = node->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeM = node->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeX = nodeM->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeY = nodeM->leftChild_;

    node->leftChild_ = nodeX;
    nodeM->rightChild_ = node;
    node = nodeM;

    // Fix number counts
    node->rightChild_->num_ = 1 + ( (nodeN==NULL) ? 0 : nodeN->num_ )
                                + ( (nodeX==NULL) ? 0 : nodeX->num_ );
    node->num_ = 1 + node->rightChild_->num_ + ( (nodeY==NULL) ? 0 : nodeY->num_ );
}

template <typename KeyType>
void AugTreeSet<KeyType>::RightRotateTwo(AugTreeNode<KeyType, size_type>* &node)
{
    AugTreeNode<KeyType, size_type>* nodeN = node->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeM = node->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeX = nodeM->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeY = nodeM->leftChild_;
    AugTreeNode<KeyType, size_type>* nodeS = nodeX->rightChild_;
    AugTreeNode<KeyType, size_type>* nodeT = nodeX->leftChild_;

    node->leftChild_ = nodeS;
    nodeM->rightChild_ = nodeT;
    nodeX->rightChild_ = node;
    nodeX->leftChild_ = nodeM;
    node = nodeX;

    // Fix number counts
    node->leftChild_->num_ = 1 + ( (nodeT==NULL) ? 0 : nodeT->num_ )
                               + ( (nodeY==NULL) ? 0 : nodeY->num_ );
    node->rightChild_->num_ = 1 + ( (nodeN==NULL) ? 0 : nodeN->num_ )
                                + ( (nodeS==NULL) ? 0 : nodeS->num_ );
    node->num_ = 1 + node->leftChild_->num_ + node->rightChild_->num_;
}

// template <typename KeyType>
// typename AugTreeNode<KeyType, AugTreeSet<KeyType>::size_type>* AugTreeSet<KeyType>::ExtractMin(AugTreeNode<KeyType, size_type>* &node)
// {
//     if (node->leftChild_ == NULL)
//     {
//         AugTreeNode<KeyType, size_type>* minNode = node;
//         node = node->rightChild_;
//         return minNode;
//     } 
//     else
//     {
//         AugTreeNode<KeyType, size_type>* minNode = ExtractMin(node->leftChild_);
//         --node->num_;
//         RebalanceAt(node);
//         return minNode;
//     }
// }

// template <typename KeyType>
// AugTreeNode<KeyType, size_type>* AugTreeSet<KeyType>::ExtractMax(AugTreeNode<KeyType, size_type>* &node)
// {
//     if (node->rightChild_ == NULL)
//     {
//         AugTreeNode<KeyType, size_type>* maxNode = node;
//         node = node->leftChild_;
//         return maxNode;
//     } 
//     else
//     {
//         AugTreeNode<KeyType, size_type>* maxNode = ExtractMax(node->rightChild_);
//         --node->num_;
//         RebalanceAt(node);
//         return maxNode;
//     }
// }

template <typename KeyType>
void AugTreeSet<KeyType>::ClearAll(AugTreeNode<KeyType, size_type>* node)
{
    if (node == NULL)
    {
        // done
        return;
    } 
    else
    {
        ClearAll(node->leftChild_);
        ClearAll(node->rightChild_);
        delete node;
        node = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////
}

#endif