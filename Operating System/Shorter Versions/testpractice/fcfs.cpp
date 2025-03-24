#include <iostream>
#include <queue>
#include <chrono>
#include <thread>

struct Process {
  int id;
  int burstTime;
};

void executeProcess(const Process& process) {
  std::cout << "Executing Process P" << process.id << " for burst time: " << process.burstTime << "ms\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(process.burstTime));
  std::cout << "- P" << process.id << " finished executing." << std::endl;
}

int main() {
  std::queue<Process> processqueue;
  processqueue.push({1, 100});
  processqueue.push({2, 200});
  processqueue.push({3, 120});
  processqueue.push({4, 150});
  while(not processqueue.empty()) {
    Process currentprocess = processqueue.front();
    processqueue.pop();
    executeProcess(currentprocess);
  }
  return 0;
}