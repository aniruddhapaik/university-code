#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main() {
  HANDLE th32cs_snapprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (th32cs_snapprocess == INVALID_HANDLE_VALUE) {
    std::cerr << "Failed to create snapshot." << std::endl;
    return -1;
  }

  PROCESSENTRY32 pe = {};
  pe.dwSize = sizeof(PROCESSENTRY32);
  if (Process32First(th32cs_snapprocess, &pe)) {
    do {
      std::wcout << L"PID: " << pe.th32ProcessID << " | NAME: " << pe.szExeFile << std::endl;
    } while (Process32Next(th32cs_snapprocess, &pe));
  } else { std::cerr << "Failed to retrive process info." << std::endl; }
  CloseHandle(th32cs_snapprocess);
  DWORD currentPID = GetCurrentProcessId();
  std::cout << "\nCurrent process ID: " << currentPID << std::endl;
  return 0;
}