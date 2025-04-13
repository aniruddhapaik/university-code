#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

struct Process {
  int id;
  int burstTime;
};

std::ostream& operator<<(std::ostream& COUT,
                         const std::vector<Process>& processes) {
  for (const auto& p : processes) {
    std::cout << 'P' << p.id << " BT: " << p.burstTime << std::endl;
  }
  return COUT;
}

bool compareBurstTime(const Process& a, const Process& b) {
  return a.burstTime < b.burstTime;
}

void executeProcess(const Process& process) {
  std::cout << "Processing: P" << process.id
            << " with burst time: " << process.burstTime << "ms\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(process.burstTime));
  std::cout << "P" << process.id << " completed.\n";
}

int main() {
  std::vector<Process> processes = {{1, 300}, {2, 100}, {3, 200}, {4, 400}};
  std::cout << processes;
  std::sort(processes.begin(), processes.end(), compareBurstTime);
  std::cout << "After Sorting:\n" << processes;

  for (const auto& process : processes) {
    executeProcess(process);
  }

  return 0;
}