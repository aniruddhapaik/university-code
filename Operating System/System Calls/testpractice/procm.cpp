#include <windows.h>
#include<iostream>

void getCurrentProcessInfo() {
  DWORD processID = GetCurrentProcessId();
  std::cout << "PID: " << processID << std::endl;
}

int main() {
  getCurrentProcessInfo();

  return 0;
}