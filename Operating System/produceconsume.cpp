#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

class Buffer {
private:
    std::queue<int> queue;
    const int max_size;
    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

public:
    Buffer(int size) : max_size(size) {}

    void produce(int item) {
        std::unique_lock<std::mutex> lock(mtx);
        not_full.wait(lock, [this] { return queue.size() < max_size; });
        
        queue.push(item);
        std::cout << "Produced: " << item << std::endl;
        
        lock.unlock();
        not_empty.notify_one();
    }

    int consume() {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, [this] { return !queue.empty(); });
        
        int item = queue.front();
        queue.pop();
        std::cout << "Consumed: " << item << std::endl;
        
        lock.unlock();
        not_full.notify_one();
        return item;
    }
};

void producer(Buffer& buffer, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    
    for (int i = 0; i < count; ++i) {
        buffer.produce(distrib(gen));
        std::this_thread::sleep_for(std::chrono::milliseconds(50 + distrib(gen) % 100));
    }
}

void consumer(Buffer& buffer, int count) {
    for (int i = 0; i < count; ++i) {
        buffer.consume();
        std::this_thread::sleep_for(std::chrono::milliseconds(100 + (i % 100)));
    }
}

int main() {
    Buffer buffer(5);  // Buffer with capacity 5
    int items_to_produce = 20;
    
    std::thread producer_thread(producer, std::ref(buffer), items_to_produce);
    std::thread consumer_thread(consumer, std::ref(buffer), items_to_produce);
    
    producer_thread.join();
    consumer_thread.join();
    
    return 0;
}