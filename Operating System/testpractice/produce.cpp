#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

const int maxsize = 5;
std::mutex mtx;
std::queue<int> buffer;
std::condition_variable notempty;
std::condition_variable notfull;

void produce(int item) {
  std::unique_lock<std::mutex> lock(mtx);
  notfull.wait(lock, [] { return buffer.size() < maxsize; });
  buffer.push(item);
  std::cout << "Produced item " << item << std::endl;
  lock.unlock();
  notempty.notify_one();
}

void consume() {
  std::unique_lock<std::mutex> lock(mtx);
  notempty.wait(lock, [] { return buffer.size() > 0; });
  int item = buffer.front();
  buffer.pop();
  std::cout << "- Consumed item " << item << std::endl;
  lock.unlock();
  notfull.notify_one();
}

void producer() {
  for (int i = 0; i < 10; i++) {
    produce(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void consumer() {
  for (int j = 0; j < 10; j++) {
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