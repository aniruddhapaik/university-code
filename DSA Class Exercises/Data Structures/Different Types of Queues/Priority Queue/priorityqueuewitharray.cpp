#include "../../input_utils.h"
#include <vector>

struct Node {
	int value;
	int priority;

	Node(int val, int prty) {
		value = val;
		priority = prty;
	}
};

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
		//if ()
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

	void deQueue() {
		if (this->queue->empty()) { std::cout << "Queue is empty! can't dequeue" << std::endl; }
		else { this->queue->pop_back(); }
	}

	const void topElement() const {
		if (this->queue->empty()) { std::cout << "Queue is emtpy!" << std::endl; }
		else { 
			Node tempnode = *(this->queue->end());
			std::cout << "Value: " << tempnode.value \
							  << "Priority: " << tempnode.priority << std::endl; 
		}
	}

	const void displayQueue() const {
		if (this->queue->empty()) { std::cout << "Queue is emtpy!" << std::endl; }
		else {
			size_t counter{this->queue->size()-1};
			std::cout << "Queue element (with their priorities): " << std::endl;
			while (counter > 0) {
				std::cout << this->queue->at(counter).value <<\
					    '(' << this->queue->at(counter).priority << ") | ";
				counter--;
			}
			std::cout << this->queue->at(counter).value <<\
					    '(' << this->queue->at(counter).priority << ")";
		}
	}
};