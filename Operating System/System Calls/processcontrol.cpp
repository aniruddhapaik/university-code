#include <windows.h>
//------------------
#include <psapi.h>
#include <tlhelp32.h>

#include <iostream>
#include <limits>

enum class menu : short {
  def = 0,
  getpid = 1,
  listproc,
  forkproc,
  termproc,
  getproctimes,
  getprocmem,
  suspendproc,
  resumeproc,
  waitprocexit,
  setpriority,
  getprocexcode,
  exitprog = 100
};

std::istream& operator>>(std::istream& input, menu& choice) {
  short ch;
  input >> ch;
  choice = (menu)ch;
  return input;
}

void GetCurrentProcessInfo() {
  DWORD processID = GetCurrentProcessId();
  std::cout << "Current Process ID: " << processID << std::endl;
}

void ListRunningProcesses() {
  HANDLE hProcessSnap;
  PROCESSENTRY32 pe32;
  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    std::cerr << "Failed to get process snapshot. Error: " << GetLastError()
              << std::endl;
    return;
  }

  pe32.dwSize = sizeof(PROCESSENTRY32);

  if (Process32First(hProcessSnap, &pe32)) {
    std::cout << "Running Processes:\n";
    do {
      std::cout << "PID: " << pe32.th32ProcessID
                << " | Name: " << pe32.szExeFile << std::endl;
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

  if (CreateProcess(NULL, (LPSTR)program, NULL, NULL, FALSE,
                    NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
    std::cout << "Process created successfully!\n";
    std::cout << "Process ID: " << pi.dwProcessId << std::endl;
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  } else {
    std::cerr << "Failed to create process. Error: " << GetLastError()
              << std::endl;
  }
}

void TerminateProcessByID(DWORD processID) {
  HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);

  if (hProcess == NULL) {
    std::cerr << "Failed to open process. Error: " << GetLastError()
              << std::endl;
    return;
  }

  if (TerminateProcess(hProcess, 0)) {
    std::cout << "Process " << processID << " terminated successfully."
              << std::endl;
  } else {
    std::cerr << "Failed to terminate process. Error: " << GetLastError()
              << std::endl;
  }

  CloseHandle(hProcess);
}

void GetProcessTimesInfo(DWORD processID) {
  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processID);

  if (hProcess == NULL) {
    std::cerr << "Failed to open process. Error: " << GetLastError()
              << std::endl;
    return;
  }

  FILETIME creationTime, exitTime, kernelTime, userTime;
  if (GetProcessTimes(hProcess, &creationTime, &exitTime, &kernelTime,
                      &userTime)) {
    SYSTEMTIME sysTime;
    FileTimeToSystemTime(&creationTime, &sysTime);
    std::cout << "Process Start Time: " << sysTime.wHour << ":"
              << sysTime.wMinute << ":" << sysTime.wSecond << std::endl;
  } else {
    std::cerr << "Failed to retrieve process times. Error: " << GetLastError()
              << std::endl;
  }

  CloseHandle(hProcess);
}

void GetProcessMemoryInfo(DWORD processID) {
  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                FALSE, processID);

  if (hProcess == NULL) {
    std::cerr << "Failed to open process. Error: " << GetLastError()
              << std::endl;
    return;
  }

  PROCESS_MEMORY_COUNTERS pmc;
  if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
    std::cout << "Memory Usage (Working Set Size): "
              << pmc.WorkingSetSize / (1024 * 1024) << " MB\n";
  } else {
    std::cerr << "Failed to retrieve memory info. Error: " << GetLastError()
              << std::endl;
  }

  CloseHandle(hProcess);
}

void SuspendProcess(DWORD processID) {
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  if (hSnapshot == INVALID_HANDLE_VALUE) return;

  THREADENTRY32 te32;
  te32.dwSize = sizeof(THREADENTRY32);

  if (Thread32First(hSnapshot, &te32)) {
    do {
      if (te32.th32OwnerProcessID == processID) {
        HANDLE hThread =
            OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
        if (hThread) {
          SuspendThread(hThread);
          CloseHandle(hThread);
        }
      }
    } while (Thread32Next(hSnapshot, &te32));
  }

  CloseHandle(hSnapshot);
}

void ResumeProcess(DWORD processID) {
  HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  if (hSnapshot == INVALID_HANDLE_VALUE) return;

  THREADENTRY32 te32;
  te32.dwSize = sizeof(THREADENTRY32);

  if (Thread32First(hSnapshot, &te32)) {
    do {
      if (te32.th32OwnerProcessID == processID) {
        HANDLE hThread =
            OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
        if (hThread) {
          ResumeThread(hThread);
          CloseHandle(hThread);
        }
      }
    } while (Thread32Next(hSnapshot, &te32));
  }

  CloseHandle(hSnapshot);
}

