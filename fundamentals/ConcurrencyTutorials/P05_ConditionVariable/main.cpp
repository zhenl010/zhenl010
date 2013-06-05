#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace {
//////////////////////////////////////////////////////////////////////////

template<typename T>
class ConcurrentQueue {
private:
  unsigned int capacity_;
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable not_full_;
  std::condition_variable not_empty_;

public:
  ConcurrentQueue(int capacity): capacity_(capacity) {}

  void Deposit(int val) {
    std::unique_lock<std::mutex> lck(mutex_);

    not_full_.wait(lck, [this](){
      return this->queue_.size() < this->capacity_;
    });

    queue_.push(val);

    not_empty_.notify_one();
  }

  T Fetch() {
    std::unique_lock<std::mutex> lck(mutex_);

    not_empty_.wait(lck, [this]() {
      return 0 < this->queue_.size();
    });

    T t = queue_.front();
    queue_.pop();

    not_full_.notify_one();
    return t;
  }

  int Size() {
    std::lock_guard<std::mutex> lck(mutex_);
    return queue_.size();
  }
};

void RandWait(int ms_max) {
  typedef std::chrono::milliseconds milliseconds;
  unsigned int ms = 1 + rand() % ms_max;
  std::this_thread::sleep_for(milliseconds(ms));
}

void Producer(int id, ConcurrentQueue<int>& queue) {
  while (true) {
    RandWait(2000);
    int i = rand();
    queue.Deposit(i);
    std::cout << "Producer " << id << " produced " << i << std::endl;
  }
}

void Consumer(int id, ConcurrentQueue<int>& queue) {
  while (true) {
    RandWait(50);
    int product = queue.Fetch();
    std::cout << "Consumer " << id << " fetched " << product << std::endl;
  }
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int consumer_num = 100;
  int producer_num = 4;
  const int kCapacity = 20;
  ConcurrentQueue<int> queue(kCapacity);

  std::vector<std::thread> consumer_threads;
  for (int i=0; i<consumer_num; ++i) {
    consumer_threads.push_back(std::thread(Consumer, i, std::ref(queue)));
  }

  std::vector<std::thread> producer_threads;
  for (int i=0; i<producer_num; ++i) {
    producer_threads.push_back(std::thread(Producer, i, std::ref(queue)));
  }

  for (int i=0; i<consumer_num; ++i) { consumer_threads[i].join(); }
  for (int i=0; i<producer_num; ++i) { producer_threads[i].join(); }

  return 0;
}