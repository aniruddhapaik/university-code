#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

struct Process {
  int id;
  int burstTime;
  int arrivalTime;
  int priority;
};

bool comparePriority(const Process& a, const Process& b) {
  return a.priority > b.priority;  // Higher priority first
}

std::ostream& operator<<(std::ostream& COUT,
                         const std::vector<Process>& processes) {
  for (const Process& proc : processes) {
    std::cout << 'P' << proc.id << " Priority: " << proc.priority
              << " AT: " << proc.arrivalTime << " BT: " << proc.burstTime
              << std::endl;
  }

  return COUT;
}

inline static void printExecutionInfo(const Process& process,
                                      const int runningTime) {
  std::cout << "[T+" << runningTime << "] Processing P" << process.id
            << " of priority: " << process.priority
            << " BT remaining: " << process.burstTime << std::endl;
}

void priorityScheduling(std::vector<Process>& processes) {
  int runningTime = 0;

  std::sort(processes.begin(), processes.end(), comparePriority);
  std::cout << processes;

  while (not processes.empty()) {
    int i = 0;
    while (runningTime < processes[i].arrivalTime) {
      i++;
      if (not(i < processes.size())) {
        std::cout << "[T+" << runningTime << "]" << std::endl;
        runningTime++;
        i = 0;
      }
    }

    printExecutionInfo(processes[i], runningTime);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    processes[i].burstTime--;
    if (processes[i].burstTime == 0) {
      processes.erase(processes.begin() + i);
    }
    runningTime++;
  }
}

int main() {
  std::vector<Process> processes = {{1, 25, 10, 3},
                                    {2, 12, 20, 4},
                                    {3, 50, 0, 2},
                                    {4, 17, 30, 5},
                                    {5, 37, 40, 2}};

  priorityScheduling(processes);

  return 0;
}
