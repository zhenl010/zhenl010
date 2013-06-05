#include <iostream>
#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

namespace {
//////////////////////////////////////////////////////////////////////////

std::unordered_map<std::string, int> pages;

void PageInc(const std::string& url) {
  // simulate a long page fetch
  int mcss = rand();
  std::this_thread::sleep_for(std::chrono::microseconds(mcss));

  std::mutex mutex;
  mutex.lock();
  pages[url] = mcss;
  mutex.unlock();
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  std::thread t1(PageInc, "http://fake_site_0001");
  std::thread t2(PageInc, "http://fake_site_0002");
  t1.join();
  t2.join();

  for (const auto& itr: pages) {
    std::cout << itr.first << " ==> " << itr.second << std::endl;
  }

  return 0;
}