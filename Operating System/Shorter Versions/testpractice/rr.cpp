#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <thread>

const int timequantum = 50;

struct Process {
  int id;
  int burstTime;
  int remainingTime;
};

void roundRobin(std::vector<Process>& processes) {
  std::queue<Process> processqueue;
  for(auto& p : processes) {
    p.remainingTime = p.burstTime;
    processqueue.push(p);
  }

  int currentTime = 0;
  while(not processqueue.empty()) {
    Process currentProcess = processqueue.front();
    processqueue.pop();
    int executionTime = std::min(currentProcess.remainingTime, timequantum);
    std::cout << "[T+" << currentTime << "] Processing P" << currentProcess.id << " for time quantum " << executionTime;
    std::this_thread::sleep_for(std::chrono::milliseconds(executionTime));
    currentTime += executionTime;
    currentProcess.remainingTime -= executionTime;
    if (currentProcess.remainingTime > 0) { 
      processqueue.push(currentProcess); 
      std::cout << " - BT remaining: " << currentProcess.remainingTime << std::endl;
    }
    else { std::cout << " -> P" << currentProcess.id << " completed." << std::endl; }
  }
}

int main() {
  std::vector<Process> processes = {{1, 200}, {2, 150}, {3, 100}};
  roundRobin(processes);
  return 0;
}