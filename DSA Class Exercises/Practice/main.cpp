// #include <iostream>
// #include <vector>
// #include <conio.h>
// #include "fibsearchpractice.h"
//
// int main() {
//   std::vector<int> sortedarr {1,2,3,4,5,6,7,8,9,10, 11, 12, 13, 14, 15};
//
//   FibonacciSearch& fibsearch = FibonacciSearch::get();
//   fibsearch.setArray(&sortedarr);
//
//     int key{};
//     while(1) {
//         system("cls");
//         std::cout << "Fibonacci Search\nPress CTRL+C to quit" << std::endl;
//         std::cout << "Enter a value to search in array: ";
//         if (std::cin >> key) {
//           fibsearch.setTerm(key);
//         } else {
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
//             '\n'); std::cout << "Enter a valid number!" << std::endl;
//         }
//         _getch();
//     }
//
//     return 0;
// }

#include "KnapSack.h"

int main() {
  // Knapsack algorithm
  std::vector<std::pair<float, float>> items = {
    {2, 10}, {3, 5}, {5, 15}, {7, 7}, {1, 6}, {4, 18}, {1, 3}
  };

  float maxcapacity = 15;

  KnapSack sack;
  sack.getItemList(maxcapacity, items);
}

// #include "binsearchpractice.h"
// #include "linsearchpractice.h"
// #include "fibsearchpractice.h"
// #include "stackpractice.h"
// #include "queuepractice.h"
// #include "matchingbracketpractice.h"
// #include <iostream>
// #include <vector>
// #include <limits>
// #include <conio.h>
// #include <string>
// #include "KnapSack.h"
// #include <utility>
// #include "Dijkstra.h"
//
// void clearAndResetInput() {
//   std::cin.clear();
//   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
// }
//
// bool handleInput(int& choice) {
//   std::cin >> choice;
//   if (std::cin.fail()) {
//     if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." <<
//     std::endl; } else { std::cout << "Enter valid integer!" << std::endl; }
//     clearAndResetInput();
//     return false;
//   }
//   return true;
// }
//
// namespace StackMenu {
//   enum stackmenu {push, top, pop, empty, size, printstack, exitprogram};
// }
//
// namespace QueueMenu {
//   enum queuemenu {enqueue, front, dequeue, empty, size, printqueue,
//   exitprogram};
// }
//
// void stackMenu() {
//   using namespace StackMenu;
//   Stack stack;
//   int choice {};
//
//   while (true) {
//     system( "cls" );
//     std::cout << "Stack Menu ---\n";
//     std::cout << "0. Push\n";
//     std::cout << "1. Top\n";
//     std::cout << "2. Pop\n";
//     std::cout << "3. Check If Empty\n";
//     std::cout << "4. Size\n";
//     std::cout << "5. Print Stack\n";
//     std::cout << "6. Exit\n";
//     std::cout << "-------------\n";
//     std::cout << "Enter choice: " << std::flush;
//
//     if (handleInput(choice)) {
//       int key = 0;
//       switch(choice) {
//         case stackmenu::push:
//           std::cout << "Enter key to push: " << std::flush;
//           if (handleInput(key)) { stack.push(key); }
//           break;
//         case stackmenu::top:
//           stack.top();
//           break;
//         case stackmenu::pop:
//           stack.pop();
//           break;
//         case stackmenu::empty:
//           stack.empty();
//           break;
//         case stackmenu::size:
//           stack.size();
//           break;
//         case stackmenu::printstack:
//           std::cout << stack;
//           break;
//         case stackmenu::exitprogram:
//           return;
//         default:
//           std::cout << "Enter valid choice!" << std::endl;
//       }
//     }
//     _getch();
//   }
// }
//
// void queueMenu() {
//   using namespace QueueMenu;
//   Queue queue;
//   int choice {};
//
//   while (true) {
//     system( "cls" );
//     std::cout << "Queue Menu ---\n";
//     std::cout << "0. Enqueue\n";
//     std::cout << "1. Front\n";
//     std::cout << "2. Dequeue\n";
//     std::cout << "3. Check if empty\n";
//     std::cout << "4. Size of Queue\n";
//     std::cout << "5. Print queue\n";
//     std::cout << "6. Exit program\n";
//     std::cout << "-----------------\n";
//     std::cout << "Enter choice: " << std::flush;
//
//     if (handleInput( choice )) {
//       int key {};
//       switch (choice) {
//         case queuemenu::enqueue:
//           std::cout << "Enter key: " << std::flush;
//           if (handleInput( key )) { queue.enQueue(key); }
//           break;
//         case queuemenu::front:
//           queue.front();
//           break;
//         case queuemenu::dequeue:
//           queue.deQueue();
//           break;
//         case queuemenu::empty:
//           queue.empty();
//           break;
//         case queuemenu::size:
//           queue.size();
//           break;
//         case queuemenu::printqueue:
//           std::cout << queue;
//           break;
//         case queuemenu::exitprogram:
//           return;
//         default:
//           std::cout << "Enter valid choice!" << std::endl;
//       }
//     }
//     _getch();
//   }
// }

