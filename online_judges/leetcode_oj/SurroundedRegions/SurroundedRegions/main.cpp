#include <iostream>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

template<typename T, int N>
int ArraySize(T (&) [N]) { return N; }

class Solution {
public:
    void solve(vector<vector<char>> &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(board.empty()) return;

        dset_.resize(board.size());
        for (size_t i=0; i<dset_.size(); ++i) { dset_[i].resize(board[i].size()); }
        // Outside board cells with 'O' initiated as <M, N>
        Cell outer = { &outer, 0 };
        for (size_t i=0; i<dset_.size(); ++i) {
            for (size_t j=0; j<dset_.size(); ++j) {
                dset_[i][j].rank = 0;
                if (i==0 || j==0 || (i+1)==dset_.size() || (j+1)==dset_[0].size()) {
                    dset_[i][j].parent = &outer;
                } else {
                    dset_[i][j].parent = &dset_[i][j];
                }

                if (0<i && 0<j && board[i][j]=='O') { // look for 'O' connections
                    if (board[i-1][j]=='O') Union(&dset_[i][j], &dset_[i-1][j]);
                    if (board[i][j-1]=='O') Union(&dset_[i][j], &dset_[i][j-1]);
                }
            }
        }

        for (size_t i=1; i+1<dset_.size(); ++i) {
            for (size_t j=1; j+1<dset_.size(); ++j) {
                if (board[i][j]=='O' && Find(&dset_[i][j])!=Find(&outer)) {
                    board[i][j] = 'X';
                }
            }
        }
    }

private:
    struct Cell { Cell* parent; int rank; };

    Cell* Find(Cell* cell) {
        Cell* parent = cell->parent;
        if (parent!=cell) {
            parent = Find(cell->parent);
            cell->parent = parent;
        }
        return parent;
    }

    void Union(Cell* x, Cell* y) {
        Cell* xr = Find(x);
        Cell* yr = Find(y);
        if (xr->rank < yr->rank) {
            xr->parent = yr->parent;
        } else if (yr->rank < xr->rank) {
            yr->parent = xr->parent;
        } else {
            yr->parent = xr->parent;
            ++(yr->rank);
        }
    }

    vector<vector<Cell>> dset_;
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    string strs[] = { "OOO","OOO","OOO" };
    vector<vector<char>> board(ArraySize(strs));
    for (size_t i=0; i<board.size(); ++i) {
        board[i].assign(strs[i].begin(), strs[i].end());
    }

    Solution solver;
    solver.solve(board);

    return 0;
}