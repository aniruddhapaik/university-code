#include <iostream>
#include <vector>
#include <thread>

int runningTime = 0;

struct Process {
  int id;
  int burstTime;
};

void executeProcess(const Process& process) {
  std::cout << "[T+" << runningTime << "ms] Executing process " << process.id << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(process.burstTime));
  runningTime += process.burstTime;
}

int main() {
  std::vector<Process> processes = {{1, 10}, {2, 15}, {3, 30}, {4, 20}};
  for (const auto& p : processes) { executeProcess(p); }
  std::cout << "[T+" << runningTime << "ms] Finished executing all processes" << std::endl;
  return 0;
}