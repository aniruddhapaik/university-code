#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

std::queue<int> buffer;
const int maxsize = 5;
std::mutex mtx;
std::condition_variable notfull;
std::condition_variable notempty;

void produce(int item) {
  std::unique_lock<std::mutex> lock(mtx);
  notfull.wait(lock, [] { return buffer.size() < maxsize; });
  buffer.push(item);
  std::cout << "Produced item: " << item << std::endl;
  lock.unlock();
  notempty.notify_one();
}

void consume() {
  std::unique_lock<std::mutex> lock(mtx);
  notempty.wait(lock, [] { return not buffer.empty(); });
  int item = buffer.front();
  buffer.pop();
  std::cout << "- Consumed item: " << item << std::endl;
  lock.unlock();
  notfull.notify_one();
}

void producer() {
  for (int i = 0; i < 10; ++i) {
   produce(i);
   std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
  }
}

void consumer() {
  for (int i = 0; i < 10; ++i) {
    consume();
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
  }
}

int main() {
  std::thread producerthread(producer);
  std::thread consumerthread(consumer);
  producerthread.join();
  consumerthread.join();
  return 0;
}