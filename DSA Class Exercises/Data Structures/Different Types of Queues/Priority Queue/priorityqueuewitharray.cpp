#include "../../input_utils.h"
#include <vector>
#include <string>

template<typename T>
struct Node_t {
	T value;
	T priority;

	Node_t(T val, T prty) {
		value = val;
		priority = prty;
	}
};

namespace priorityqueue {
	typedef Node_t<int> Node;
}

using namespace priorityqueue;

template <typename T>
std::ostream& operator<< (std::ostream& COUT, const Node_t<T>& node) {
	COUT << node.value << " (p: " << node.priority << ") ";
	return COUT;
}

template <typename T>
std::ostream& operator<< (std::ostream& COUT, const std::vector<T>& nodelist) {
	size_t counter{nodelist.size()-1};
	std::cout << "Queue element (with their priorities):\nTop-> ";
	while (counter > 0 and counter < nodelist.size()) {
		std::cout << nodelist.at(counter) << "| ";
		counter--;
	}
	std::cout << nodelist.at(counter) << std::flush;
	return COUT;
}

class PriorityQueueWithArray {
private:
	
	std::vector<Node>* queue = nullptr;
	int last_input;

	bool handleInput() {
		std::cin >> this->last_input;
		if (std::cin.fail()) {
			if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
			else { std::cout << "Enter valid integer!" << std::endl; }
			clearAndResetInputState();
			return false;
		} else { return true; }
	}

	void push(Node* temp_node) {
		if (this->queue->empty()) { this->queue->push_back(*temp_node); }
		else {
			size_t counter{0};
			while(counter < this->queue->size()) {
				if (temp_node->priority < this->queue->at(counter).priority) { counter++; } 
				else if (temp_node->priority >= this->queue->at(counter).priority) {
					this->queue->emplace(this->queue->begin()+counter, *temp_node);
					break;
				}
			}
			if (counter == this->queue->size()) { this->queue->push_back(*temp_node); }
		}
	}

public:
	PriorityQueueWithArray() {
		this->queue = new std::vector<Node>;
		this->last_input = 0;
	}

	void enQueue() {
		int temp_element{}, temp_priority{};

		std::cout << "Enter element only: " << std::flush;
		if (this->handleInput()) { temp_element = this->last_input; }
		else { return; }

		std::cout << "Enter priority for element (" << temp_element << ") only: " << std::flush;
		if (this->handleInput()) { temp_priority = this->last_input; }
		else { return; }

		this->push(new Node(temp_element, temp_priority));
	}

	friend std::ostream& operator<< (std::ostream&, const Node&);

	void deQueue() {
		if (this->queue->empty()) { std::cout << "Queue is empty! can't dequeue" << std::endl; }
		else {
			std::cout << "Dequeuing: " << this->queue->back();
			this->queue->pop_back(); 
		}
	}

	const void topElement() const {
		if (this->queue->empty()) { std::cout << "Queue is emtpy!" << std::endl; }
		else { 
			Node tempnode = this->queue->back();
			std::cout << "Displaying Top Element:\n";
			std::cout << this->queue->back();
		}
	}

	template <typename T>
	friend std::ostream& operator<< (std::ostream&, const std::vector<T>&);

	const void displayQueue() const {
		if (this->queue->empty()) { std::cout << "Queue is emtpy!" << std::endl; }
		else {
			std::cout << *(this->queue);
		}
	}
};