#include <cassert>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

//////////////////////////////////////////////////////////////////////////
}

// void threadFun()
// {
//     std::cout << "Hi from thread!\n";
// }
// std::thread th( &threadFun );
// std::thread th( []()
// {
//     std::cout << "Hi from thread!\n";
// });

void thFunc(int i)
{
    std::cout << "Hi from thread " << i << "!\n";
}

int main()
{
    std::vector<std::thread> workers;
    for (int i=0; i<8; ++i)
    {
        auto th = std::thread(&thFunc, i);
        workers.push_back(std::move(th));
        assert(!th.joinable());
    }

    std::cout << "Hi from main!\n";
    // std::for_each(workers.begin(), workers.end(), [](std::thread &th)
    // {
    //     th.join();
    // });
    for (std::thread &th : workers)
    {
        assert(th.joinable());
        th.join();
    }

    return 0;
}