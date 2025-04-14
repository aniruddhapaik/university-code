#include <windows.h>
#include <iostream>
#include <bitset>

void ListDrives() {
  DWORD drivesmask = GetLogicalDrives();
  if (drivesmask == 0) {
    std::cerr << "Failed to get drives info" << std::endl;
    return;
  }
  std::cout << "Drives Mask: " << std::bitset<sizeof(DWORD)*8>(drivesmask) << std::endl;
  std::cout << "Available drives:\n";
  for (char letter = 'A'; letter <= 'Z'; letter++) {
    if (drivesmask & (1 << (letter - 'A'))) {
      std::cout << letter << ":\\" << std::endl;
    }
  }
}

int main() {
  ListDrives();
  return 0;
}