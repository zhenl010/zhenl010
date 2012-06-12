#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class WordFinder {
public:
    WordFinder(const vector<vector<char> >& board)
    : board_(board), rownum_(board.size()), colnum_(board_.begin()->size())
    {}

    bool HasWordPath(const string& word) {
        // Init
        isvalid_.resize(rownum_);
        for(int i=0; i<rownum_; ++i) {
            isvalid_[i] = vector<bool>(board_[i].size(), true);
        }

        for(int i=0; i<rownum_; ++i) {
            for(int j=0; j<colnum_; ++j) {
                queue<BoardCell> cells;
                BoardCell cell = {i, j};
                cells.push(cell);
                if(HasWordPath(cells, word, 0)) {
                    isvalid_.clear();
                    return true;
                }
            }
        }

        isvalid_.clear();
        return false;
    }

private:
    struct BoardCell {
        int row;
        int col;
    };

private:
    bool HasWordPath(queue<BoardCell>& cells, const string& word, int idx) {
        if(idx == word.size()) return true;

        while (cells.empty() != true) {
            BoardCell cell = cells.front();
            // continue search if match
            if (IsValid(cell) && board_[cell.row][cell.col]==word[idx]) {
                isvalid_[cell.row][cell.col] = false;
                queue<BoardCell> nbors;
                AddValidNbors(nbors, cell);
                if (HasWordPath(nbors, word, idx+1) == true) { return true; }
            }
            // no match, backtrack
            cells.pop();
            isvalid_[cell.row][cell.col] = true;
        }
        return false;
    }

    bool IsValid(const BoardCell& cell) {
        return isvalid_[cell.row][cell.col];
    }

    void AddValidNbors(queue<BoardCell>& nbors, const BoardCell& cell) {
        BoardCell nbor_left = { cell.row, cell.col-1 };
        if (nbor_left.col>=0 && IsValid(nbor_left)) { nbors.push(nbor_left); }
        BoardCell nbor_right = { cell.row, cell.col+1 };
        if (nbor_right.col<colnum_ && IsValid(nbor_right)) { nbors.push(nbor_right); }
        BoardCell nbor_down = { cell.row-1, cell.col };
        if (nbor_down.row>=0 && IsValid(nbor_down)) { nbors.push(nbor_down); }
        BoardCell nbor_up = { cell.row+1, cell.col };
        if (nbor_up.row<rownum_ && IsValid(nbor_up)) { nbors.push(nbor_up); }
    }

    const vector<vector<char> >& board_;
    const int rownum_;
    const int colnum_;
    vector<vector<bool> > isvalid_;
};

class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        WordFinder finder(board);
        return finder.HasWordPath(word);
    }
};

int main(int argc, char** argv) {
    Solution solver;

    char* lines[] = {
        "ab",
        "cd"
    };
    vector<vector<char> > board(sizeof(lines)/sizeof(char*));
    for (size_t i=0; i<board.size(); ++i) {
        board[i] = vector<char>(lines[i], lines[i]+strlen(lines[i]));
    }
    string word = "acdb";

    bool doexist = solver.exist(board, word);

    return 0;
}