void WaitForProcessToExit(DWORD processID) {
  HANDLE hProcess = OpenProcess(SYNCHRONIZE, FALSE, processID);

  if (hProcess == NULL) {
    std::cerr << "Failed to open process. Error: " << GetLastError()
              << std::endl;
    return;
  }

  std::cout << "Waiting for process " << processID << " to exit...\n";
  WaitForSingleObject(hProcess, INFINITE);
  std::cout << "Process exited.\n";

  CloseHandle(hProcess);
}

void SetProcessPriority(DWORD processID, DWORD priority) {
  HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION, FALSE, processID);

  if (hProcess == NULL) {
    std::cerr << "Failed to open process. Error: " << GetLastError()
              << std::endl;
    return;
  }

  if (SetPriorityClass(hProcess, priority)) {
    std::cout << "Process priority updated successfully.\n";
  } else {
    std::cerr << "Failed to set priority. Error: " << GetLastError()
              << std::endl;
  }

  CloseHandle(hProcess);
}

void GetProcessExitCode(DWORD processID) {
  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processID);

  if (hProcess == NULL) {
    std::cerr << "Failed to open process. Error: " << GetLastError()
              << std::endl;
    return;
  }

  DWORD exitCode;
  if (GetExitCodeProcess(hProcess, &exitCode)) {
    std::cout << "Process Exit Code: " << exitCode << std::endl;
  } else {
    std::cerr << "Failed to get exit code. Error: " << GetLastError()
              << std::endl;
  }

  CloseHandle(hProcess);
}

template <typename T>
bool inputFailSafe(T& input) {
  std::cin >> input;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}

int main() {
  menu choice;
  short prioritylevel;
  DWORD processID;
  char program[256];

  // std::cout << NORMAL_PRIORITY_CLASS << std::endl;

  while (true) {
    std::cout << "\n==== Process Management ====\n";
    std::cout << "1. Get Current Process Info (GetCurrentProcessId)\n";
    std::cout << "2. List Running Processes (CreateToolhelp32Snapshot)\n";
    std::cout << "3. Create New Process (CreateProcess)\n";
    std::cout << "4. Terminate Process\n";
    std::cout << "5. Get Process Execution Times (GetProcessTimes)\n";
    std::cout << "6. Get Process Memory Usage (GetProcessMemoryInfo)\n";
    std::cout << "7. Suspend a Process (SuspendThread)\n";
    std::cout << "8. Resume a Process (ResumeThread)\n";
    std::cout << "9. Wait for a Process to Exit (WaitForSingleObject)\n";
    std::cout << "10. Set Process Priority (SetPriorityClass)\n";
    std::cout << "11. Get Process Exit Code (GetExitCodeProcess)\n";
    std::cout << "100. Exit\n";
    std::cout << std::string(10, '-') << '\n';
    std::cout << ">> Enter choice: ";

    if (not inputFailSafe(choice)) {
      choice = menu::def;
    }

    std::cout << std::endl;

    switch (choice) {
      case menu::getpid:
        GetCurrentProcessInfo();
        break;
      case menu::listproc:
        ListRunningProcesses();
        break;
      case menu::forkproc:
        std::cout << "Enter the program to run (e.g., notepad.exe): ";
        std::cin >> program;
        CreateNewProcess(program);
        break;
      case menu::termproc:
        std::cout << "Enter Process ID to terminate: ";
        std::cin >> processID;
        TerminateProcessByID(processID);
        break;
      case menu::getproctimes:
        std::cout << "Enter Process ID for getting process times: ";
        if (inputFailSafe(processID)) {
          GetProcessTimesInfo(processID);
        }
        break;
      case menu::getprocmem:
        std::cout << "Enter Process ID for getting process memory usage: ";
        if (inputFailSafe(processID)) {
          GetProcessMemoryInfo(processID);
        }
        break;
      case menu::suspendproc:
        std::cout << "Enter Process ID to suspend process: ";
        if (inputFailSafe(processID)) {
          SuspendProcess(processID);
        }
        break;
      case menu::resumeproc:
        std::cout << "Enter Process ID to resume process: ";
        if (inputFailSafe(processID)) {
          ResumeProcess(processID);
        }
        break;
      case menu::waitprocexit:
        std::cout << "Enter Process ID to wait for its exit: ";
        if (inputFailSafe(processID)) {
          WaitForProcessToExit(processID);
        }
        break;
      case menu::setpriority:
        std::cout << "Enter Process ID to set its priority: ";
        if (inputFailSafe(processID)) {
          std::cout << "* Priority Level Guide *\n";
          std::cout << "1. IDLE_PRIORITY_CLASS\n";
          std::cout << "2. NORMAL_PRIORITY_CLASS\n";
          std::cout << "3. HIGH_PRIORITY_CLASS\n";
          std::cout << "4. REALTIME_PRIORITY_CLASS\n";
          std::cout << std::string(10, '-') << std::endl;
          std::cout << ">> Enter priority level: ";

          if (inputFailSafe(prioritylevel)) {
            // SetProcessPriority()
          }
        }
        break;
      case menu::getprocexcode:
        std::cout << "Enter Process ID to get its exit status code: ";
        if (inputFailSafe(processID)) {
          GetProcessExitCode(processID);
        }
        break;
      case menu::exitprog:
        return 0;
      default:
        std::cout << "Invalid choice. Try again.\n";
    }
    std::cout << std::string(10, '-') << std::endl;
  }
  return 0;
}

