#include <iostream>

class Vehicle {
 public:
  void startEngine() { std::cout << "#!#!#!#!..." << std::endl; }

  void accelerate() {
    this->speed += 5;
    std::cout << "\nSpeeding up by 5 units\n"
              << "Speed: " << this->speed << std::endl;
  }

  void decelerate() {
    this->speed -= 5;
    std::cout << "\nSpeeding down by 5 units\n"
              << "Speed: " << this->speed << std::endl;
  }

 private:
  int speed = 0;
};

class Truck : public Vehicle {
 private:
  uint8_t wheels = 8;
};

int main() {
  Truck truck_lord_one;

  truck_lord_one.startEngine();
  truck_lord_one.accelerate();
  truck_lord_one.accelerate();
  truck_lord_one.decelerate();

  return 0;
}