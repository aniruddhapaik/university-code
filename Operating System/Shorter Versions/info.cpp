#include <windows.h>
#include <thread>
#include <iostream>

void printSystemInfo() {
  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);

  std::cout << "Processor Arch: " << sysinfo.wProcessorArchitecture << std::endl;
  std::cout << "Number of processors: " << sysinfo.dwNumberOfProcessors << std::endl;
}

void getMemoryStatus() {
  MEMORYSTATUSEX memStatus;
  memStatus.dwLength = sizeof(memStatus);

  if(GlobalMemoryStatusEx(&memStatus)) {
    std::cout << "Total memory: " << memStatus.ullTotalPhys / (1024*1024) << " MB" << std::endl;
    std::cout << "Available memory: " << memStatus.ullAvailPhys / (1024*1024) << " MB" << std::endl;
  } else {
    std::cerr << "Error fetching memory information" << std::endl;
  }
}

int main() {
  while(true) {
    system("cls");
    printSystemInfo();
    getMemoryStatus();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  
  return 0;
}