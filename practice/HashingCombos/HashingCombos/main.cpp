#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "VectorHeap.h"

int main (int argc, char** argv)
{
    using namespace std;
    using namespace augment_hash_functions;

    unordered_map<std::vector<int>, int, VectorHash<int> > clickcombos;

    std::vector<int> cmb = vector<int>(3, 2);
    unordered_map<std::vector<int>, int>::iterator itr = clickcombos.find(cmb);
    if (itr == clickcombos.end()) {
        clickcombos[cmb] = 1;
    } else {
        ++clickcombos[cmb];
    }

    return 0;
}