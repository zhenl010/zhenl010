//////////////////////////////////////////////////////////////////////////
// A very specific sudoku solver that only works for standard (9x9) sudoku
//////////////////////////////////////////////////////////////////////////
#ifndef SUDOKU_SOLVER_H_
#define SUDOKU_SOLVER_H_
#include <iostream>
#include <vector>
#include "active_maker.h"

namespace augment_puzzle_helpers
{
////////////////////////////////////////////////////////////////

static const char NUMERIC_CHAR_NUM = 9;
static const char STARTING_CHAR = '1';

// utility class that works specifically for "123456789"
class NumCharMarker {
public:
    NumCharMarker() : activenum_(NUMERIC_CHAR_NUM) {
        for (char i=0; i<NUMERIC_CHAR_NUM; ++i) {
            charids_[i] = i;
            numchars_[i] = STARTING_CHAR+i;
        }
    }

    bool IsActive(char x);
    void MarkAll();
    void Mark(char x);
    void UnMark(char x);
    void UnMarkAll();
    char ActiveNum();
    char Next();
    char NextViaIndex(char idx);

private:
    char GetRank(char x);
    char GetId(char x);

    // inter reference char array
    char charids_[NUMERIC_CHAR_NUM];
    char numchars_[NUMERIC_CHAR_NUM];
    char activenum_;
};

inline bool NumCharMarker::IsActive(char x) {
    return GetId(x) < activenum_;
}
inline void NumCharMarker::MarkAll() { activenum_ = 0; }

inline void NumCharMarker::Mark(char x) {
    char lastchar = numchars_[--activenum_];
    std::swap(numchars_[GetId(x)], numchars_[activenum_]);
    std::swap(charids_[GetRank(x)], charids_[GetRank(lastchar)]);
    return;
}

inline void NumCharMarker::UnMark(char x) {
    char lastchar = numchars_[activenum_];
    std::swap(numchars_[GetId(x)], numchars_[activenum_]);
    std::swap(charids_[GetRank(x)], charids_[GetRank(lastchar)]);
    ++activenum_;
    return;
}

inline void NumCharMarker::UnMarkAll() { activenum_ = NUMERIC_CHAR_NUM; }
inline char NumCharMarker::ActiveNum() { return activenum_; }
inline char NumCharMarker::Next() { return numchars_[0]; }
inline char NumCharMarker::NextViaIndex(char idx) { return numchars_[idx]; }

inline char NumCharMarker::GetRank(char x) { return x-STARTING_CHAR; }
inline char NumCharMarker::GetId(char x) { return charids_[GetRank(x)]; }

static const int SQUARE_SIZE = 3;
static const int GRID_SIZE = SQUARE_SIZE*SQUARE_SIZE;
static const char EMPTY_CELL_CHAR = '\0';

enum SUDOKU_BLOCK_NUMS {
    BOX = 0,
    ROW = 1,
    COL = 2,
    NBOR_BLOCK_NUM = 3
};

struct Piece;
struct Block {
    typedef ActiveMarker<Piece*, GRID_SIZE>::iterator BlockIterator;
    ActiveMarker<Piece*, GRID_SIZE> pieces_;
    NumCharMarker charmaker_;
};
struct Piece {
    bool Empty() { return x_==EMPTY_CELL_CHAR; }
    char x_;
    Block* blocks_[NBOR_BLOCK_NUM];
    ActiveMarker<Piece*, GRID_SIZE>::IdType activeids_[NBOR_BLOCK_NUM];
};

class SudokuSolver { // find one solution only and used only once @@
public:
    SudokuSolver() { InitPieces(); Reset(); }
    void Reset();

    // Assume always valid input and Empty cells are indicated by the character '.'.
    void ReadIn(std::vector<std::vector<char> > &board);
    std::vector<std::vector<char> > SampleOut();

    void FindOneSudoku();
    void FindOneSudokuRec(Piece* recs[], int recidx, int piecenum);

    bool IsSolved() { return fillednum_ == GRID_SIZE*GRID_SIZE; }

private:
    void InitPieces();
    NumCharMarker GetValidChars(Piece* ptrp);
    void FillOnePiece(Piece*, char);
    void UndoFillPiece(Piece*, char);

    void MarkPiecesInBlock(Block* ptrblock, char x) {
        ptrblock->charmaker_.Mark(x);
    }
    void UnMarkPiecesInBlock(Block* ptrblock, char x) {
        ptrblock->charmaker_.UnMark(x);
    }
    void UnMarkPiecesInBlockAllChar(Block* ptrblock) {
        ptrblock->charmaker_.UnMarkAll();
    }

    void DebugCoutPieces() {
        using namespace std;
        for (int i=0; i<GRID_SIZE; ++i)  {
            cout << pieces_[i][0].x_;
            for (int j=1; j<GRID_SIZE; ++j) {
                cout << " " << pieces_[i][j].x_;
            }
            cout << endl;
        }
        cout << endl;
    }
    void DebugCoutPiecesBlockIds(int blockindex) {
        using namespace std;
        for (int i=0; i<GRID_SIZE; ++i)  {
            cout << pieces_[i][0].activeids_[blockindex];
            for (int j=1; j<GRID_SIZE; ++j) {
                cout << " " << pieces_[i][j].activeids_[blockindex];
            }
            cout << endl;
        }
        cout << endl;
    }

    Piece pieces_[GRID_SIZE][GRID_SIZE];
    Block blocks_[NBOR_BLOCK_NUM][GRID_SIZE]; // block buffer
    int fillednum_;
};

////////////////////////////////////////////////////////////////
}

#endif