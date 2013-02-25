#include <iostream>
#include <vector>

using namespace std;

template<typename T, int N>
int ArraySize(T (&) [N]) { return N; }

class Solution {
public:
	struct Cell { Cell* parent; int rank; };
	void solve(vector<vector<char>> &board) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (board.empty() || board[0].empty()) return;

		Cell outer_o = { &outer_o, 0 };
		Cell outer_x = { &outer_x, 0 };
		vector<vector<Cell>> mat(board.size(), vector<Cell>(board[0].size()));
		for (size_t i=0; i<mat.size(); ++i) {
			for (size_t j=0; j<mat[i].size(); ++j) {
				mat[i][j].parent = &mat[i][j];
				mat[i][j].rank = 0;
				if (i==0 || j==0 || (i+1)==mat.size() || (j+1)==mat[i].size()) { // edge cell
					if (board[i][j]=='O') {
						UnionSets(&mat[i][j], &outer_o);
					}
				}
			}
		}

		for (size_t i=1; i<mat.size(); ++i) {
			for (size_t j=1; j<mat[i].size(); ++j) {
				if(board[i][j] == 'O') {
					if (board[i][j] == board[i-1][j]) UnionSets(&mat[i][j], &mat[i-1][j]);
					if (board[i][j] == board[i][j-1]) UnionSets(&mat[i][j], &mat[i][j-1]);
				}
			}
		}

		for (size_t i=1; i<mat.size(); ++i) {
			for (size_t j=1; j<mat[i].size(); ++j) {
				if (board[i][j]=='O' && FindSet(&mat[i][j])!=FindSet(&outer_o))	{
					board[i][j] = 'X';
				}
			}
		}
	}

private:
	Cell* FindSet(Cell* cell) {
		if (cell->parent != cell) {
			cell->parent = FindSet(cell->parent);
		}
		return cell->parent;
	}

	void UnionSets(Cell* ca, Cell* cb) {
		Cell* ra = FindSet(ca);
		Cell* rb = FindSet(cb);
		if(ra==rb) return;

		if (ra->rank < rb->rank) {
			ra->parent = rb;
		} else if (rb->rank < ra->rank)	{
			rb->parent = ra;
		} else {
			rb->parent = ra;
			++ra->rank;
		}
	}
};

int main() {
	Solution solver;

	string strs[] = { "OO","OO" };
	vector<vector<char>> board(ArraySize(strs));
	for (size_t i=0; i<board.size(); ++i) {
		board[i].assign(strs[i].begin(), strs[i].end());
	}
	solver.solve(board);

	return 0;
}