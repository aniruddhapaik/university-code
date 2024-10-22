//#include "../../input_utils.h"
#include "circularqueuewitharray.cpp"

enum Menu {getfront=0, getrear, displayqueue, enqueue, 
					 dequeue, isempty, isfull, exitprogram};

template <typename T>
bool handleInput(T& choice) {
	std::cin >> choice;
	if (std::cin.fail()) {
		if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
		else { std::cout << "Enter valid input!" << std::endl; }
		clearAndResetInputState();
		return false;
	} else { return true; }
}

void printMenu(size_t& size_of_array) {
	short int choice;
	CircularQueueWithArray circular_queue(size_of_array);

	while(1) {
		system("cls");
		std::cout << "** Circular Queue with Array **\n";
		std::cout << "-- Menu -----------------------\n";
		std::cout << getfront << " . Get Front\n";
		std::cout << getrear << " . Get Rear\n";
		std::cout << displayqueue << " . Display Queue\n";
		std::cout << "-------------------------------\n";
		std::cout << enqueue << " . Enequeue\n";
		std::cout << dequeue << " . Dequeue\n";
		std::cout << "-------------------------------\n";
		std::cout << isempty << " . Check if Empty\n";
		std::cout << isfull << " . Check if Full\n";
		std::cout << "-------------------------------\n";
		std::cout << exitprogram << " . Exit Program\n\n";
		std::cout << "Enter choice: " << std::flush;

		if (handleInput(choice)) {
			switch (choice) {
				case getfront:
					circular_queue.getFront();
					break;
				case getrear:
					circular_queue.getRear();
					break;
				case displayqueue:
					circular_queue.displayQueue();
					break;
				case enqueue:
					circular_queue.enQueue();
					break;
				case dequeue:
					circular_queue.deQueue();
					break;
				case isempty:
					circular_queue.isEmpty(true);
					break;
				case isfull:
					circular_queue.isFull(true);
					break;
				case exitprogram:
					return;
				default:
					std::cout << "Enter valid choice!" << std::endl;
			}
		}

		_getch();
	}
}

int main() {
	size_t size_of_array;
	std::cout << "Enter the max size of the queue: " << std::flush;
	if (handleInput(size_of_array)) {
		printMenu(size_of_array);
	}

	return 0;
}