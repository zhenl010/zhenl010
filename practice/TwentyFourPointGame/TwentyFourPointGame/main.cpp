#include <iostream>
#include <vector>
#include <string>
#include "expression_tree.h"
#include "int_fraction.h"
#include "game_twenty_four.h"

namespace // unnamed namespace
{
    using namespace std;

}

int main(int argc, char** argv)
{
    using namespace std;
    using namespace augment_data_structure;

    for (int i=1; i<14; ++i) {for (int j=1; j<14; ++j)
    {for (int k=1; k<14; ++k) {for (int l=0; l<14; ++l){
        GameTwentyFour game_test(i, j, k, l);
        if (game_test.IsSolvable())
        {
            cout << game_test.Answer() << endl;
        }
    }}}}

    return 0;
}