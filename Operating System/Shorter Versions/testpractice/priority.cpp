#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <thread>

struct Process {
  int id;
  int arrivalTime;
  int burstTime;
  int priority;
};

bool comparePriority(const Process& a, const Process& b) {
  return a.priority > b.priority;
}

void executeProcesses(std::vector<Process>& processes) {
  int runningTime = 0;
  std::sort(processes.begin(), processes.end(), comparePriority);
  while (not processes.empty()) {
    int i = 0;
    while(runningTime < processes[i].arrivalTime) {
      i++;
      if (not (i < processes.size())) {
        std::cout << "[T+" << runningTime << "]" << std::endl;
        i = 0;
        runningTime++;
      }
    }

    std::cout << "[T+" << runningTime << "] Executing P" << processes[i].id << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    processes[i].burstTime--;
    if (not (processes[i].burstTime > 0)) { 
      std::cout << "- P" << processes[i].id << " completed" << std::endl;
      processes.erase(processes.begin()+i); 
    }
    runningTime++;
  }
}

int main() {
  std::vector<Process> processes = {{1, 10, 10, 2}, {2, 5, 15, 1}, {3, 15, 5, 3}};
  executeProcesses(processes);
  return 0;
}