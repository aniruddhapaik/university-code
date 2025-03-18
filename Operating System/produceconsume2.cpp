#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

class Buffer {
 private:
  std::queue<int> queue;
  const int max_size;
  std::mutex mtx;
  std::condition_variable not_full;
  std::condition_variable not_empty;
  std::chrono::time_point<std::chrono::steady_clock> starttime;

 public:
  Buffer(int size, std::chrono::time_point<std::chrono::steady_clock> starttime)
      : max_size(size), starttime(starttime) {}

  void produce(int item) {
    std::unique_lock<std::mutex> lock(mtx);
    not_full.wait(lock, [this] { return queue.size() < max_size; });

    queue.push(item);
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - starttime)
            .count();
    std::cout << std::string("[T+" + std::to_string(elapsed) + "ms]" +
                             " + Produced: " + std::to_string(item))
              << std::endl;

    lock.unlock();
    not_empty.notify_one();
  }

  int consume() {
    std::unique_lock<std::mutex> lock(mtx);
    not_empty.wait(lock, [this] { return !queue.empty(); });

    int item = queue.front();
    queue.pop();
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - starttime)
            .count();
    std::cout << std::string("[T+" + std::to_string(elapsed) + "ms]" +
                             " - Consumed: " + std::to_string(item))
              << std::endl;

    lock.unlock();
    not_full.notify_one();
    return item;
  }
};

void producer(Buffer &buffer, int count) {
  for (int i = 0; i < count; ++i) {
    buffer.produce(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void consumer(Buffer &buffer, int count) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(150, 500);

  for (int i = 0; i < count; ++i) {
    buffer.consume();
    int sleeptime = dis(gen);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    std::cout << std::string("Resuming after " + std::to_string(sleeptime) +
                             "ms ");
  }
}

int main() {
  auto starttime = std::chrono::steady_clock::now();
  Buffer buffer(5, starttime);  // Buffer with capacity 5
  int items_to_produce = 20;

  std::thread producer_thread(producer, std::ref(buffer), items_to_produce);
  std::thread consumer_thread(consumer, std::ref(buffer), items_to_produce);

  producer_thread.join();
  consumer_thread.join();

  return 0;
}
