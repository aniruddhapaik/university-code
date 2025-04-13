#include <windows.h>

#include <iostream>

void ListDrives() {
  DWORD drives = GetLogicalDrives();
  if (drives == 0) {
    std::cerr << "failed to get, " << GetLastError() << std::endl;
    return;
  }

  std::cout << "Available drives " << std::endl;
  for(char letter = 'A'; letter <= 'Z'; ++letter) {
    if (drives & (1 << (letter - 'A'))) {
      std::cout << letter << ".\\" << std::endl;
    }
  }
}

int main() {
  ListDrives();
  return 0;
}