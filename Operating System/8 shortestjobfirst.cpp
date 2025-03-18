#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

struct Process {
  int id;
  int burstTime;
};

bool compareBurstTime(Process a, Process b) {
  return a.burstTime < b.burstTime;
}

inline static auto getelapsed(
    std::chrono::time_point<std::chrono::steady_clock> starttime) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now() - starttime)
      .count();
}

void executeProcess(
    Process p, std::chrono::time_point<std::chrono::steady_clock> starttime) {
  auto elapsed = getelapsed(starttime);
  std::cout << "[T+" + std::to_string(elapsed) + "ms] Process " << p.id
            << " is executing with burst time " << p.burstTime << " ms"
            << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(p.burstTime));
  elapsed = getelapsed(starttime);
  std::cout << "[T+" + std::to_string(elapsed) + "ms] Process " << p.id
            << " has finished executing" << std::endl;
}

int main() {
  std::vector<Process> processes = {{1, 300}, {2, 100}, {3, 200}, {4, 400}};

  for (auto &proc : processes) {
    std::cout << "P" << proc.id << ": burst time " << proc.burstTime << "ms\n";
  }
  std::cout << std::endl;

  // Sort processes by burst time
  std::sort(processes.begin(), processes.end(), compareBurstTime);

  std::cout << "After sorting: ";
  for (auto &proc : processes) {
    std::cout << "P" << proc.id << " ";
  }
  std::cout << "\n" << std::endl;

  auto starttime = std::chrono::steady_clock::now();

  // Execute each process sequentially
  for (auto &proc : processes) {
    executeProcess(proc, starttime);
  }

  return 0;
}
