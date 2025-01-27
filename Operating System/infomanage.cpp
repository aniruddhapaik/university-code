#include <windows.h>
#include <iostream>
#include <thread>

void printSystemInformation() {
  // Query System Information
  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);

  std::cout << "Processor Architecture: " << sysinfo.wProcessorArchitecture << std::endl;
  std::cout << "Number of Processors: " << sysinfo.dwNumberOfProcessors << std::endl;
  std::cout << "Page Size: " << sysinfo.dwPageSize << " bytes" << std::endl;
}

void printMemoryStatus() {
  // Query Memory Information
  MEMORYSTATUSEX memStatus;
  memStatus.dwLength = sizeof(memStatus);

  if (GlobalMemoryStatusEx(&memStatus)) {
      std::cout << "Total Physical Memory: " << memStatus.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
      std::cout << "Available Physical Memory: " << memStatus.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;
  } else {
      std::cerr << "Error querying memory status. Error code: " << GetLastError() << std::endl;
  }
}

int main() {
  while(true) {
    system("cls");
    printSystemInformation();
    printMemoryStatus();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  
  return 0;
}