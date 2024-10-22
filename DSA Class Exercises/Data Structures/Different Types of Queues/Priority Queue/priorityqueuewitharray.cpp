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

namespace intnode_namespace {
	typedef Node_t<int> Node;
}

using namespace intnode_namespace;

template <typename T>
std::ostream& operator<< (std::ostream& COUT, const Node_t<T>& node) {
	COUT << node.value << " (p: " << node.priority << ") ";
	return COUT;
}

template <typename T>
std::ostream& operator<< (std::ostream& COUT, const std::vector<T>& nodelist) {
	size_t counter{nodelist.size()-1};
	std::cout << "Queue element (with their priorities):\nFront-> ";
	while (counter > 0 and counter < nodelist.size()) {
		std::cout << nodelist.at(counter) << "| ";
		counter--;
	}
	std::cout << nodelist.at(counter) << std::flush;
	return COUT;
}

template <typename T>
class PriorityQueueWithArray {
private:
	
	std::vector<Node>* queue = nullptr;
	T last_input;

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
		T temp_element{}, temp_priority{};

		std::cout << "Enter element only: " << std::flush;
		if (this->handleInput()) { temp_element = this->last_input; }
		else { return; }

		std::cout << "Enter priority for element (" << \
			temp_element << ") only: " << std::flush;
		if (this->handleInput()) { temp_priority = this->last_input; }
		else { return; }

		this->push(new Node(temp_element, temp_priority));
	}

	friend std::ostream& operator<< (std::ostream& COUT, const Node_t<T>& node);

	void deQueue() {
		if (this->queue->empty()) { 
			std::cout << "Queue is empty! can't dequeue" << std::endl; 
		}
		else {
			std::cout << "Dequeuing: " << this->queue->back();
			this->queue->pop_back(); 
		}
	}

	const void frontElement() const {
		if (this->queue->empty()) { std::cout << "Queue is emtpy!" << std::endl; }
		else { 
			Node tempnode = this->queue->back();
			std::cout << "Displaying Front Element:\n";
			std::cout << this->queue->back();
		}
	}

	friend std::ostream& operator<< (std::ostream&, const std::vector<T>&);

	const void displayQueue() const {
		if (this->queue->empty()) { std::cout << "Queue is emtpy!" << std::endl; }
		else {
			std::cout << *(this->queue);
		}
	}
};