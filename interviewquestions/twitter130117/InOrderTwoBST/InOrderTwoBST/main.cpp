#include <iostream>
#include <stack>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

void InsertValue(TreeNode* &node, int x) {
    if (!node) {
        node = new TreeNode(x);
        return;
    }

    if (x < node->val) {
        InsertValue(node->left, x);
    } else if (node->val < x) {
        InsertValue(node->right, x);
    }
}

void InorderTraverse(TreeNode* r) {
    if (!r) return;
    InorderTraverse(r->left);
    std::cout << " " << r->val;
    InorderTraverse(r->right);
}

void InorderTraverseItr(TreeNode* root) {
    std::stack<TreeNode*> trace;
    TreeNode* node = root;

    while ( !trace.empty() || node ) {
        if ( !node ) {
            node = trace.top();
            std::cout << " " << node->val;
            trace.pop();
            node = node->right;
        } else {
            trace.push(node);
            node = node->left;
        }
    }
}

class TreeIterator {
public:
    TreeIterator(TreeNode*);
    TreeNode* Current();
    TreeIterator& operator++();
    TreeIterator operator++(int);

private:
    void Update();

    TreeNode* current_;
    TreeNode* node_;
    bool isUpdated_;
    std::stack<TreeNode*> trace_;
};

TreeIterator::TreeIterator(TreeNode* root)
: node_(root), isUpdated_(false) {
    Update();
}

TreeNode* TreeIterator::Current() {
    return current_;
}

TreeIterator& TreeIterator::operator++() {
    isUpdated_ = false;
    Update();
    return *this;
}

TreeIterator TreeIterator::operator++(int) {
    TreeIterator ans = *this;
    ++(*this);
    return ans;
}

void TreeIterator::Update() {
    while ( (!isUpdated_) && (!trace_.empty() || node_) ) {
        if ( !node_ ) {
            node_ = trace_.top();
            current_ = node_;
            trace_.pop();
            node_ = node_->right;
            isUpdated_ = true;
        } else {
            trace_.push(node_);
            node_ = node_->left;
        }
    }

    if ((!isUpdated_)) {
        current_ = NULL; // already go over all nodes now 
        isUpdated_ = true;    
    }
}

void PrintTwoTrees(TreeNode* tree_p, TreeNode* tree_q) {
    TreeIterator itr_p(tree_p);
    TreeIterator itr_q(tree_q);    

    while (itr_p.Current() && itr_q.Current()) {
        if (itr_p.Current()->val < itr_q.Current()->val) {
            std::cout << " " << itr_p.Current()->val;
            ++itr_p;
        } else if (itr_q.Current()->val < itr_p.Current()->val) {
            std::cout << " " << itr_q.Current()->val;
            ++itr_q;
        } else { // equal
            std::cout << " " << itr_p.Current()->val;
            ++itr_p;
            ++itr_q;
        }
    }

    while (itr_p.Current()) {
        std::cout << " " << itr_p.Current()->val;
        ++itr_p;
    }

    while (itr_q.Current()) {
        std::cout << " " << itr_q.Current()->val;
        ++itr_q;
    }
}

int main(int argc, char** argv) {
    bool keepTesting = true;

    while (keepTesting) {
        // Create a binary search tree
        TreeNode* tree_one = NULL;
        InsertValue(tree_one, rand()%10);
        InsertValue(tree_one, rand()%10);
        InsertValue(tree_one, rand()%10);
        InsertValue(tree_one, rand()%10);

        InorderTraverse(tree_one);
        std::cout << std::endl << "////////////////////////////////////////" << std::endl;

        TreeNode* tree_two = NULL;
        InsertValue(tree_two, rand()%10);
        InsertValue(tree_two, rand()%10);
        InsertValue(tree_two, rand()%10);
        InsertValue(tree_two, rand()%10);

        InorderTraverse(tree_two);
        std::cout << std::endl << "////////////////////////////////////////" << std::endl;

        PrintTwoTrees(tree_one, tree_two);
        std::cout << std::endl << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << std::endl << "----------------------------------------" << std::endl;
    }

    return 0;
}