//////////////////////////////////////////////////////////////////////////
//  * From Cracking the Coding Interview, 5th edition 
//  * Problem 4.1
//  *
//  * Implement a function to check if a binary tree is balanced. For the
//  * purpose of this question, a balanced tree is defined to be a tree
//  * such that the heights of the two subtrees of any node never differ
//  * by more than one.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

typedef int DataType;

struct BinaryTreeNode
{
    DataType data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

const int INVALID_TREE_HEIGHT = -1;
const int VALID_HEIGHT_DIFFERENCE = 1;

// prototypes
int BalancedHeight(const BinaryTreeNode* node);
bool IsBalanced(const BinaryTreeNode* node);

BinaryTreeNode* NewNode(DataType x)
{
    BinaryTreeNode* new_node = new BinaryTreeNode;
    new_node->data = x;
    new_node->left = nullptr;
    new_node->right = nullptr;
    return new_node;
}

void InsertSingleNodeToLeft(BinaryTreeNode* node, BinaryTreeNode* newnode)
{
    newnode->left = node->left;
    node->left = newnode;
}

void InsertSingleNodeToRight(BinaryTreeNode* node, BinaryTreeNode* newnode)
{
    newnode->right = node->right;
    node->right = newnode;
}

static int height_cal_count = -1;
// returns tree height for balanced tree and INVALID_TREE_HEIGHT for unbalanced
int BalancedHeight(const BinaryTreeNode* node)
{
    ++height_cal_count;

    if (node == nullptr)
    {
        return 0;
    } 
    else
    {
        int leftheight = BalancedHeight(node->left);
        if (leftheight == INVALID_TREE_HEIGHT)
        {
            return INVALID_TREE_HEIGHT;
        }

        int rightheight = BalancedHeight(node->right);
        if (rightheight == INVALID_TREE_HEIGHT)
        {
            return INVALID_TREE_HEIGHT;
        }

        if (VALID_HEIGHT_DIFFERENCE < abs(leftheight-rightheight))
        {
            return INVALID_TREE_HEIGHT;
        }

        return std::max(leftheight, rightheight) + 1;
    }
}

bool IsBalanced(const BinaryTreeNode* node)
{
    return BalancedHeight(node) != INVALID_TREE_HEIGHT;
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    BinaryTreeNode* root = NewNode(0);
    BinaryTreeNode* node_001 = NewNode(1);
    InsertSingleNodeToLeft(root, node_001);
    BinaryTreeNode* node_002 = NewNode(2);
    InsertSingleNodeToRight(root, node_002);
    BinaryTreeNode* node_003 = NewNode(3);
    InsertSingleNodeToRight(node_001, node_003);
    BinaryTreeNode* node_004 = NewNode(4);
    InsertSingleNodeToLeft(node_002, node_004);

    if (IsBalanced(root))
    {
        std::cout << "Valid!" << std::endl;
    } 
    else
    {
        std::cout << "INVALID!!!!!!!!" << std::endl;
    }

    std::cout << "Height routine entered time: " << height_cal_count << std::endl;

    return 0;
}