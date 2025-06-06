#include <windows.h>
#include <iostream>
#include <thread>

void printSystemInfo() {
  SYSTEM_INFO system_info;
  GetSystemInfo(&system_info);
  std::cout << "Processor Architecture: " << system_info.wProcessorArchitecture << std::endl;
  std::cout << "Number of Processors: " << system_info.dwNumberOfProcessors << std::endl;
}

void printMemoryStatus() {
  MEMORYSTATUSEX memorystatusex;
  memorystatusex.dwLength = sizeof(MEMORYSTATUSEX);
  if (GlobalMemoryStatusEx(&memorystatusex)) {
    std::cout << "Total memory: " << memorystatusex.ullTotalPhys << std::endl;
    std::cout << "Available memory: " << memorystatusex.ullAvailPhys << std::endl;
  } else { std::cerr << "Failed to get memory info" << std::endl; }
}

int main() {
  while(true) {
    system("cls");
    printSystemInfo();
    printMemoryStatus();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  return 0;
}