#include <iostream>

class Car {
 public:
  virtual void makeCarNoise() {
    std::cout << "../!?#@%&.. generic car engine running noises" << std::endl;
  }
};

class Ferrari : public Car {
 public:
  void makeCarNoise() override {
    std::cout << "..#######.. Ferrari engine running noises" << std::endl;
  }
};

int main() {
  Car* vehicle = nullptr;

  vehicle = new Car;
  vehicle->makeCarNoise();

  vehicle = new Ferrari;
  vehicle->makeCarNoise();
  return 0;
}