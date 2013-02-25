#ifndef SLOWER_SOLUTION_H__
#define SLOWER_SOLUTION_H__

#include <vector>

class SlowerSolution {
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
		GetSizes(&buffer_[0]);

		// Init super root
		InitValues(&buffer_[0]);
		buffer_[0].values = std::vector<int>(M_+2, 0); // super node is special
		FindMostValues(&buffer_[0]);
		return buffer_[0].values[M_+1];
	}

private:
	struct TargetNode {
		int val;
		TargetNode* parent;
		std::vector<TargetNode*> children;
		int size;
		std::vector<int> values;
	};

	void Init() {
		static const TargetNode init_node = { 0, &buffer_[0], std::vector<TargetNode*>(), 1, std::vector<int>() };
		for (int i = 0; i <= N_; i++) {
			buffer_[i] = init_node;
		}
		buffer_[0].parent = NULL; // supper node, as root
		buffer_[0].values = std::vector<int>(M_, 0);
	}

	void GetGraph(Target targets[]) {
		for (int i = 1; i <= N_; i++) { // starts from one!
			buffer_[i].val = targets[i].val;
			buffer_[i].parent = &buffer_[targets[i].pre];
			buffer_[targets[i].pre].children.push_back(&buffer_[i]);
		}
	}

	int GetSizes(TargetNode* node) {
		for(size_t i=0; i<node->children.size(); ++i) {
			node->size += GetSizes(node->children[i]);
		}
		return node->size;
	}

	void InitValues(TargetNode* node) {
		node->values = std::vector<int>(std::min(M_, node->size)+1, 0);
		node->values[1] = node->val;
		for(size_t i=0; i<node->children.size(); ++i) {
			InitValues(node->children[i]);
		}
	}

	void FindMostValues(TargetNode* node) {
		for(size_t i=0; i<node->children.size(); ++i) {
			TargetNode* child = node->children[i];
			FindMostValues(child);
			for(size_t num=node->values.size()-1; num>1; --num) { // reverse trick to avoid wipe
				for(size_t m=1; m<num && m<child->values.size(); ++m) {
					node->values[num] = std::max(node->values[num], node->values[num-m]+child->values[m]);
				}
			}
		}
	}

	int N_;
	int M_;
	TargetNode buffer_[MAX_N];
};

#endif // !SLOWER_SOLUTION_H__
