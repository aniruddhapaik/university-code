#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::queue<int> buffer;
const unsigned int max_size = 5;
std::mutex mtx;
std::condition_variable not_full;
std::condition_variable not_empty;

void produce(int item) {
  std::unique_lock<std::mutex> lock(mtx);
  not_full.wait(lock, [] { return buffer.size() < max_size; });

  buffer.push(item);
  std::cout << "Produced: " << item << std::endl;

  lock.unlock();
  not_empty.notify_one();
}

void consume() {
  std::unique_lock<std::mutex> lock(mtx);
  not_empty.wait(lock, [] { return !buffer.empty(); });

  int item = buffer.front();
  buffer.pop();
  std::cout << "- Consumed: " << item << std::endl;

  lock.unlock();
  not_full.notify_one();
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
  std::thread producer_thread(producer);
  std::thread consumer_thread(consumer);

  producer_thread.join();
  consumer_thread.join();

  return 0;
}