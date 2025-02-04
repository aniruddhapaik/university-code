#include <windows.h>
#include <iostream>
#include <thread>

void printSystemInformation() {
  // Query System Information
  SYSTEM_INFO sysinfo;
  GetSystemInfo(&sysinfo);

  std::cout << "Processor Architecture: " << sysinfo.wProcessorArchitecture << '\n';
  std::cout << "Number of Processors: " << sysinfo.dwNumberOfProcessors << '\n';
  std::cout << std::endl;
  std::cout << "Hardware information" << '\n';   
  std::cout << "  OEM ID: " << sysinfo.dwOemId << '\n';
  std::cout << "  Page size: " << sysinfo.dwPageSize << " bytes" << '\n'; 
  std::cout << "  Processor type: " << sysinfo.dwProcessorType << '\n'; 
  std::cout << "  Minimum application address: " << sysinfo.lpMinimumApplicationAddress << '\n'; 
  std::cout << "  Maximum application address: " << sysinfo.lpMaximumApplicationAddress << '\n'; 
  std::cout << "  Active processor mask: " << sysinfo.dwActiveProcessorMask << '\n'; 
  std::cout << std::endl;
}

void printMemoryStatus() {
  // Query Memory Information
  MEMORYSTATUSEX memStatus;
  memStatus.dwLength = sizeof(memStatus);

  if (GlobalMemoryStatusEx(&memStatus)) {
      std::cout << "Total Physical Memory: " << memStatus.ullTotalPhys / (1024 * 1024) << " MB" << '\n';
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