// http://apps.topcoder.com/forums/;jsessionid=E9F9D7AD8268C70E91E2FBEC32D9EEBF?module=Thread&threadID=510405&start=0&mc=4#536735
// For the first problem you can get an exact formula as an answer:
// 
// ==> geometry/tiling/count.1x2.p <==
// Count the ways to tile an MxN rectangle with 1x2 dominos.
// 
// ==> geometry/tiling/count.1x2.s <==
// The number of ways to tile an MxN rectangle with 1x2 dominos is
// 2^(M*N/2) times the product of
// 
// { cos^2(m*pi/(M+1)) + cos^2(n*pi/(N+1)) } ^ (1/4)
// 
// over all m,n in the range 0<m><M+1, 0><n><N+1.
// 
// (this was taken from http://www.faqs.org/faqs/puzzles/archive/geometry/part1/ )
// 
// These problems are similar to the problem pavement which was a backup task in IOI 2001, you can find the solution here http://olympiads.win.tue.nl/ioi/ioi2001/contest/A-2001-7.pdf . 
// Also the task bugs from ceoi 2002, you can find the problem and it's solution here: http://ics.upjs.sk/ceoi/Documents.html . 
// Also this problem from topcoder ( http://www.topcoder.com/stat?c=problem_statement&pm=1706&rd=5855 ) is similar, you can find the solution here: http://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm209 .>
#include <cstdio>

#pragma warning(disable: 4996)

class TilingCounter {
public:
    static const int MAXH = 12;
    static const int MAXW = 11;
    static const int MAX_CASENUM = 1<<MAXW;

    TilingCounter(int h, int w)
    : h_(h), w_(w), cnts_() {
        if (h_<w_) { h_=w; w_=h; } // swap(h_, w_);
        case_num_ = 1<<w_;
        cnts_[0][0] = 1;
    }

    long long int GetCount() {
        if ((h_*w_) % 2 == 1) return 0;

        int comp_line = 0;
        for(int i=0; i<h_; ++i) {
            for (int j=0; j<case_num_; ++j) {
                if (0 < cnts_[i][j]) { UpdateCount(i, j, 0, comp_line); }
            }
        }

        return cnts_[h_][0];
    }

private:
    void UpdateCount(int i, int j, int k, int comp_line) {
        if (w_ <= k) {
            cnts_[i+1][comp_line] += cnts_[i][j];
            return;
        }

        if (j>>k & 1) {
            // no tiling:
            comp_line &= (~(1<<k));
            UpdateCount(i, j, k+1, comp_line);
        } else {
            // tiling one:
            comp_line |= (1<<k);
            UpdateCount(i, j, k+1, comp_line);

            // tiling two:
            if (((k+1)<w_) && (0==(j>>(k+1) & 1))) {
                comp_line &= (~(3<<k));
                UpdateCount(i, j, k+2, comp_line);
            }
        }
    }

    int h_;
    int w_;
    int case_num_;
    long long int cnts_[MAXH][MAX_CASENUM]; // init as zeros
};

long long int ans_hack[12][12]={{0,1,0,1,0,1,0,1,0,1,0},{1,2,3,5,8,13,21,34,55,89,144},{0,3,0,11,0,41,0,153,0,571,0},
{1,5,11,36,95,281,781,2245,6336,18061,51205},{0,8,0,95,0,1183,0,14824,0,185921,0},
{1,13,41,281,1183,6728,31529,167089,817991,4213133,21001799},
{0,21,0,781,0,31529,0,1292697,0,53175517,0},
{1,34,153,2245,14824,167089,1292697,12988816,108435745,1031151241,8940739824},
{0,55,0,6336,0,817991,0,108435745,0,14479521761,0},
{1,89,571,18061,185921,4213133,53175517,1031151241,14479521761,258584046368,3852472573499},
{0,144,0,51205,0,21001799,0,8940739824,0,3852472573499,0}};

int main() {
    int h, w;
    scanf("%d %d", &h, &w);
    while(0<h && 0<w) {
        printf("%lld\n", TilingCounter(h,w).GetCount());
        scanf("%d %d", &h, &w);
    }
    return 0;
}