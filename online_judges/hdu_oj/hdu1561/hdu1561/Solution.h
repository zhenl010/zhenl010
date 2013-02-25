#ifndef SOLUTION_H__
#define SOLUTION_H__

class Solution {
public:
	// N,M.(1 <= M <= N <= 200);
	static const int MAX_M = 201;
	static const int MAX_N = 201; // count also a super node at 0
	struct Target { int val; int pre; };

	int FindMostValue(Target targets[], int N, int M) {
		N_ = N;
		M_ = M;
		Init();
		GetGraph(targets);
		FindValues();
		return tree_[0].values[M_];
	}

private:
	struct TargetNode {
		int val;
		TargetNode* eldest;
		TargetNode* sibling;
		int maxm;
		int values[MAX_M];
	};

	void Init() {
		for (int i = 0; i <= N_; i++) {
			tree_[i].val = 0;
			tree_[i].eldest = NULL;
			tree_[i].sibling = NULL;
			tree_[i].maxm = 1;
			memset(tree_[i].values, 0, sizeof(tree_[i].values));
		}
	}

	void GetGraph(Target targets[]) {
		for (int i = 1; i <= N_; i++) { // starts from one!
			tree_[i].val = targets[i].val;
			tree_[i].sibling = tree_[targets[i].pre].eldest;
			tree_[targets[i].pre].eldest = &tree_[i];
		}
	}

	void FindValues() {
		// Init values
		FindSizes();
		for (int i = 1; i <= N_; i++) {
			tree_[i].values[0] = tree_[i].val;
		}
		FindValues(&tree_[0]);
	}

	void FindValues(TargetNode* node) {
		TargetNode* child = node->eldest;
		while (child != NULL) {
			FindValues(child);
			for (int num=node->maxm-1; num>0; --num) { // reverse trick to avoid wipe
				for (int m=0; m<num && m<node->maxm; ++m) {
					node->values[num] = std::max(node->values[num], node->values[num-m-1]+child->values[m]);
				}
			}
			child = child->sibling;
		}
	}

	void FindSizes() {
		FindSizes(&tree_[0]);
		tree_[0].maxm = M_+1; // super node
	}

	void FindSizes(TargetNode* node) {
		TargetNode* child = node->eldest;
		while (child != NULL) {
			FindSizes(child);
			node->maxm = std::min(node->maxm+child->maxm, M_);
			child = child->sibling;
		}
	}

	int N_;
	int M_;
	TargetNode tree_[MAX_N];
};

#endif