// int main() {
// queueMenu();

// MatchingBracket& matcher = MatchingBracket::get();

// std::string str1("()(())[][{{}}]");
// std::string str2("()(())[[{{}}]");
// std::string str3("()())[[{}}]");

// matcher.setString(&str3);
// matcher.match();

// Knapsack algorithm
/*std::vector<std::pair<float, float>> items = {
  {2, 10}, {3, 5}, {5, 15}, {7, 7}, {1, 6}, {4, 18}, {1, 3}
};

float maxcapacity = 15;

KnapSack sack;
sack.getItemList(maxcapacity, items);*/

// Dijkstra's algorithm
//  std::vector<std::vector<int>> dijkstrasadjmatrix {
//    {0, 2, 4, 0, 0, 0},
//    {0, 0, 1, 7, 0, 0},
//    {0, 0, 0, 0, 3, 0},
//    {0, 0, 0, 0, 0, 1},
//    {0, 0, 0, 2, 0, 5},
//    {0, 0, 0, 0, 0, 0}
//  };
//
//  Dijkstra dijalgo;
//  dijalgo.getAdjMatrix(dijkstrasadjmatrix);
//  dijalgo.setSource(1); // 1 to n
//
//  return 0;
//}

// #include "binsearchpractice.h"
// #include "linsearchpractice.h"
// #include "fibsearchpractice.h"
// #include "stackpractice.h"
// #include "queuepractice.h"
// #include "matchingbracketpractice.h"
// #include <iostream>
// #include <vector>
// #include <limits>
// #include <conio.h>
// #include <string>
// #include "KnapSack.h"
// #include <utility>
// #include "Dijkstra.h"
//
// void clearAndResetInput() {
//   std::cin.clear();
//   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
// }
//
// bool handleInput(int& choice) {
//   std::cin >> choice;
//   if (std::cin.fail()) {
//     if (std::cin.eof()) { std::cout << "Reached end of input (EOF)." <<
//     std::endl; } else { std::cout << "Enter valid integer!" << std::endl; }
//     clearAndResetInput();
//     return false;
//   }
//   return true;
// }
//
// namespace StackMenu {
//   enum stackmenu {push, top, pop, empty, size, printstack, exitprogram};
// }
//
// namespace QueueMenu {
//   enum queuemenu {enqueue, front, dequeue, empty, size, printqueue,
//   exitprogram};
// }
//
// void stackMenu() {
//   using namespace StackMenu;
//   Stack stack;
//   int choice {};
//
//   while (true) {
//     system( "cls" );
//     std::cout << "Stack Menu ---\n";
//     std::cout << "0. Push\n";
//     std::cout << "1. Top\n";
//     std::cout << "2. Pop\n";
//     std::cout << "3. Check If Empty\n";
//     std::cout << "4. Size\n";
//     std::cout << "5. Print Stack\n";
//     std::cout << "6. Exit\n";
//     std::cout << "-------------\n";
//     std::cout << "Enter choice: " << std::flush;
//
//     if (handleInput(choice)) {
//       int key = 0;
//       switch(choice) {
//         case stackmenu::push:
//           std::cout << "Enter key to push: " << std::flush;
//           if (handleInput(key)) { stack.push(key); }
//           break;
//         case stackmenu::top:
//           stack.top();
//           break;
//         case stackmenu::pop:
//           stack.pop();
//           break;
//         case stackmenu::empty:
//           stack.empty();
//           break;
//         case stackmenu::size:
//           stack.size();
//           break;
//         case stackmenu::printstack:
//           std::cout << stack;
//           break;
//         case stackmenu::exitprogram:
//           return;
//         default:
//           std::cout << "Enter valid choice!" << std::endl;
//       }
//     }
//     _getch();
//   }
// }
//
// void queueMenu() {
//   using namespace QueueMenu;
//   Queue queue;
//   int choice {};
//
//   while (true) {
//     system( "cls" );
//     std::cout << "Queue Menu ---\n";
//     std::cout << "0. Enqueue\n";
//     std::cout << "1. Front\n";
//     std::cout << "2. Dequeue\n";
//     std::cout << "3. Check if empty\n";
//     std::cout << "4. Size of Queue\n";
//     std::cout << "5. Print queue\n";
//     std::cout << "6. Exit program\n";
//     std::cout << "-----------------\n";
//     std::cout << "Enter choice: " << std::flush;
//
//     if (handleInput( choice )) {
//       int key {};
//       switch (choice) {
//         case queuemenu::enqueue:
//           std::cout << "Enter key: " << std::flush;
//           if (handleInput( key )) { queue.enQueue(key); }
//           break;
//         case queuemenu::front:
//           queue.front();
//           break;
//         case queuemenu::dequeue:
//           queue.deQueue();
//           break;
//         case queuemenu::empty:
//           queue.empty();
//           break;
//         case queuemenu::size:
//           queue.size();
//           break;
//         case queuemenu::printqueue:
//           std::cout << queue;
//           break;
//         case queuemenu::exitprogram:
//           return;
//         default:
//           std::cout << "Enter valid choice!" << std::endl;
//       }
//     }
//     _getch();
//   }
// }
//
// int main() {
//   std::vector<int> sortedarr {1,2,3,4,5,6,7,8,9,10, 11, 12, 13, 14, 15};

