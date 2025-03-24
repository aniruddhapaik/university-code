#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

struct Process {
  int id;
  int burstTime;
  int remainingTime;
};

void roundRobinScheduling(std::vector<Process>& processes, int timeQuantum) {
  std::queue<Process> processQueue;
  for (auto& process : processes) {
    process.remainingTime = process.burstTime;
    processQueue.push(process);
  }

  int currentTime = 0;
  while (!processQueue.empty()) {
    Process currentProcess = processQueue.front();
    processQueue.pop();

    int executionTime = std::min(timeQuantum, currentProcess.remainingTime);
    std::cout << "Processing: P" << currentProcess.id << " for "
              << executionTime << "ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(executionTime));
    currentTime += executionTime;
    currentProcess.remainingTime -= executionTime;

    if (currentProcess.remainingTime > 0) {
      processQueue.push(currentProcess);
    } else {
      std::cout << "P" << currentProcess.id << " completed at " << currentTime
                << "ms\n";
    }
  }
}

int main() {
  std::vector<Process> processes = {{1, 100}, {2, 250}, {3, 300}};
  int timeQuantum = 50;

  roundRobinScheduling(processes, timeQuantum);

  return 0;
}
