#include <thread>
#include <iostream>

void HelloWorld() {
  std::cout << "Hello world from thread ";
  std::cout << std::this_thread::get_id() << std::endl;
}

int main() {
  std::thread t1(HelloWorld);
  std::thread t2(HelloWorld);
  // even for this simple case interleaving happens!
  t1.join();
  t2.join();

  return 0;
}