// BinarySearch& binsearch = BinarySearch::get();
// binsearch.setArray(&sortedarr);
// std::cout << "\nBinary Search -----\n";
// binsearch.setTerm(10);

// LinearSearch& linsearch = LinearSearch::get();
// linsearch.setArray(&sortedarr);
// std::cout << "\nLinear Search -----\n";
// linsearch.setTerm(5);

// FibonacciSearch& fibsearch = FibonacciSearch::get();
// fibsearch.setArray(&sortedarr);
// std::cout << "\nFibonacci Search -----\n";
// fibsearch.setTerm(12);

// stackMenu();

// queueMenu();

// MatchingBracket& matcher = MatchingBracket::get();

// std::string str1("()(())[][{{}}]");
// std::string str2("()(())[[{{}}]");
// std::string str3("()())[[{}}]");

// matcher.setString(&str3);
// matcher.match();

// Knapsack algorithm
/*std::vector<std::pair<float, float>> items = {
  {2, 10}, {3, 5}, {5, 15}, {7, 7}, {1, 6}, {4, 18}, {1, 3}
};

float maxcapacity = 15;

KnapSack sack;
sack.getItemList(maxcapacity, items);*/

// Dijkstra's algorithm
//  std::vector<std::vector<int>> dijkstrasadjmatrix {
//    {0, 2, 4, 0, 0, 0},
//    {0, 0, 1, 7, 0, 0},
//    {0, 0, 0, 0, 3, 0},
//    {0, 0, 0, 0, 0, 1},
//    {0, 0, 0, 2, 0, 5},
//    {0, 0, 0, 0, 0, 0}
//  };
//
//  Dijkstra dijalgo;
//  dijalgo.getAdjMatrix(dijkstrasadjmatrix);
//  dijalgo.setSource(1); // 1 to n
//
//  return 0;
//}