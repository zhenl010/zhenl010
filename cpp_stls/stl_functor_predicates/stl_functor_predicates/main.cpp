#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TableBasedSorter {
    TableBasedSorter() {
        for(int i = 0; i < 128; ++i) {
            mTable[i] = ((rand() ^ 0xff80) + 128) - i;
        }
    }
    bool operator()(int a, int b) const {
        return mTable[b] < mTable[a];
    }
    int mTable[128];
} table_based_compare;

bool myfunction (int i,int j) { return (i<j); }

struct myclass {
    bool operator() (int i,int j) { return (i<j);}
} myobject;

int main(int argc, char** argv) {
    int myints[] = {32,71,12,45,26,80,53,33};
    vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33


    // using object as comp
    sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

    sort(myvector.begin(), myvector.end(), table_based_compare);

    // print out content:
    cout << "myvector contains:";
    for (auto it=myvector.begin(); it!=myvector.end(); ++it)
        cout << " " << *it;

    cout << endl;

    return 0;
}