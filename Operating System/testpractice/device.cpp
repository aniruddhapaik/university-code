#include <windows.h>
#include <iostream>
#include <bitset>

void listDrives() {
  DWORD drivemask = GetLogicalDrives();
  if (drivemask == 0) { 
    std::cerr << "Failed to get drives info, " << GetLastError() << std::endl;
    return;
  }
  std::cout << "drive mask: " << std::bitset<sizeof(DWORD)*8>(drivemask) << std::endl;
  std::cout << "Available drives:\n";
  for (char letter = 'A'; letter <= 'Z'; letter++) {
    if (drivemask & (1 << (letter - 'A'))) {
      std::cout << letter << ":\\" << std::endl;
    }
  }
}

int main() {
  listDrives();
  return 0;
}