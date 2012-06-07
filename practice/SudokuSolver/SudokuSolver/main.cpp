#include <iostream>
#include <vector>
#include "sudoku_solver.h"
#include "active_maker.h"

namespace // unnamed
{
////////////////////////////////////////////////////////////////

using namespace std;
using namespace augment_puzzle_helpers;

class Solution {
public:
    void solveSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        static SudokuSolver helper;
        helper.ReadIn(board);
        helper.FindOneSudoku();
        board = helper.SampleOut();
    }
};

////////////////////////////////////////////////////////////////
}


int main(int argc, char** argv)
{
    // play with numcharmarker
    NumCharMarker numcharmarkerone;
    numcharmarkerone.Mark('1');
    NumCharMarker numcharmarkertwo = numcharmarkerone;
    char activenum = numcharmarkertwo.ActiveNum();
    for (int i=0; i<100; ++i) {
        char chidx = rand()%9;
        char x = numcharmarkertwo.NextViaIndex(chidx);
        numcharmarkerone.Mark(x);

        char nextone = numcharmarkerone.Next();
        char nexttwo = numcharmarkertwo.Next();
        cout << nextone << "    " << nexttwo << endl;

        numcharmarkerone.UnMark(x);
    }

    cout << "//////////////////////////////////////////////////////////////////////////" << endl;
    cout << "// MARKER ONE:" << endl;
    for (char chidx=0; chidx<numcharmarkerone.ActiveNum(); ++chidx) {
        cout << numcharmarkerone.NextViaIndex(chidx);
    }
    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;
    cout << "//////////////////////////////////////////////////////////////////////////" << endl;
    cout << "// MARKER TWO:" << endl;
    for (char chidx=0; chidx<numcharmarkertwo.ActiveNum(); ++chidx) {
        cout << numcharmarkertwo.NextViaIndex(chidx);
    }
    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;

    const int ACTIVE_CHAR_NUM = 10;
    ActiveMarker<char, ACTIVE_CHAR_NUM> charmarkerthree;
    charmarkerthree.MarkAll();

    ActiveMarker<char, ACTIVE_CHAR_NUM>::IdType activeids[ACTIVE_CHAR_NUM];
    for (int i=0; i<ACTIVE_CHAR_NUM; ++i) {
        activeids[i] = charmarkerthree.Add('0'+i);
    }

    for (int i=0; i<ACTIVE_CHAR_NUM; ++i) {
        charmarkerthree.Mark(activeids[i]);
        char nextone = charmarkerthree.Next();
        cout << nextone << "    " << endl;
        charmarkerthree.UnMark(activeids[i]);
    }

    Solution solver;

    char* rowbd[] = {
        "53..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };
    int sudosize = sizeof(rowbd)/sizeof(char*); // default as 9
    vector<vector<char> > board(sudosize);
    for (int i=0; i<(int)board.size(); ++i) {
        board[i] = vector<char>(rowbd[i], rowbd[i]+sudosize);
    }
    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;
    cout << endl;
    for (int i=0; i<(int)board.size(); ++i)  {
        vector<char>::iterator itr = board[i].begin();
        cout << *itr;
        ++itr;
        for (; itr!=board[i].end(); ++itr) {
            cout << " " << *itr;
        }
        cout << endl;
    }
    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;

    solver.solveSudoku(board);

    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;
    cout << endl;
    for (int i=0; i<(int)board.size(); ++i)  {
        vector<char>::iterator itr = board[i].begin();
        cout << *itr;
        ++itr;
        for (; itr!=board[i].end(); ++itr) {
            cout << " " << *itr;
        }
        cout << endl;
    }
    cout << endl << "//////////////////////////////////////////////////////////////////////////" << endl;

    return 0;
}