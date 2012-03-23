#include <iostream>
#include <vector>

const int ROW_NUM = 3;
const int COL_NUM = 3;

void ZeroRowCol(int mat[ROW_NUM][COL_NUM])
{
    if (ROW_NUM <= 0 || COL_NUM <= 0 )
    {
        return;
    }

    using namespace std;
    vector <bool> zrows(ROW_NUM, false);
    vector <bool> zcols(COL_NUM, false);

    for (int i=0; i<ROW_NUM; ++i)
    {
        for (int j=0; j<COL_NUM; ++j)
        {
            if (mat[i][j]==0)
            {
                zrows[i] = true;
                zcols[j] = true;
            }
        }
    }

    for (int i=0; i<ROW_NUM; ++i)
    {
        for (int j=0; j<COL_NUM; ++j)
        {
            if (zrows[i] || zcols[j])
            {
                mat[i][j] = 0;
            }
        }
    }
}

void CoutMatrix(const int mat[ROW_NUM][COL_NUM])
{
    for (int i=0; i<ROW_NUM; ++i)
    {
        for (int j=0; j<COL_NUM; ++j)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    int mat[ROW_NUM][COL_NUM];

    for (int i=0; i<ROW_NUM; ++i)
    {
        for (int j=0; j<COL_NUM; ++j)
        {
            mat[i][j] = rand() % 4;
        }
    }

    CoutMatrix(mat);

    ZeroRowCol(mat);

    CoutMatrix(mat);

    return 0;
}