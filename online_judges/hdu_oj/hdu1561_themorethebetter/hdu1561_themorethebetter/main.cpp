#include <iostream>
#include <vector>

const int MAX_M = 200;
const int MAX_N = 200;

struct Target {
    int pre;
    int val;
};

struct PubBuffer {
    int TotY[MAX_M][MAX_N];
    int TotN[MAX_M][MAX_N];
};

void SetZeroes(PubBuffer& buffer, int N, int M) {
    for (int i=0; i<M; ++i) {
        for (int j=0; i<N; ++i) {
            buffer.TotY[i][j] = 0;            
        }
    }
} 

class Solution {
public:
    Solution() {
        ptr_curr = &buffer_one;
        ptr_prev = &buffer_two;
    }

    int FindMostValue(Target targets[], int N, int M) {
        Init(N, M);

        return 0;
    }

private:
    void Init(int N, int M) {
    }

    PubBuffer buffer_one;
    PubBuffer buffer_two;
    PubBuffer* ptr_curr;
    PubBuffer* ptr_prev;
};

int main() {
    using namespace std;

    int N, M;
    Solution solver;
    do {
        cin >> N >> M;
        Target targets[MAX_N];
        for (int i=0; i<N; ++i) {
            cin >> targets[i].pre >> targets[i].val;
        }
        cout << solver.FindMostValue(targets, N, M) << endl;
    } while (!(N==0 && M==0));
    
    return 0;
}