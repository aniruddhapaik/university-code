#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>

int runningTime = 0;

struct Process {
  int id;
  int burstTime;
};

bool compareBurst(const Process& a, const Process& b) {
  return a.burstTime < b.burstTime;
}

void executeProcess(const Process& process) {
  std::cout << "[T+" << runningTime << "ms] Executing process " << process.id 
            << " for " << process.burstTime << "ms" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(process.burstTime));
  runningTime += process.burstTime;
}

int main() {
  std::vector<Process> processes = {{1, 30}, {2, 40}, {3, 10}, {4, 20}};
  std::sort(processes.begin(), processes.end(), compareBurst);
  for (const auto& p : processes) {
    executeProcess(p);
  }
  std::cout << "[T+" << runningTime << "ms] Finished executing all processes" << std::endl;
  return 0;
}