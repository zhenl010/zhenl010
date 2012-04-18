#ifndef EXPRESSION_TREE_H_
#define EXPRESSION_TREE_H_

#include <cassert>
#include <string>
#include <sstream>

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

// Optype has to return a DataType
// class Optype
// {
// public:
//     virtual DataType operator()(const DataType&, const DataType&) = 0;
//     friend std::ostream& operator<<(std::ostream& osm, const Optype& opf);
// };

// forward declearations:
template<class DataType, class Optype> class ExpressionTree;
template<class DataType, class Optype>
void Swap(ExpressionTree<DataType, Optype>& lhs, ExpressionTree<DataType, Optype>& rhs);
template<class DataType, class Optype>
ExpressionTree<DataType, Optype>
Merge(const ExpressionTree<DataType, Optype>&, const Optype* op_ptr, const ExpressionTree<DataType, Optype>&);

template<class DataType, class Optype>
class ExpressionTree
{
public:
    ExpressionTree() { root_ = nullptr; }
    ExpressionTree(DataType x) { root_ = CreateLeaf(x); }
    ExpressionTree(const ExpressionTree<DataType, Optype>&);
    ExpressionTree(ExpressionTree<DataType, Optype>&&);
    ExpressionTree<DataType, Optype>& operator=(ExpressionTree<DataType, Optype>);
    ~ExpressionTree() { ClearNode(root_); root_ = nullptr; }

    friend void Swap<DataType, Optype>(ExpressionTree<DataType, Optype>&, ExpressionTree<DataType, Optype>&);
    friend ExpressionTree<DataType, Optype> 
    Merge(const ExpressionTree<DataType, Optype>&, const Optype*, const ExpressionTree<DataType, Optype>&);

    ExpressionTree<DataType, Optype>& Merge(const Optype*, const ExpressionTree<DataType, Optype>&);
    bool IsEmpty() const { return root_ == nullptr; }
    DataType Calculate() { assert( IsEmpty() != true ); return Calculate(root_); }
    std::string GetString();

private:
    struct Node
    {
        Node() : left(nullptr), right(nullptr) {}
        Node* left;
        Node* right;
    };

    struct TrukNode : public Node
    {
        TrukNode(const Optype* op_ptr) : opptr(op_ptr) {}
        const Optype* opptr; // notice it saves a ptr rather than op
    };

    Node* CreateTruk(const Optype* op_ptr)
    {
        TrukNode* node = new TrukNode(op_ptr);
        return node;
    }

    struct LeafNode : public Node
    {
        LeafNode(const DataType& x) : data(x) {}
        DataType data;
    };

    Node* CreateLeaf(const DataType& x)
    {
        LeafNode* node = new LeafNode(x);
        return node;
    }

    bool IsLeaf( const Node* const node ) const { return node->left == nullptr && node->right == nullptr; }
    DataType GetData(Node* node) { return static_cast<const LeafNode*>(node)->data; }
    const Optype* GetOp(Node* node) { return static_cast<const TrukNode*>(node)->opptr; }
    DataType Calculate(Node* node);
    void ToString(Node*, std::string&);
    Node* CreateClone(const Node* const oldnode);
    void ClearNode(Node* node);

    Node* root_;
};

template<class DataType, class Optype>
ExpressionTree<DataType, Optype>::
ExpressionTree(const ExpressionTree<DataType, Optype>& rhs)
: root_(nullptr)
{
    if (rhs.IsEmpty())
    {
        return;
    }

    root_ = CreateClone(rhs.root_);
}

template<class DataType, class Optype>
ExpressionTree<DataType, Optype>::
ExpressionTree(ExpressionTree<DataType, Optype>&& rhs)
: root_(nullptr)
{
    Swap<DataType, Optype>(*this, rhs);
}

template<class DataType, class Optype>
ExpressionTree<DataType, Optype>& ExpressionTree<DataType, Optype>::
operator=(ExpressionTree<DataType, Optype> rhs)
{
    Swap<DataType, Optype>(*this, rhs);

    return *this;
}

template<class DataType, class Optype>
ExpressionTree<DataType, Optype>& ExpressionTree<DataType, Optype>::
Merge(const Optype* op_ptr, const ExpressionTree<DataType, Optype>& rhs)
{
    Node* node = CreateTruk(op_ptr);
    ExpressionTree<DataType, Optype> temp(rhs);
    std::swap(node->right, temp.root_);
    node->left = root_;
    root_ = node;

    return *this;
}

template<class DataType, class Optype>
void Swap(ExpressionTree<DataType, Optype>& lhs, ExpressionTree<DataType, Optype>& rhs)
{
    std::swap(lhs.root_, rhs.root_);
}

template<class DataType, class Optype>
ExpressionTree<DataType, Optype> 
Merge(const ExpressionTree<DataType, Optype>& lhs, const Optype* op_ptr, const ExpressionTree<DataType, Optype>& rhs)
{
    ExpressionTree<DataType, Optype> temp(lhs);
    temp.Merge(op_ptr, rhs);
    return temp;
}

template<class DataType, class Optype>
DataType ExpressionTree<DataType, Optype>::
Calculate(Node* node)
{
    if (IsLeaf(node))
    {
        return GetData(node);
    }

    const Optype* op_ptr = GetOp(node);

    ///@TODO: get rid of const_cast?
    Optype* optr = const_cast<Optype*>(op_ptr);

    return (*optr)(Calculate(node->left), Calculate(node->right));
}

template<class DataType, class Optype>
std::string ExpressionTree<DataType, Optype>::
GetString()
{
    std::string str;

    ToString(root_, str);

    return str;
}

template<class DataType, class Optype>
void ExpressionTree<DataType, Optype>::
ToString(Node* node, std::string& str)
{
    if (IsLeaf(node))
    {
        std::stringstream strstream;
        strstream << GetData(node);
        str += strstream.str();
        return;
    }

    str += '(';
    ToString(node->left, str);
    const Optype* op_ptr = GetOp(node);
    std::stringstream opstream;
    opstream << (*op_ptr);
    str += opstream.str();
    ToString(node->right, str);
    str += ')';
}

template<class DataType, class Optype>
typename ExpressionTree<DataType, Optype>::Node* ExpressionTree<DataType, Optype>::
CreateClone(const Node* oldnode)
{
    if (oldnode == nullptr)
    {
        return nullptr;
    }

    Node* newnode = nullptr;
    if (IsLeaf(oldnode))
    {
        // CloneLeaf(newnode, static_cast<const LeafNode*>(oldnode));
        newnode = CreateLeaf(static_cast<const LeafNode*>(oldnode)->data);
    } 
    else
    {
        newnode = CreateTruk(static_cast<const TrukNode*>(oldnode)->opptr);
    }

    assert(newnode != nullptr);

    newnode->left = CreateClone(oldnode->left);
    newnode->right = CreateClone(oldnode->right);

    return newnode;
}

template<class DataType, class Optype>
void ExpressionTree<DataType, Optype>::
ClearNode(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    ClearNode(node->left);
    ClearNode(node->right);
    delete node;
}

//////////////////////////////////////////////////////////////////////////
}

#endif