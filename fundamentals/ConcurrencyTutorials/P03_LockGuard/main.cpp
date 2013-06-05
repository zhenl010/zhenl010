#include <iostream>
#include <thread>
#include <mutex>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

struct Counter {
  int val;

  Counter(): val(0) {}
  void Inc() { ++val; }
  void Dec() { val = 0<val ? --val : 0; }
};

struct ConcurrentCounter {
  Counter counter;
  std::mutex mutex;

  void Inc() {
    std::lock_guard<std::mutex> guard(mutex);
    counter.Inc();
  }

  void Dec() {
    std::lock_guard<std::mutex> guard(mutex);
    counter.Inc();
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {

  return 0;
}