/*
### **Explanation of the Process Management System Calls Used**
1. **`GetCurrentProcessId()`** – Retrieves the current process ID.
2. **`CreateToolhelp32Snapshot()`** – Takes a snapshot of all running processes.
3. **`Process32First()` / `Process32Next()`** – Iterates through running
processes.
4. **`CreateProcess()`** – Starts a new process (e.g., `notepad.exe`).
5. **`OpenProcess()`** – Gets a handle to a process using its ID.
6. **`TerminateProcess()`** – Terminates a process by its ID.
7. **`CloseHandle()`** – Releases handles after use to prevent resource leaks.

---

### **Other Process Management System Calls That Can Be Added**
1. **`GetProcessTimes()`** – Retrieves process execution times (CPU time, start
time).
2. **`GetProcessMemoryInfo()`** – Gets memory usage of a process.
3. **`SuspendThread()` / `ResumeThread()`** – Pauses or resumes a process.
4. **`WaitForSingleObject()`** – Waits for a process to exit.
5. **`EnumProcesses()`** – An alternative to `CreateToolhelp32Snapshot()` for
listing processes.
6. **`SetPriorityClass()`** – Changes the priority of a process.
7. **`GetExitCodeProcess()`** – Retrieves the exit code of a process.

---

## **1. Get Process Execution Times (`GetProcessTimes`)**
This function retrieves the execution times of a process, including:
- Creation time
- Exit time
- Kernel mode time (CPU time spent in system calls)
- User mode time (CPU time spent in user-mode execution)

**Usage:** Call this function with a process ID to get its execution times.

---

## **2. Get Process Memory Usage (`GetProcessMemoryInfo`)**
This retrieves the memory usage of a process, including:
- Page file usage
- Private bytes
- Working set size (RAM usage)

**Usage:** Call this function with a process ID to check how much memory it is
using.

---

## **3. Suspend and Resume a Process (`SuspendThread`, `ResumeThread`)**
These functions allow you to pause and resume a process by suspending/resuming
its main thread.

**Usage:** Call `SuspendProcess(processID)` to pause, and
`ResumeProcess(processID)` to resume execution.

---

## **4. Wait for a Process to Exit (`WaitForSingleObject`)**
If you start a process and want to wait for it to finish, you can use
`WaitForSingleObject`.

**Usage:** This is useful if you want to wait for a background process to
complete.

---

## **5. Set Process Priority (`SetPriorityClass`)**
Windows lets you change a process's priority to control CPU allocation.

**Usage:** Call `SetProcessPriority(processID, HIGH_PRIORITY_CLASS)` to boost
priority.

### **Priority Levels:**
- `IDLE_PRIORITY_CLASS`
- `NORMAL_PRIORITY_CLASS`
- `HIGH_PRIORITY_CLASS`
- `REALTIME_PRIORITY_CLASS` (dangerous, use with caution!)

---

## **6. Get Process Exit Code (`GetExitCodeProcess`)**
After a process exits, you can check its exit status.

**Usage:** If a process crashes, this can help diagnose why.

---

## **Final Thoughts**
Now, you have a **feature-rich process manager**! 🚀 Here’s **everything** we
covered:
1. ✅ Get current process information.
2. ✅ List all running processes.
3. ✅ Create a new process.
4. ✅ Terminate a process by ID.
5. ✅ Get process execution times.
6. ✅ Get memory usage of a process.
7. ✅ Suspend and resume a process.
8. ✅ Wait for a process to exit.
9. ✅ Set process priority.
10. ✅ Get exit code of a process.
*/