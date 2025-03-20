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
    processQueue.push(process);
  }

  int currentTime = 0;
  while (!processQueue.empty()) {
    Process currentProcess = processQueue.front();
    processQueue.pop();

    if (currentProcess.remainingTime > timeQuantum) {
      std::cout << std::string("[T+" + std::to_string(currentTime) + "ms] P" +
                               std::to_string(currentProcess.id) +
                               " is executing for " +
                               std::to_string(timeQuantum) + "ms. ");
      //<< std::endl;
      currentTime += timeQuantum;

      std::this_thread::sleep_for(std::chrono::milliseconds(timeQuantum));

      currentProcess.remainingTime -= timeQuantum;
      std::cout << std::string(
          "Time remaining : " + std::to_string(currentProcess.remainingTime) +
          "ms\n");
      processQueue.push(currentProcess);
    } else {
      std::cout << std::string(
          "[T+" + std::to_string(currentTime) + "ms] P" +
          std::to_string(currentProcess.id) + " is executing for " +
          std::to_string(currentProcess.remainingTime) +
          "ms\n");
      //<< std::endl;
      currentTime += currentProcess.remainingTime;

      std::this_thread::sleep_for(
          std::chrono::milliseconds(currentProcess.remainingTime));

      currentProcess.remainingTime = 0;
      std::cout << std::string("[T+" + std::to_string(currentTime) +
                               "ms] --- P" + std::to_string(currentProcess.id) +
                               " finished at time " +
                               std::to_string(currentTime) + "ms\n")
                << std::endl;
    }
  }
}

int main() {
  std::vector<Process> processes = {
      {1, 100, 100}, {2, 250, 250}, {3, 300, 300}};
  int timeQuantum = 20;

  std::cout << "Time Quantum: " << timeQuantum
            << "\nP1 BT:" << processes[0].burstTime << "ms"
            << "\nP2 BT:" << processes[1].burstTime << "ms"
            << "\nP1 BT:" << processes[2].burstTime << "ms\n"
            << std::endl;

  roundRobinScheduling(processes, timeQuantum);

  return 0;
}
