#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

int runningTime = 0;

struct Process {
  int id;
  int arrivalTime;
  int burstTime;
  int priority;
};

bool comparePriority(const Process& a, const Process& b) {
  return a.priority > b.priority;
}

void executeProcess(Process& process) {
  std::cout << "[T+" << runningTime << "] Executing P" << process.id << " of priority " << process.priority << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  runningTime++;
  process.burstTime--;
}

int main() {
  std::vector<Process> processes = {{1, 5, 20, 2}, {2, 15, 40, 1}, {3, 5, 10, 5}, {4, 0, 30, 3}};
  std::sort(processes.begin(), processes.end(), comparePriority);
  while(not processes.empty()) {
    int i = 0;
    while(runningTime < processes[i].arrivalTime) {
      i++;
      if (i >= processes.size()) {
        std::cout << "[T+" << runningTime << "]" << std::endl;
        runningTime++; i = 0;
      }
    }
    executeProcess(processes[i]);
    if (processes[i].burstTime <= 0) {
      processes.erase(processes.begin()+i);
    }
  }
  std::cout << "[T+" << runningTime << "] Finished executing all processes" << std::endl;
  return 0;
}