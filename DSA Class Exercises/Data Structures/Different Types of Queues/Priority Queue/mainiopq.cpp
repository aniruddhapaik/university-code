//#include "../../input_utils.h"
#include "priorityqueuewitharray.cpp"

enum Menu {enqueue=0, dequeue, frontelement, displayqueue, exitprogram};

bool handleInput(short int& choice) {
	std::cin >> choice;
	if (std::cin.fail()) {
		if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." << std::endl; }
		else { std::cout << "Enter valid integer!" << std::endl; }
		clearAndResetInputState();
		return false;
	} else { return true; }
}

void printMenu() {
	short int choice;
	PriorityQueueWithArray<int> queue;
	
	while(1) {
		system("cls");
		std::cout << "** Priority Queue with Array **\n";
		std::cout << "---- (Ascending order priority)\n";
		std::cout << "- (e.g.: 1 -> highest priority)\n";
		std::cout << "-- Menu -----------------------\n";
		std::cout << enqueue << " . Enqueue (value, priority)\n";
		std::cout << dequeue << " . Dequeue\n";
		std::cout << "-------------------------------\n";
		std::cout << frontelement << " . Front element\n";
		std::cout << displayqueue << " . Display queue\n";
		std::cout << "-------------------------------\n";
		std::cout << exitprogram << " . Exit program\n";
		std::cout << "-------------------------------\n\n";
		std::cout << "Enter choice: " << std::flush;
		
		if (handleInput(choice)) {
			switch (choice) {
				case enqueue:
					queue.enQueue();
					break;
				case dequeue:
					queue.deQueue();
					break;
				case frontelement:
					queue.frontElement();
					break;
				case displayqueue:
					queue.displayQueue();
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
	printMenu();

	return 0;
}