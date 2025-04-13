#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>

struct Process {
  int id;
  int burstTime;
};

bool compareBurstTime(const Process& a, const Process& b) {
  return a.burstTime < b.burstTime;
}

std::ostream& operator<<(std::ostream& COUT, const std::vector<Process>& processes) {
  for (const auto& p : processes) {
    COUT << "P" << p.id << " BT: " << p.burstTime << "ms\n";
  }
  return COUT;
}

void executeProcesses(const Process& process) {
  std::cout << "Executing P" << process.id << " for burst time " << process.burstTime << "ms\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(process.burstTime));
  std::cout << "- P" << process.id << " completed. "<< std::endl;
}

int main() {
  std::vector<Process> processes{{1,100},{2,200},{3,150},{4,80}};
  std::cout << "Before sorting:\n" << processes;
  std::sort(processes.begin(), processes.end(), compareBurstTime);
  std::cout << "After sorting:\n" << processes;
  for (const auto& p : processes) {
    executeProcesses(p);
  }
  return 0;
}