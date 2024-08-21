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
        std::cout << "**********************\n";
        std::cout << "| Singly Linked list |\n";
        std::cout << "----------------------\n";
        std::cout << "**       Menu       **\n";
        std::cout << "**********************\n";
        std::cout << pushfront << " : Push Front (key)\n";
        std::cout << getfront << " : Get Key Front\n";
        std::cout << popfront << " : Pop Front\n";
        std::cout << "----------------------\n";
        std::cout << pushback << " : Push Back (key)\n";
        std::cout << getback << " : Get Key Back\n";
        std::cout << popback << " : Pop Back\n";
        std::cout << "----------------------\n";
        std::cout << addbefore << " : Add Before (key)\n";
        std::cout << addafter << " : Add After (key)\n";
        std::cout << "----------------------\n";
        std::cout << findkey << " : Check if Key is in List (key)\n";
        std::cout << delkey << " : Delete Key (key)\n";
        std::cout << peekindex << " : Peek (index)\n";
        std::cout << delindex << " : Delete at Index (index)\n";
        std::cout << "----------------------\n";
        std::cout << isempty << " : Check if Empty\n";
        std::cout << getsize << " : Get size of List\n";
        std::cout << printlist << " : Print List\n";
        std::cout << "----------------------\n";
        std::cout << exitprogram << " : Exit Program\n";
        std::cout << "**********************\n";
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
                list.pushFront();
                break;
            case getfront:
                list.getFront();
                break;
            case popfront:
                list.popFront();
                break;
            case pushback:
                list.pushBack();
                break;
            case getback:
                list.getBack();
                break;
            case popback:
                list.popBack();
                break;
            case addbefore:
                list.addBefore();
                break;
            case addafter:
                list.addAfter();
                break;
            case findkey:
                list.findNode();
                break;
            case delkey:
                list.delKey();
                break;
            case peekindex:
                list.peekIndex();
                break;
            case delindex:
                list.delIndex();
                break;
            case isempty:
                list.isEmpty(true);
                break;
            case getsize:
                list.getSize();
                break;
            case printlist:
                list.printList();
                break;
            case exitprogram:
                return 0;
                break;
            default:
                std::cout << "Enter valid option!" << std::endl;
                break;
            }
        }
        std::cout << "\nPress ENTER to continue... " << std::flush;
        _getch();
    }
    return 0;
}