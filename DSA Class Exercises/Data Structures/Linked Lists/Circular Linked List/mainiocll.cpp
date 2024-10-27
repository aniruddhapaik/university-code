#include "../../input_utils.h"
#include "circularlinkedlist.cpp"

enum Menu {
  pushfront = 0,
  pushback,
  pushafter,
  deletekey,
  listsize,
  displaylist,
  exitprogram
};

bool handleInput(short int& choice) {
  std::cin >> choice;
  if (std::cin.fail()) {
    if (std::cin.eof()) {
      std::cout << "Reached end of input (EOF)." << std::endl;
    } else {
      std::cout << "Error: Enter valid integer!" << std::endl;
    }
    clearAndResetInputState();
  } else {
    return true;
  }
  return false;
}

void printMenu() {
  short int choice{};
  CircularLinkedList list;
  while (1) {
    system("cls");
    std::cout << "** Circular Linked List **\n";
    std::cout << "-- Menu ------------------\n";
    std::cout << pushfront << " . Push Front (key)\n";
    std::cout << pushback << " . Push Back (key)\n";
    std::cout << pushafter << " . Push After (key)\n";
    std::cout << "--------------------------\n";
    std::cout << deletekey << " . Delete (key)\n";
    std::cout << "--------------------------\n";
    std::cout << listsize << " . List Size\n";
    std::cout << displaylist << " . Display List\n";
    std::cout << "--------------------------\n";
    std::cout << exitprogram << " . Exit Program\n";
    std::cout << "** -------------------- **\n\n";
    std::cout << "Enter choice: " << std::flush;

    if (handleInput(choice)) {
      switch (choice) {
        case pushfront:
          list.pushFront();
          break;
        case pushback:
          list.pushBack();
          break;
        case pushafter:
          list.pushAfter();
          break;
        case deletekey:
          list.deleteKey();
          break;
        case listsize:
          list.getListSize();
          break;
        case displaylist:
          list.displayList();
          break;
        case exitprogram:
          return;
        default:
          std::cout << "Choose valid option!" << std::endl;
      }
    }
    _getch();
  }
}

int main() {
  printMenu();

  return 0;
}