#include "../../input_utils.h"
#include <vector>

class CircularQueueWithArray {
private:
	size_t maxsize, front, rear;
	std::vector<int>* queue = nullptr;
	int last_input;

	bool handleInput() {
		std::cin >> this->last_input;
		if (std::cin.fail()) {
			if (std::cin.eof()) { std::cout << "Reached end of input (EOF)" << std::endl; }
			else { std::cout << "Enter valid integer!" << std::endl; }
			clearAndResetInputState();
		} else { return true; }
		return false;
	}

public:
	CircularQueueWithArray(size_t max_size) {
		this->maxsize = max_size;
		this->front = this->rear = -1;
		this->queue = new std::vector<int>;
		this->queue->resize(this->maxsize);
		this->last_input = 0;
	}

	void getFront() const {
		if (not this->isEmpty()) {
			std::cout << "Front: " << this->queue->at(this->front) << std::endl;
		} else { std::cout << "Queue is empty!" << std::endl; }
	}

	void getRear() const {
		if (not this->isEmpty()) {
			std::cout << "Rear: " << this->queue->at(this->rear) << std::endl;
		} else { std::cout << "Queue is empty!" << std::endl; }
	}

	void displayQueue() {
		if (not this->isEmpty()) {
			auto tempfront = this->front;
			std::cout << "Front: " << std::flush;
			while(tempfront != this->rear) {
				std::cout << this->queue->at(tempfront) << " | " ;
				tempfront = (tempfront + 1) % this->maxsize;
			}
			std::cout << this->queue->at(tempfront) << std::endl;
		} else { std::cout << "Queue is empty! Nothing to display" << std::endl; }
	}

	void enQueue() {
		if (this->isEmpty()) {
			std::cout << "Enter key to enqueue: " << std::flush;
			if (this->handleInput()) {
				this->front = this->rear = 0;
				this->queue->at(this->rear) = this->last_input;
			}
		}
		else if (not this->isFull()) {
			std::cout << "Enter key to enqueue: " << std::flush;
			if (this->handleInput()) {
				this->rear = (this->rear + 1) % this->maxsize;
				this->queue->at(this->rear) = this->last_input;
			}	
		} else { std::cout << "Queue is full!" << std::endl; }
	}

	void deQueue() {
		if (not this->isEmpty()) { 
			std::cout << "Dequeuing first element: " <<
										this->queue->at(this->front) << std::endl;
			if (this->front == this->rear) {
				this->front = this->rear = -1;
			} else {
				this->front = (this->front + 1) % this->maxsize;
			}
		} else { std::cout << "Queue is empty!" << std::endl; }
	}

	const bool isEmpty(bool printmessage = false) const { 
		if (this->front == static_cast<size_t>(-1) 
				 and this->rear == static_cast<size_t>(-1)) { 
			if (printmessage) { std::cout << "Queue is empty!" << std::endl; }
			return true; 
		}
		else { 
			if (printmessage) { std::cout << "Queue is not empty." << std::endl; }
			return false;
		}
	}

	const bool isFull(bool printmessage = false) const {
		if ((this->rear + 1) % this->maxsize == this->front) { 
			if (printmessage) { std::cout << "Queue is full!" << std::endl; }	
			return true; 
		}
		else { 
			if (printmessage) { std::cout << "Queue is not full yet." << std::endl; }	
			return false; 
		}
	}
};