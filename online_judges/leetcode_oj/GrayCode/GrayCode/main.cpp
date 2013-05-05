#include <iostream>
#include <vector>

using namespace std;

class GrayCodeStream {
public:
    explicit GrayCodeStream(int n): mask_(0<n ? 1<<(n-1) : 0), x_(0), idx_(0) {}

    vector<int> GetFullCircle() {
        vector<int> codes;
        mems_[++idx_] = Mem(mask_, 0);

        while (0<idx_) {
            Mem mem = mems_[idx_--];
            if (mem.mask==0) { codes.push_back(x_); continue; }

            if (mem.stage == 0) {
                mem.stage = 1;
                mems_[++idx_] = mem;
                mems_[++idx_] = Mem(mem.mask>>1, 0); // 1st recursive call
            } else if (mem.stage == 1) {
                x_ ^= mem.mask;
                mems_[++idx_] = Mem(mem.mask>>1, 0); // 2nd recursive call
            }
        }

        return codes;
    }

    int Next() { // this totally works !!!!!!
        isnew_ = true;
        Mem mem;
        while (isnew_) {
            if (!(0<idx_)) { mems_[++idx_] = Mem(mask_, 0); x_ = 0; }

            mem = mems_[idx_--];
            if (mem.mask==0) {
                isnew_=false;
            } else if (mem.stage == 0) {
                mem.stage = 1;
                mems_[++idx_] = mem;
                mems_[++idx_] = Mem(mem.mask>>1, 0); // 1st recursive call
            } else if (mem.stage == 1) {
                x_ ^= mem.mask;
                mems_[++idx_] = Mem(mem.mask>>1, 0); // 2nd recursive call
            }
        }
        return x_;
    }

private:
    struct Mem {
        int mask;
        int stage;
        Mem(int m=0, int s=0): mask(m), stage(s){}
    };

    bool isnew_;
    int mask_;
    int x_;
    int idx_;
    Mem mems_[64];
};

class IterSolution {
public:
    vector<int> grayCode(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        GrayCodeStream strm(n); // return strm.GetFullCircle();
        int x = strm.Next();
        vector<int> codes(1, x);
        for (int y=strm.Next(); y!=x; y=strm.Next()) { codes.push_back(y); }
        return codes;
    }
};

class Solution {
public:
    vector<int> grayCode(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> codes;

        int mask = 0<n ? 1<<(n-1) : 0;
        int x = 0;
        GrayCode(codes, mask, x);

        return codes;
    }

    vector<int> grayCodeHacked(int n) { // this is more like a hack lol
        vector<int> ret;
        int count = 0x01 << n;
        for(int i = 0 ; i < count; ++i) {
            ret.push_back(i ^ (i>>1));
        }
        return ret;
    }

private:
    void GrayCode(vector<int>& codes, int mask, int& x) {
        if (mask == 0) {
            codes.push_back(x);
            return;
        }

        GrayCode(codes, mask>>1, x);
        x ^= mask;
        GrayCode(codes, mask>>1, x);
    }
};

int main() {
    Solution solver;
    IterSolution itr_sol;

    for (int i=-1; i<5; ++i) {
        vector<int> codes_itr = itr_sol.grayCode(i);
        vector<int> codes_rec = solver.grayCode(i);
        if (codes_itr != codes_rec) cout << "Results differ!!!" << endl;
    }

    return 0;
}