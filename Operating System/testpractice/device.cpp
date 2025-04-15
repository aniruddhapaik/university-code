#include <windows.h>
#include <iostream>
#include <bitset>

void ListDrives() {
  DWORD drives = GetLogicalDrives();
  if (drives == 0) { std::cerr << "Failed to get drives info" << std::endl; return; }
  std::cout << "Available drives:\n";
  for (char letter = 'A'; letter < 'Z'; letter++) {
    if (drives & (1 << (letter - 'A'))) {
      std::cout << letter << ":\\" << std::endl;
    }
  }
}

int main() {
  ListDrives();
  return 0;
}