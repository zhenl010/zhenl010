#include <iostream>

namespace { // unnamed namespace
//////////////////////////////////////////////////////////////////////////

const int ROW_NUM = 5;
const int COL_NUM = 5;

// template version might be better?
template<typename T, int M, int N>
class SpiralPrintWorker {
public:
    SpiralPrintWorker(const T (&mat)[M][N]): mat_(mat) {}

    void print();

private:
    const T (&mat_)[M][N];
    void PrintRow(int row, int s, int e);
    void PrintCol(int col, int s, int e);
};

// template<typename T, int M, int N>
template<typename T, int M, int N>
void SpiralPrintWorker<T, M, N>::print() {
    int b = 0;
    int l = 0;
    int t = M - 1;
    int r = N - 1;
    while ( (l<=r) && (b<=t) ) {
        PrintRow(b++, l, r); if (t<b) continue;
        PrintCol(r--, b, t); if (r<l) continue;
        PrintRow(t--, r, l); if (t<b) continue;
        PrintCol(l++, t, b);
    }
}

template<typename T, int M, int N>
void SpiralPrintWorker<T, M, N>::PrintRow(int row, int s, int e) {
    int inc = (e < s) ? -1 : 1;
    while (s != e) {
        std::cout << mat_[row][s] << " ";
        s += inc;
    }
    std::cout << mat_[row][s] << " ";
}

template<typename T, int M, int N>
void SpiralPrintWorker<T, M, N>::PrintCol(int col, int s, int e) {
    int inc = (e < s) ? -1 : 1;
    while (s != e) {
        std::cout << mat_[s][col] << " ";
        s += inc;
    }
    std::cout << mat_[s][col] << " ";
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

// intuitive version that print layer by layer, and a stand-alone version
void CoutByLayer(const int mat[ROW_NUM][COL_NUM]) {
    if (ROW_NUM<=0 || COL_NUM<=0) return;

    for (int layer=0; layer<=(std::min(ROW_NUM, COL_NUM)-1)/2; ++layer) {
        for (int i=layer, j=layer; j<COL_NUM-layer; ++j) {
            std::cout << mat[i][j] << " ";
        }

        if (ROW_NUM-layer-1 != layer) {// degenerate case
            for (int i=layer+1, j=COL_NUM-layer-1; i<ROW_NUM-layer-1; ++i) {
                std::cout << mat[i][j] << " ";
            }

            for (int i=ROW_NUM-layer-1, j=COL_NUM-layer-1; j>=layer; --j) {
                std::cout << mat[i][j] << " ";
            }

            if (COL_NUM-layer-1 != layer) { // degenerate case
                for (int i=ROW_NUM-layer-2, j=layer; i>layer; --i) {
                    std::cout << mat[i][j] << " ";
                }
            }
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void SpiralPrintMatrix(const int arr[ROW_NUM][COL_NUM]) {
    int rowmin = 0;
    int rowmax = ROW_NUM-1;
    int colmin = 0;
    int colmax = COL_NUM-1;

    int i = 0; // variable for index used in the following loop
    while(colmin<=colmax && rowmin<=rowmax) {
        for(i=colmin; i<=colmax; i++) { // upper row
            std::cout << arr[rowmin][i] << " ";
        }
        ++rowmin;
        if(rowmax<rowmin) continue;
        for(i=rowmin; i<=rowmax; i++) { // right col
            std::cout << arr[i][colmax] << " ";
        }
        --colmax;
        if(colmax<colmin) continue;
        for(i=colmax; i>=colmin; i--) { // bottom row
            std::cout << arr[rowmax][i] << " ";
        }
        rowmax --;
        for(i=rowmax; i>=rowmin; i--) { // left col
            std::cout << arr[i][colmin] << " ";
        }
        colmin ++;
    }
}

//////////////////////////////////////////////////////////////////////////
} // end of unnamed namespace

int main() {
    // allocation
    double** pp = new double* [ROW_NUM];
    pp[0] = new double [ROW_NUM * COL_NUM];
    for (int i = 1; i < ROW_NUM; ++i) {
        pp[i] = pp[i-1] + COL_NUM;
    }

    // use pp[i][j]
    // If the template were using T**:
    // SpiralPrintWorker<double, ROW_NUM, COL_NUM> spiral(pp);

    // deallocation
    delete [] pp[0];
    delete [] pp;

    // if using boost:
    // Create a 3D array
    // typedef boost::multi_array<double, 3> array_type;
    // typedef array_type::index index;
    // array_type A(boost::extents[x][y][z]);
    // for(index i = 0; i != x; ++i) 
    //     for(index j = 0; j != y; ++j)
    //         for(index k = 0; k != z; ++k)
    //             A[i][j][k] = values++;

    // static size 2-D array
    int mat[ROW_NUM][COL_NUM];
    for (int i=0; i<ROW_NUM; ++i) {
        for (int j=0; j<COL_NUM; ++j) {
            mat[i][j] = i*COL_NUM + j;
        }
    }

    // If the template were using T[M][N]:
    SpiralPrintWorker<int, ROW_NUM, COL_NUM> worker(mat);
    worker.print();
    std::cout << std::endl << std::endl;

    CoutMatrix(mat);

    SpiralPrintMatrix(mat);

    return 0;
}