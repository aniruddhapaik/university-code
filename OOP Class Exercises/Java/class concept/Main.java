// Define the Car class
class Car {
  // Attributes (Instance Variables)
  String make;
  String model;
  int year;

  // Constructor to initialize Car object
  Car(String make, String model, int year) {
    this.make = make;
    this.model = model;
    this.year = year;
  }

  // Method to display car information
  void displayInfo() {
    System.out.println("Car Make: " + make);
    System.out.println("Car Model: " + model);
    System.out.println("Car Year: " + year);
  }

  // Method for the car to honk
  void honk() {
    System.out.println("Beep beep!");
  }
}

// Main class to test the Car class
public class Main {
  public static void main(String[] args) {
    // Create an object (instance) of the Car class
    Car myCar = new Car("Toyota", "Corolla", 2021);

    // Call methods on the Car object
    myCar.displayInfo(); // Display car information
    myCar.honk(); // Make the car honk
  }
}
