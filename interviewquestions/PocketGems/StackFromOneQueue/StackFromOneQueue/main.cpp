#include <iostream>
#include <deque>
#include <queue>

template<typename T>
class StackByQueue {
public:
    bool empty() { return queue_.empty(); }
    typename std::queue<T>::size_type size() { return queue_.size(); }
    T& top() { return queue_.back(); }
    void push(const T& x);
    void pop();

private:
    std::queue<T> queue_;
};

template<typename T>
void StackByQueue<T>::push(const T& x) {
    queue_.push(x);
}

template<typename T>
void StackByQueue<T>::pop() {
    size_t n = queue_.size();
    for (size_t i=0; i<(n-1); ++i) {
        T x = queue_.front();
        queue_.pop();
        queue_.push(x);
    }
    queue_.pop();
}

int main(int argc, char** argv) {
    StackByQueue<int> stack;

    for (int i=0; i<10; ++i) {
        stack.push(i);
    }

    while (!stack.empty()) {
        std::cout << " " << stack.top();
        stack.pop();
    }

    return 0;
}