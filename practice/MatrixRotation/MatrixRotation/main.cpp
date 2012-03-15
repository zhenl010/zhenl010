#include <iostream>

const int MATRIX_SIZE = 4; // assume same number of column and rows
const int MATRIX_INDEX_MAX = MATRIX_SIZE - 1;

void CoutMatrix(int color_matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    using namespace std;
    for (int i=0; i<MATRIX_SIZE; ++i)
    {
        for (int j=0; j<MATRIX_SIZE; ++j)
        {
            cout << color_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Rotate clock wise
// more intuitive way of getting rotated indices
void RotateMatrixCCW(int mat[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int layer=0; layer<=(MATRIX_INDEX_MAX/2); ++layer)
    {
        for (int loc=0; loc<=(MATRIX_INDEX_MAX-2*layer-1); ++loc)
        {
            int tmp = mat[layer][layer+loc];
            mat[layer][layer+loc] = mat[layer+loc][MATRIX_INDEX_MAX-layer];
            mat[layer+loc][MATRIX_INDEX_MAX-layer]=mat[MATRIX_INDEX_MAX-layer][MATRIX_INDEX_MAX-layer-loc];
            mat[MATRIX_INDEX_MAX-layer][MATRIX_INDEX_MAX-layer-loc] = mat[MATRIX_INDEX_MAX-layer-loc][layer];
            mat[MATRIX_INDEX_MAX-layer-loc][layer] = tmp;
        }
    }
}

// Rotate clock wise
// more general way of getting rotated indices
void RotateMatrixCW(int mat[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i=0; i<=MATRIX_INDEX_MAX/2; ++i)
    {
        for (int j=i; j<MATRIX_INDEX_MAX-i; ++j)
        {
            int tmp = mat[i][j];
            mat[i][j] = mat[MATRIX_INDEX_MAX-j][i];
            mat[MATRIX_INDEX_MAX-j][i] = mat[MATRIX_INDEX_MAX-i][MATRIX_INDEX_MAX-j];
            mat[MATRIX_INDEX_MAX-i][MATRIX_INDEX_MAX-j] = mat[j][MATRIX_INDEX_MAX-i];
            mat[j][MATRIX_INDEX_MAX-i] = tmp;
        }
    }
}

int main()
{
    int color_matrix[MATRIX_SIZE][MATRIX_SIZE];

    for (int i=0; i<MATRIX_SIZE; ++i)
    {
        for (int j=0; j<MATRIX_SIZE; ++j)
        {
            color_matrix[i][j] = i*MATRIX_SIZE+j;
        }
    }

    CoutMatrix(color_matrix);

    RotateMatrixCCW(color_matrix);

    CoutMatrix(color_matrix);

    RotateMatrixCW(color_matrix);

    CoutMatrix(color_matrix);

    return 0;
}