#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

struct Process {
  int id;
  int burstTime;
};

std::queue<Process> processQueue;
std::mutex mtx;

inline static auto getelapsed(
    std::chrono::time_point<std::chrono::steady_clock> starttime) {
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - starttime)
                     .count();
  return elapsed;
}

void processExecution(
    int threadID,
    std::chrono::time_point<std::chrono::steady_clock> starttime) {
  while (!processQueue.empty()) {
    mtx.lock();
    if (!processQueue.empty()) {
      Process currentProcess = processQueue.front();
      processQueue.pop();
      mtx.unlock();

      auto elapsed = getelapsed(starttime);

      std::cout << std::string(
                       "[T+" + std::to_string(elapsed) + "ms] " + "[Th" +
                       std::to_string(threadID) + "] > Processing: P" +
                       std::to_string(currentProcess.id) +
                       " with burst time: " +
                       std::to_string(currentProcess.burstTime) + "ms\n")
                << std::flush;

      std::this_thread::sleep_for(
          std::chrono::milliseconds(currentProcess.burstTime));

      elapsed = getelapsed(starttime);

      std::cout << std::string("[T+" + std::to_string(elapsed) + "ms] " +
                               "[Th" + std::to_string(threadID) + "] > P" +
                               std::to_string(currentProcess.id) +
                               " completed.\n")
                << std::flush;
    } else {
      mtx.unlock();
    }
  }
}

int main() {
  // Adding processes to the queue
  processQueue.push({1, 500});
  processQueue.push({2, 300});
  processQueue.push({3, 200});
  processQueue.push({4, 400});

  auto starttime = std::chrono::steady_clock::now();

  std::thread t1(processExecution, 1, starttime);
  std::thread t2(processExecution, 2, starttime);

  t1.join();
  t2.join();

  return 0;
}
