#include <iostream>
#include <cmath>
#include <cassert>
#include <list>
#include <vector>
// #include <algorithm>

namespace // unnamed namespace
{
    class Solver
    {
    public:
        enum BUFFER_INDICES
        {
            INDEX_THREE = 0,
            INDEX_FIVE = 1,
            INDEX_SEVEN = 2,
            INDEX_NUM = 3
        };

        int KthIntPrimeFactors357(int k);

    private:
        void Init();
        void Clear() { buffer_.clear(); }
        std::vector< std::list<int> > buffer_;
    };

    void Solver::Init()
    {
        buffer_.resize(3);
        buffer_[INDEX_THREE].push_back(3);
        buffer_[INDEX_FIVE].push_back(5);
        buffer_[INDEX_SEVEN].push_back(7);
    }

    int Solver::KthIntPrimeFactors357(int k)
    {
        using namespace std;
        assert(k>0);

        Init();

        int num = 0;
        int result = 3; // when k == 1
        while (num < k)
        {
            ++num;
            int int_three = buffer_[INDEX_THREE].front();
            int int_five = buffer_[INDEX_FIVE].front();
            int int_seven = buffer_[INDEX_SEVEN].front();

            result = min(int_three, min(int_five, int_seven));
            assert(result < INT_MAX/7);
            if (result == int_three)
            {
                buffer_[INDEX_THREE].pop_front();
                buffer_[INDEX_THREE].push_back(result*3);
                buffer_[INDEX_FIVE].push_back(result*5);
            } 
            else if (result == int_five)
            {
                buffer_[INDEX_FIVE].pop_front();
                buffer_[INDEX_FIVE].push_back(result*5);
            }
            else // (result == int_seven)
            {
                buffer_[INDEX_SEVEN].pop_front();
            }
            buffer_[INDEX_SEVEN].push_back(result*7);
        }

        Clear();

        return result;
    }

    // const int Solver::buffer[PERIOD] = { 3, 5, 7, 9, 15, 21, 25, 27, 35, 45, 49, 63, 75, 81, 105 };
}

int main(int argc, char** argv)
{
    using namespace std;
    Solver solver;

    // when i==505 then x*7 will be larger then INT_MAX !!!
    for (int i=1; i<505; ++i)
    {
        cout << solver.KthIntPrimeFactors357(i) << "    ";
    }

    return 0;
}