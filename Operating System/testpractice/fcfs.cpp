#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

struct Process {
    int id;
    int burstTime;
};

void executeProcess(const Process& process) {
    std::cout << "Processing: P" << process.id << " with burst time: " << process.burstTime << "ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(process.burstTime));
    std::cout << "P" << process.id << " completed.\n";
}

int main() {
    std::queue<Process> processQueue;
    processQueue.push({1, 500});
    processQueue.push({2, 300});
    processQueue.push({3, 200});
    processQueue.push({4, 400});

    while (!processQueue.empty()) {
        Process currentProcess = processQueue.front();
        processQueue.pop();
        executeProcess(currentProcess);
    }

    return 0;
}