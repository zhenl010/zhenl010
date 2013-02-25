#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

const int MATRIX_SIZE = 3; // assume same number of column and rows
const int MATRIX_INDEX_MAX = MATRIX_SIZE - 1;

template<class T>
inline void RotateElements(T& a, T& b, T& c, T& d) {
    T tmp = a;
    a = b;
    b = c;
    c = d;
    d = tmp;
}

// Rotate clock wise
template<class T, int N>
void RotateMatrixCW(T mat[N][N]) {
    for (int i=0; i<=(N-1)/2; ++i) {
        for (int j=i; j<(N-1)-i; ++j) {
            RotateElements<int>( mat[i][j],
                mat[(N-1)-j][i],
                mat[(N-1)-i][(N-1)-j],
                mat[j][(N-1)-i]);
        }
    }
}

// Rotate clock wise
template<class T, int N>
void RotateMatrixCCW(T mat[N][N]) {
    for (int i=0; i<=(N-1)/2; ++i) {
        for (int j=i; j<(N-1)-i; ++j) {
            RotateElements<int>( mat[i][j],
                mat[j][(N-1)-i],
                mat[(N-1)-i][(N-1)-j],
                mat[(N-1)-j][i]);
        }
    }
}

void CoutMatrix(int color_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    using namespace std;
    for (int i=0; i<MATRIX_SIZE; ++i) {
        for (int j=0; j<MATRIX_SIZE; ++j) {
            cout << color_matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//////////////////////////////////////////////////////////////////////////
}


int main(int argc, char** argv) {
    int mat[MATRIX_SIZE][MATRIX_SIZE];
    for (int i=0; i<MATRIX_SIZE; ++i) {
        for (int j=0; j<MATRIX_SIZE; ++j) {
            mat[i][j] = i*MATRIX_SIZE+j+1;
        }
    }

    CoutMatrix(mat);

    RotateMatrixCCW<int, MATRIX_SIZE>(mat);
    std::cout << "after rotation" << std::endl << std::endl;
    CoutMatrix(mat);

    RotateMatrixCW<int, MATRIX_SIZE>(mat);
    std::cout << "after rotation" << std::endl << std::endl;
    CoutMatrix(mat);

    return 0;
}