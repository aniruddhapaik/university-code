#include <iostream>
#include <string>

enum class Gender : uint8_t { male, female };

class Animal {
 protected:
  std::string name;
  std::string baby;
  Gender gender;
  int number_of_legs;

 public:
  Animal(std::string namestr, Gender gn, int legs) {
    this->name = namestr;
    this->gender = gn;
    this->number_of_legs = legs;
  }

  virtual const void makeSound() const = 0;  // Pure virtual function
  virtual const void giveBirth() const = 0;  // another pure virtual function
};

class Mammal : public Animal {  // inheritting from Animal class
 public:
  Mammal(std::string namestr, Gender gn, int legs) : Animal(namestr, gn, legs) {
    this->baby = "baby";  // initializing default baby for mammals
  }

  const void giveBirth() {
    std::cout << Animal::name << " gave birth to a " << Animal::baby
              << std::endl;
  }
};

class Bird : public Animal {  // inheriting from Animal class
};

class Dog : public Mammal {  // inheriting from Mammal class derived from Animal
                             // class, multilevel inheritance
};

class Human : public Mammal {  // inheriting from Mammal class derived from
                               // Animal class, multilevel inheritance
};

class Chicken : public Bird {  // inheriting from Bird class derived from Animal
                               // class, multilevel inheritance
};

int main() { return 0; }