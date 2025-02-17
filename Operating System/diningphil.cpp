#include <array>
#include <iostream>
#include <mutex>
#include <thread>

constexpr int NUM_PHILOSOPHERS = 5;
std::array<std::mutex, NUM_PHILOSOPHERS> forks;

void philosopher(int id) {
  int left = id;
  int right = (id + 1) % NUM_PHILOSOPHERS;

  while (true) {
    std::string linethink = std::string("Philosopher ") + std::to_string(id) +
                            std::string(" is * thinking *...\n");
    std::cout << linethink << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Pick up both forks safely
    std::scoped_lock lock(forks[left], forks[right]);

    std::string lineeat = std::string("Philosopher ") + std::to_string(id) +
                          std::string(" is {eating}...[ LOCKING Left: ") +
                          std::to_string(left) + std::string(" | Right: ") +
                          std::to_string(right) + std::string(" ]\n");
    std::cout << lineeat << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main() {
  std::array<std::thread, NUM_PHILOSOPHERS> philosophers;

  // Create philosopher threads
  for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    philosophers[i] = std::thread(philosopher, i);

  // Join threads
  for (auto& p : philosophers) p.join();

  return 0;
}
