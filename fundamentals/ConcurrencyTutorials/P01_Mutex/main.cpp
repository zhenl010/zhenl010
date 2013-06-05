#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

namespace {
//////////////////////////////////////////////////////////////////////////

class Counter {
public:
  Counter() { Reset(); }
  void Reset() { cnt_ = 0; }
  int Cnt() { return cnt_; }
  void Inc() {
    mutex_.lock();
    ++cnt_;
    mutex_.unlock();
  }

private:
  std::mutex mutex_;
  int cnt_;
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Counter counter;

  std::vector<std::thread> threads;
  for (int i=0; i<8; ++i) {
    threads.push_back(std::thread([&counter]() {
      for (int j=0; j<10000; ++j) {
        counter.Inc();
      }
    } ));
  }

  for (auto& th: threads) {
    th.join();
  }

  std::cout << counter.Cnt() << std::endl;

  return 0;
}