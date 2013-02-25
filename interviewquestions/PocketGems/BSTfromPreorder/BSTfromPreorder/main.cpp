#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <cassert>

struct Node {
    Node(int x): data(x), left(NULL), right(NULL) {}
    int data;
    Node* left;
    Node* right;
};

void InsertToTree(Node** node, int x) {
    if(*node == NULL) *node = new Node(x);

    if(x < (*node)->data) {
        InsertToTree( &((*node)->left), x );
    } else if ((*node)->data < x) {
        InsertToTree( &((*node)->right), x );
    }
}

void RotateLeft(Node** node) {
    assert(*node && (*node)->right);
    Node* p = *node;
    Node* q = p->right;
    p->right = q->left;
    q->left = p;
    *node = q;
}

void RotateRight(Node** node) {
    assert(*node && (*node)->left);
    Node* q = *node;
    Node* p = q->left;
    q->left = p->right;
    p->right = q;
    *node = p;
}

void InorderTraverse(Node* node, std::ostream& stream) {
    if (node == NULL) return;

    InorderTraverse(node->left, stream);
    stream << " " << node->data;
    InorderTraverse(node->right, stream);
}

void PreorderTraverse(Node* node, std::ostream& stream) {
    if (node == NULL) return;

    stream << " " << node->data;
    PreorderTraverse(node->left, stream);
    PreorderTraverse(node->right, stream);
}

void PostorderTraverse(Node* node, std::ostream& stream) {
    if (node == NULL) return;

    PostorderTraverse(node->left, stream);
    PostorderTraverse(node->right, stream);
    stream << " " << node->data;
}

// construct binary search tree from pre-order traversal
Node* BstFromPreorder(const std::vector<int>& nums) {
    if (nums.empty()) return NULL;
    
    Node* root = new Node(nums[0]);
    std::stack<Node*> pre_nodes;
    pre_nodes.push(root);
    for (size_t i=1; i<nums.size(); ++i) {
        Node* node = new Node(nums[i]);
        Node* last = pre_nodes.top();
        if (node->data < last->data) {
            last->left = node;
        } else {
            while ( (!pre_nodes.empty()) && (pre_nodes.top()->data < node->data) ) {
                last = pre_nodes.top();
                pre_nodes.pop();
            }
            last->right = node;
        }
        pre_nodes.push(node);
    }

    return root;
}

int main(int argc, char** argv) {
    Node* root = NULL;
    int node_num = 10;
    for (int i=0; i<node_num; ++i) {
        InsertToTree(&root, rand()%10);
    }
    InsertToTree(&root, 5);
    
    PreorderTraverse(root, std::cout);
    std::cout << std::endl;
    InorderTraverse(root, std::cout);
    std::cout << std::endl;
    PostorderTraverse(root, std::cout);
    std::cout << std::endl;
    std::cout << std::endl;

    std::stringstream sstrm;
    PreorderTraverse(root, sstrm);
    std::vector<int> pre_nums;
    int val;
    while (sstrm >> val) {
        pre_nums.push_back(val);
    }
    Node* clone = BstFromPreorder(pre_nums);

    PreorderTraverse(clone, std::cout);
    std::cout << std::endl;
    InorderTraverse(clone, std::cout);
    std::cout << std::endl;
    PostorderTraverse(clone, std::cout);

    return 0;
}