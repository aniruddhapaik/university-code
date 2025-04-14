#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <array>

const int MAXPHILOSOPHERS = 5;
std::array<std::mutex, MAXPHILOSOPHERS> forks;

void philosopher(int id) {
  while (true) {
    std::cout << std::string("Philosopher " + std::to_string(id) + " is thinking...\n") << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << std::string("Philosopher " + std::to_string(id) + " is waiting to pick up forks...\n") << std::flush;
    std::scoped_lock lock(forks[id], forks[(id + 1) % MAXPHILOSOPHERS]);
    std::cout << std::string("Philosopher " + std::to_string(id) + " is eating with forks " +
                             std::to_string(id) + " and " + std::to_string((id + 1) % MAXPHILOSOPHERS) + "\n")
              << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main() {
  std::array<std::thread, MAXPHILOSOPHERS> philosophers;
  for (int i = 0; i < MAXPHILOSOPHERS; i++) {
    philosophers[i] = std::thread(philosopher, i);
  }
  for (auto &p : philosophers) { p.join(); }
  return 0;
}