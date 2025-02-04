#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <limits>

void GetCurrentProcessInfo() {
    DWORD processID = GetCurrentProcessId();
    std::cout << "Current Process ID: " << processID << std::endl;
}

void ListRunningProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get process snapshot. Error: " << GetLastError() << std::endl;
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hProcessSnap, &pe32)) {
        std::cout << "Running Processes:\n";
        do {
            std::cout << "PID: " << pe32.th32ProcessID << " | Name: " << pe32.szExeFile << std::endl;
        } while (Process32Next(hProcessSnap, &pe32));
    } else {
        std::cerr << "Failed to retrieve process list." << std::endl;
    }

    CloseHandle(hProcessSnap);
}

void CreateNewProcess(const char* program) {
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(si);

    if (CreateProcess(NULL, (LPSTR)program, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
        std::cout << "Process created successfully!\n";
        std::cout << "Process ID: " << pi.dwProcessId << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Failed to create process. Error: " << GetLastError() << std::endl;
    }
}

void TerminateProcessByID(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);
    
    if (hProcess == NULL) {
        std::cerr << "Failed to open process. Error: " << GetLastError() << std::endl;
        return;
    }

    if (TerminateProcess(hProcess, 0)) {
        std::cout << "Process " << processID << " terminated successfully." << std::endl;
    } else {
        std::cerr << "Failed to terminate process. Error: " << GetLastError() << std::endl;
    }

    CloseHandle(hProcess);
}

int main() {
    int choice;
    DWORD processID;
    char program[256];

  std::cout << NORMAL_PRIORITY_CLASS << std::endl;

    while (true) {
        std::cout << "\n==== Process Management ====\n";
        std::cout << "1. Get Current Process Info\n";
        std::cout << "2. List Running Processes\n";
        std::cout << "3. Create New Process\n";
        std::cout << "4. Terminate Process\n";
        std::cout << "5. Exit\n";
        std::cout << std::string(10, '-') << '\n';
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if(std::cin.fail()) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          choice = 0;
        }

        switch (choice) {
            case 1:
                GetCurrentProcessInfo();
                break;
            case 2:
                ListRunningProcesses();
                break;
            case 3:
                std::cout << "Enter the program to run (e.g., notepad.exe): ";
                std::cin >> program;
                CreateNewProcess(program);
                break;
            case 4:
                std::cout << "Enter Process ID to terminate: ";
                std::cin >> processID;
                TerminateProcessByID(processID);
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
        std::cout << std::string(10,'-') << std::endl;
    }
    return 0;
}
