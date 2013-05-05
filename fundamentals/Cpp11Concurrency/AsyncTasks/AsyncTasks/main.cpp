#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

int main() {
    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

    std::vector<std::future<void>> futures;
    for (int i=0; i<10; ++i)
    {
        auto fut = std::async([]
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << std::this_thread::get_id() << " ";
        });
        futures.push_back(std::move(fut));
    }

    // for (auto &fut: futures)
    // {
    //     fut.wait();
    // }

    std::cout << std::endl;

    return 0;
}