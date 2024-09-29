#include "queuepractice.h"

Queue::Queue() { this->queue = new std::vector<int>; }

void Queue::enQueue(int key) { this->queue->push_back(key); }

void Queue::deQueue() {
  if (this->queue->size()) {
    std::cout << "Deqeueing: " << this->queue->at( 0 ) << std::endl;
    this->queue->erase( this->queue->begin() );
    return;
  }
  std::cout << "Queue is empty!" << std::endl;
}

const void Queue::empty() const {
  if (this->queue->size()) {
    std::cout << "Queue is not empty." << std::endl;
    return;
  }
  std::cout << "Queue is empty!" << std::endl;
}

const void Queue::size() const {
  if (this->queue->size()) {
    std::cout << "Queue Size: " << this->queue->size() << std::endl;
    return;
  }
  std::cout << "Queue is empty!" << std::endl;
}

const void Queue::front() const {
  if (this->queue->size()) {
    std::cout << "Front: " << this->queue->at( 0 ) << std::endl;
    return;
  }
  std::cout << "Queue is empty!" << std::endl;
}

const void Queue::printQueue() const {
  if (this->queue->size()) {
    std::cout << "Front -> ";
    for (auto& i : *(this->queue)) {
      std::cout << i << " | ";
    }
    std::cout << std::endl;
    return;
  } 
  std::cout << "Queue is empty!" << std::endl;
}

std::ostream& operator<< (std::ostream& COUT, const Queue& queue) {
  queue.printQueue();
  return COUT;
}