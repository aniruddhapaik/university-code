#include "singlylinkedlist.cpp"
#include <conio.h>

enum menu {pushfront, getfront, popfront, pushback, getback, popback, \
           addbefore, addafter, findkey, delkey, peekindex, delindex, \
           isempty, getsize, printlist, exitprogram};

int main() {
    SinglyLinkedList list;
    int input{};

    while(1) {
        system("cls");
        std::cout << "Singly Linked list\n";
        std::cout << "Menu:\n";
        std::cout << pushfront << " : Push Front (key)\n";
        std::cout << getfront << " : Get Key Front\n";
        std::cout << popfront << " : Pop Front\n";
        std::cout << pushback << " : Push Back (key)\n";
        std::cout << getback << " : Get Key Back\n";
        std::cout << popback << " : Pop Back\n";
        std::cout << addbefore << " : Add Before (key)\n";
        std::cout << addafter << " : Add After (key)\n";
        std::cout << findkey << " : Check if Key is in List (key)\n";
        std::cout << delkey << " : Delete Key (key)\n";
        std::cout << peekindex << " : Peek (index)\n";
        std::cout << delindex << " : Delete at Index (index)\n";
        std::cout << isempty << " : Check if Empty\n";
        std::cout << getsize << " : Get size of List\n";
        std::cout << printlist << " : Print List\n";
        std::cout << exitprogram << " : Exit Program\n";
        std::cout << "\nEnter menu choice >> " << std::flush;

        std::cin >> input;
        
        if (std::cin.fail()){
            clearAndResetInputState();
            if (std::cin.eof()) {
                std::cout << "Reached end of input (EOF)." << std::endl;
            } else {
                std::cout << "Error: Invalid Input! Enter valid integer." << std::endl;
            }
        }
        else {
            switch (input) {
            case pushfront:
                break;
            case getfront:
                break;
            case popfront:
                break;
            case pushback:
                break;
            case getback:
                break;
            case popback:
                break;
            case addbefore:
                break;
            case addafter:
                break;
            case findkey:
                break;
            case delkey:
                break;
            case peekindex:
                break;
            case delindex:
                break;
            case isempty:
                break;
            case getsize:
                break;
            case printlist:
                break;
            case exitprogram:
                return 0;
                break;
            default:
                std::cout << "Enter valid option!" << std::endl;
                break;
            }
        }
        _getch();
    }
    return 0;
}