#include "sudoku_solver.h"
#include <queue>
#include <algorithm>

namespace augment_puzzle_helpers
{
////////////////////////////////////////////////////////////////

namespace // unnamed
{
////////////////////////////////////////////////////////////////

// bool PieceActiveLess(Piece* &lhs, Piece* &rhs) {
//     return (lhs->charmaker_).ActiveNum() < (rhs->charmaker_).ActiveNum();
// }
// 
// class PieceActiveLess {
//     bool operator() (Piece* &lhs, Piece* &rhs) const {
//         return (lhs->charmaker_).ActiveNum() < (rhs->charmaker_).ActiveNum();
//     }
// };

////////////////////////////////////////////////////////////////
}

void SudokuSolver::Reset() {
    fillednum_ = 0;
    // reset blocks
    for (char i=BOX; i<NBOR_BLOCK_NUM; ++i) {
        for (int j=0; j<GRID_SIZE; ++j) {
            blocks_[i][j].pieces_.UnMarkAll();
            blocks_[i][j].charmaker_.UnMarkAll();
        }
    }
    // reset pieces
    for (int i=0; i<GRID_SIZE; ++i) {
        for (int j=0; j<GRID_SIZE; ++j) {
            pieces_[i][j].x_ = EMPTY_CELL_CHAR;
        }
    }
}

// Assume always valid input and Empty cells are indicated by the character '.'.
void SudokuSolver::ReadIn(std::vector<std::vector<char> > &board) {
    Reset();
    for (int i=0; i<GRID_SIZE; ++i) {
        for (int j=0; j<GRID_SIZE; ++j) {
            if (board[i][j] == '.') { continue; }
            FillOnePiece(&pieces_[i][j], board[i][j]);
        }
    }
}

std::vector<std::vector<char> > SudokuSolver::SampleOut() {
    std::vector<std::vector<char> > board(GRID_SIZE);
    for (int i=0; i<GRID_SIZE; ++i) {
        board[i].resize(GRID_SIZE);
    }

    for (int i=0; i<GRID_SIZE; ++i) {
        for (int j=0; j<GRID_SIZE; ++j) {
            if (pieces_[i][j].Empty()) { // empty cell
                board[i][j] = '_';
            } else {
                board[i][j] = pieces_[i][j].x_;
            }
        }
    }
    return board;
}

// assume moderate number of cells filled already
void SudokuSolver::FindOneSudoku() {
    // priority_queue<Piece*, PieceActiveLess> piecequeue;
    Piece* recs[GRID_SIZE * GRID_SIZE];
    int piecenum = 0;
    for (int i=0; i<GRID_SIZE; ++i) {
        for (int j=0; j<GRID_SIZE; ++j) {
            if (pieces_[i][j].Empty()) {
                recs[piecenum++] = &pieces_[i][j];
            }
        }
    }

    // std::sort(recs, recs+piecenum, PieceActiveLess);
    FindOneSudokuRec(recs, 0, piecenum);
}

// precondition assumes there's AT LEAST one solution
void SudokuSolver::FindOneSudokuRec(Piece* recs[], int recidx, int piecenum) {
    if (IsSolved()) return;

    Piece* ptrp = recs[recidx];
    NumCharMarker charmarker = GetValidChars(ptrp);

    for (char chid=0; chid<charmarker.ActiveNum(); ++chid) {
        char fillchar = charmarker.NextViaIndex(chid);
        // Fill
        FillOnePiece(ptrp, fillchar);
        // Recursively search till find solution or fail
        FindOneSudokuRec(recs, recidx+1, piecenum);
        // Test
        if (IsSolved()) return;
        // DebugCoutPieces();
        // Undo
        UndoFillPiece(ptrp, fillchar);
    }
}

void SudokuSolver::InitPieces() {
    for (int i=0; i<GRID_SIZE; ++i) {
        for (int j=0; j<GRID_SIZE; ++j) {
            // default value is a valid solution without filled element
            // pieces_[i][j].x_ = (i*SQUARE_SIZE + i/SQUARE_SIZE + j) % GRID_SIZE + 1;
            Piece* ptrp = &pieces_[i][j];
            int boxid = SQUARE_SIZE*(i/SQUARE_SIZE)+(j/SQUARE_SIZE);
            ptrp->blocks_[BOX] = &blocks_[BOX][boxid];
            ptrp->blocks_[ROW] = &blocks_[ROW][i];
            ptrp->blocks_[COL] = &blocks_[COL][j];
            // memorize active ids when added to blocks
            ptrp->activeids_[BOX] = (blocks_[BOX][boxid]).pieces_.Add(ptrp);
            ptrp->activeids_[ROW] = (blocks_[ROW][i]).pieces_.Add(ptrp);
            ptrp->activeids_[COL] = (blocks_[COL][j]).pieces_.Add(ptrp);
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // std::cout << "BOX ids:" << std::endl;
    // DebugCoutPiecesBlockIds(BOX);
    // std::cout << "ROW ids:" << std::endl;
    // DebugCoutPiecesBlockIds(ROW);
    // std::cout << "COL ids:" << std::endl;
    // DebugCoutPiecesBlockIds(COL);
    // std::cout << ":____:" << std::endl;
    //////////////////////////////////////////////////////////////////////////
}

NumCharMarker SudokuSolver::GetValidChars(Piece* ptrp) {
    NumCharMarker charmkr;
    for (int bid=BOX; bid<NBOR_BLOCK_NUM; ++bid) {
        // reverse use of invalid chars
        NumCharMarker* ptrmker = &(ptrp->blocks_[bid]->charmaker_);
        for (char chdx=ptrmker->ActiveNum(); chdx<NUMERIC_CHAR_NUM; ++chdx) {
            if (charmkr.IsActive(ptrmker->NextViaIndex(chdx))) {
                charmkr.Mark(ptrmker->NextViaIndex(chdx));
            }
        }
    }
    return charmkr;
}

// Precondition assumes the chosen char is always valid!
void SudokuSolver::FillOnePiece(Piece* ptrp, char elm) {
    ptrp->x_ = elm;
    ++fillednum_;
    for (char bid=BOX; bid<NBOR_BLOCK_NUM; ++bid) {
        Block* ptrblock = ptrp->blocks_[bid];
        (ptrblock->pieces_).Mark(ptrp->activeids_[bid]);
        MarkPiecesInBlock(ptrblock, elm);
    }
}

void SudokuSolver::UndoFillPiece(Piece* ptrp, char elm) {
    ptrp->x_ = EMPTY_CELL_CHAR;
    --fillednum_;
    for (char bid=BOX; bid<NBOR_BLOCK_NUM; ++bid) {
        Block* ptrblock = ptrp->blocks_[bid];
        UnMarkPiecesInBlock(ptrblock, elm);
        (ptrblock->pieces_).UnMark(ptrp->activeids_[bid]);
    }
}

////////////////////////////////////////////////////////////////
}