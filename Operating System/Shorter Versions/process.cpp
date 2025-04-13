#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main() {
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (snapshot == INVALID_HANDLE_VALUE) {
    std::cerr << "Failed to create snapshot." << std::endl;
    return 1;
  }

  PROCESSENTRY32 pe = {};
  pe.dwSize = sizeof(pe);

  if (Process32First(snapshot, &pe)) {
    do {
      std::wcout << L"PID: " << pe.th32ProcessID << L" | Name: " << pe.szExeFile << std::endl;
    } while (Process32Next(snapshot, &pe));
  } else {
    std::cerr << "Failed to retrieve processes." << std::endl;
  }

  CloseHandle(snapshot);

  DWORD currentPid = GetCurrentProcessId();
  std::cout << "\nCurrent Process ID: " << currentPid << std::endl;
  return 0;
}