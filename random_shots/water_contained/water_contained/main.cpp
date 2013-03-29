#include <iostream>
#include <vector>

using namespace std;

template<typename T, int N>
int ArraySize(T (&) [N]) { return N; }

const int ROW_NUM = 100;
const int COL_NUM = 100;

class Solution {
public:
    struct Cell { Cell* parent; int rank; };

    // find the volume of total water trapped
    int solve(int board[], int row_num, int col_num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (board[ GetId(1,1,col_num) ] == 0) return;


    }

private:
    int GetId(int i, int j, int ld) { return i*ld+j; }

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

// string strs[] = { "OO","OO" };
// vector<vector<char>> board(ArraySize(strs));
// for (size_t i=0; i<board.size(); ++i) {
//     board[i].assign(strs[i].begin(), strs[i].end());
// }
// solver.solve(board);

    return 0;
}