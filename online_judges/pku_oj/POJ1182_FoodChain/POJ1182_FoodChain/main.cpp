#include <cstdio>
#include <cstdlib>

#pragma warning(disable: 4996)

struct AnimalType {
    char relation; // 0, 1, or 2
    int upper; // upper eats current
};

class Solution {
public:
    void Reset(int num) {
        num_ = num+1;
        for (int i=0; i<num_; ++i) {
            animals_[i].relation = 0;
            animals_[i].upper = i; // related to self as equal
        }
    }

    bool IsValid(int x, int y, char relation) {
        int xr = FindRoot(x);
        int yr = FindRoot(y);
        if (xr==yr && relation!=RelativeRelation(animals_[x].relation, animals_[y].relation)) return false;
        return true;
    }

    void AddRelation(int x, int y, char relation) {
        int xr = FindRoot(x);
        int yr = FindRoot(y);
        if (xr==yr) return; // already in the same chain

        animals_[yr].relation = (3 - animals_[y].relation + relation + animals_[x].relation) % 3;
        animals_[yr].upper = xr;
    }

private:
    inline char RelativeRelation(char a, char b) { return (3+b-a)%3; }
    int FindRoot(int x) { // find the highest food chain level
        if (x!=animals_[x].upper) {
            int relative = animals_[x].upper;
            animals_[x].upper = FindRoot(relative);
            animals_[x].relation = (animals_[x].relation + animals_[relative].relation) % 3;
        }
        return animals_[x].upper;
    }

    static const int kMaxN = 50001;
    int num_;
    AnimalType animals_[kMaxN];
};

int main() {
    int n, k, d, x, y;
    Solution solver;
    int cnt = 0;
    scanf("%d %d", &n, &k);
    solver.Reset(n);
    for(int i=0; i<k; ++i) {
        scanf("%d %d %d", &d, &x, &y);
        if(n<x || n<y || ((d==2)&&(x==y)) || (!solver.IsValid(x, y, d-1))) {
            ++cnt;
        } else {
            solver.AddRelation(x, y, d-1);
        }
        // printf("%d, %d: %d %d %d\n", i, cnt, d, x, y);
    }
    printf("%d\n", cnt);

    return 0;
}