#include <iostream>
#include <queue>
#include <thread>

const int TIMEQUANTUM = 20;
int runningTime = 0;

struct Process {
  int id;
  int burstTime;
};

void executeProcess(Process& process) {
  int executionTime = std::min(process.burstTime, TIMEQUANTUM);
  std::cout << "[T+" << runningTime << "ms] Executing process P" << process.id
            << " for " << executionTime << "ms. ";
  std::this_thread::sleep_for(std::chrono::milliseconds(executionTime));
  runningTime += executionTime;
  process.burstTime -= executionTime;
  std::cout << "BT left " << process.burstTime << "ms" << std::endl;
}

int main() {
  std::queue<Process> processes;
  processes.push({1, 50});
  processes.push({2, 100});
  processes.push({3, 200});
  processes.push({4, 150});
  Process* process;
  while(not processes.empty()) {
    process = &processes.front();
    processes.pop();
    executeProcess(*process);
    if (process->burstTime > 0) {
      processes.push(*process);
    } else { std::cout << "finished executing P" << process->id << std::endl; }
  }
  std::cout << "[T+" << runningTime << "ms] Finished executing all tasks" << std::endl;
  return 0;
}