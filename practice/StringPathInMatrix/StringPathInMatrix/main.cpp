//////////////////////////////////////////////////////////////////////////
// 输入一个矩阵：
// 
// ABCE
// SFCS
// ADEE
// 
// 和 一个string 比如 ABCCED
// 
// 判断这个string 是否是矩阵的一个连续路径（可以上下左右移动，一次一格），矩阵
// 中用过的字母不能再用。
// 
// 比如 ABCCED  可以。SEE 可以
// 但 ABCB 就不行 因为B 已被用过 不能往回走。
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>
#include <list>

const int MATRIX_ROWS = 3;
const int MATRIX_COLS = 4;
const int NBOR_NUM = 4;

struct IntVec2
{
    int row;
    int col;
};

const IntVec2 NbrVecDiff[NBOR_NUM] =
{
    { 0,-1 },
    { 0, 1 },
    {-1, 0 },
    { 1, 0 }
};

// helper function
void AddNewNbors(std::list<IntVec2>& newCells, const std::vector< std::vector<bool> >& processedMat, const IntVec2& curCell)
{
    // Generate neighbor cells and add if valid
    for (int i=0; i<NBOR_NUM; ++i)
    {
        IntVec2 nbrCell = { curCell.row + NbrVecDiff[i].row
                          , curCell.col + NbrVecDiff[i].col };
        if ( nbrCell.row >=0 && static_cast<unsigned int>(nbrCell.row) < processedMat.size() 
            && nbrCell.col >= 0 && static_cast<unsigned int>(nbrCell.col) < processedMat[nbrCell.row].size() )
        {
            if (processedMat[nbrCell.row][nbrCell.col] == false)
            {
                newCells.push_back(nbrCell);
            }
        }
    }
}

// helper function assuming str no-empty
bool FindPathExist(const char matrixIn[MATRIX_ROWS][MATRIX_COLS], const std::string& str, int idx, 
    std::vector< std::vector<bool> >& processedMat, std::list<IntVec2>& activeCells)
{
    while (activeCells.empty() == false)
    {
        IntVec2 cell = activeCells.front();
        activeCells.pop_front();

        // search further when match
        if (matrixIn[cell.row][cell.col] == str[idx])
        {
            if (idx == (str.length()-1))
            {
                // fully matched !!!
                return true;
            } 
            else
            {
                // mark and search deeper
                processedMat[cell.row][cell.col] = true;
                std::list<IntVec2> newCells;
                AddNewNbors(newCells, processedMat, cell);
                if (FindPathExist(matrixIn, str, idx+1, processedMat, newCells))
                {
                    return true;
                }
                processedMat[cell.row][cell.col] = false;
            }
        }        
    }
    return false;
}

// helper function assuming str no-empty
bool PathStrExist(const char matrixIn[MATRIX_ROWS][MATRIX_COLS], int row, int col, const std::string& str)
{
    using namespace std;

    vector< vector<bool> > processedMat(MATRIX_ROWS);
    for (int i=0; i<MATRIX_ROWS; ++i)
    {
        processedMat[i].resize(MATRIX_COLS, false);
    }

    list<IntVec2> activeCells;
    IntVec2 cell = { row, col };
    activeCells.push_back(cell);
    
    return FindPathExist(matrixIn, str, 0, processedMat, activeCells);
}

bool PathStrExist(const char matrixIn[MATRIX_ROWS][MATRIX_COLS], const std::string& str)
{
    // empty str is a special case
    if (str.empty() == true)
    {
        return true;
    }

    for (int iRow=0; iRow<MATRIX_ROWS; ++iRow)
    {
        for (int iCol=0; iCol<MATRIX_COLS; ++iCol)
        {
            if (PathStrExist(matrixIn, iRow, iCol, str))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    using namespace std;

    char knownMatrix[MATRIX_ROWS][MATRIX_COLS] = 
    {
        { 'A', 'B', 'C', 'E' },
        { 'S', 'F', 'C', 'S' },
        { 'A', 'D', 'E', 'E' }
    };

    string pathStr = "ABCCEDFSA";
    // string pathStr = "ABCB";
    // string pathStr = "SEE";
    // string pathStr = "\n";

    cout << pathStr << endl << endl;
    
    if (PathStrExist(knownMatrix, pathStr))
    {
        cout << "Path Exist!!!" << endl;
    } 
    else
    {
        cout << "Cant find that path!!!" << endl;
    }

    return 0;
}