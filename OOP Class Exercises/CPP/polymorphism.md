# Polymorphism

In C++, **polymorphism** is a feature that allows objects of different classes to be treated as objects of a common base class. It enables methods to do different things based on the object's actual type at runtime, despite being accessed through a common interface or base class pointer.

Polymorphism is primarily achieved through **inheritance** and **function overriding**, enabling a single function call to dynamically invoke different implementations. There are two main types of polymorphism in C++:

## 1. **Compile-Time Polymorphism** (Static Polymorphism)
   - Compile-time polymorphism occurs when the function or operator that's invoked is determined at compile time.
   - It's achieved through **function overloading**, **operator overloading**, and **templates**.
   - The key advantage of compile-time polymorphism is that it's efficient since the compiler determines which function to call.

   ### Examples of Compile-Time Polymorphism:
   
   - **Function Overloading**:
     ```cpp
     class Print {
     public:
         void print(int i) { std::cout << "Integer: " << i << std::endl; }
         void print(double d) { std::cout << "Double: " << d << std::endl; }
     };

     Print p;
     p.print(5);    // Calls print(int)
     p.print(5.5);  // Calls print(double)
     ```

   - **Operator Overloading**:
     ```cpp
     class Complex {
     public:
         double real, imag;
         Complex(double r, double i) : real(r), imag(i) {}
         Complex operator + (const Complex& c) {
             return Complex(real + c.real, imag + c.imag);
         }
     };

     Complex c1(2.3, 4.5), c2(1.6, 2.7);
     Complex c3 = c1 + c2;  // Calls operator+ overload
     ```

   - **Templates** (generic programming):
     ```cpp
     template <typename T>
     T add(T a, T b) { return a + b; }

     int x = add(2, 3);       // Calls add<int>
     double y = add(2.5, 3.5);  // Calls add<double>
     ```

## 2. **Run-Time Polymorphism** (Dynamic Polymorphism)
   - Run-time polymorphism is where the function to be invoked is determined at runtime.
   - This type of polymorphism is achieved through **virtual functions** and **function overriding**.
   - Run-time polymorphism is essential when the exact type of the object is not known until runtime. It's commonly used in systems where multiple derived classes inherit from a common base class, and each derived class has a unique implementation of a function.

   ### How Run-Time Polymorphism Works in C++:
   
   - **Virtual Functions**: A virtual function in the base class allows derived classes to provide a specific implementation that overrides the base class's version.
   - **Function Overriding**: When a derived class provides its version of a function already defined in the base class, it "overrides" the base function. **This overridden function is then invoked when accessed via a base class pointer pointing to a derived class object**.

   ### Example of Run-Time Polymorphism:
   
   ```cpp
   class Animal {
   public:
       virtual void makeSound() {
           std::cout << "Animal sound" << std::endl;
       }
   };

   class Dog : public Animal {
   public:
       void makeSound() override {  // Override base class function
           std::cout << "Woof" << std::endl;
       }
   };

   class Cat : public Animal {
   public:
       void makeSound() override {  // Override base class function
           std::cout << "Meow" << std::endl;
       }
   };

   Animal* animal1 = new Dog();
   Animal* animal2 = new Cat();

   animal1->makeSound();  // Calls Dog::makeSound()
   animal2->makeSound();  // Calls Cat::makeSound()

   delete animal1;
   delete animal2;
   ```

In this example, `animal1` and `animal2` are pointers to the `Animal` base class but point to `Dog` and `Cat` objects, respectively. The correct `makeSound` function for each derived class is called at runtime.

### Summary of Key Differences
| Type               | Method                         | Binding Time   | Example                          |
|--------------------|--------------------------------|----------------|----------------------------------|
| **Compile-Time**   | Function/Operator Overloading, Templates | Compile Time   | `add(int, int)` vs `add(double, double)` |
| **Run-Time**       | Virtual Functions, Function Overriding   | Runtime       | Base class pointer calling derived class methods |

Polymorphism is a powerful feature in C++ that promotes **code reusability, modularity, and flexibility** in large-scale software applications by allowing different behaviors to be triggered by a common interface.
---

# Virtual Table and Virtual Pointer

In C++, the **virtual table** (often referred to as the **vtable**) is a mechanism used to support **runtime polymorphism** when working with classes that have virtual functions. The virtual table allows C++ to efficiently determine the correct function to call when a function is accessed through a base class pointer or reference, which is critical in polymorphic behavior.

### Key Concepts of Virtual Table (vtable)

1. **Virtual Table (vtable)**:
   - The **vtable** is a lookup table that each polymorphic class has.
   - It is a static table of function pointers maintained for each class that has virtual functions.
   - The vtable stores pointers to the **most derived** (overridden) versions of virtual functions that an object of the class can call.

2. **Virtual Pointer (vptr)**:
   - Each object of a class with at least one virtual function has a hidden pointer, known as the **vptr** (virtual pointer), which points to the class's vtable.
   - The vptr is set up automatically by the compiler when the object is created, and it ensures the object can access the correct vtable for the current class type.

### How the Virtual Table Works

1. **Class Creation**:
   - When a class with virtual functions is defined, the compiler automatically creates a vtable for the class.
   - For each virtual function in the class (whether inherited or newly defined), a corresponding entry is added to the vtable, pointing to the function's implementation.

2. **Inheritance and Overriding**:
   - When a derived class overrides a virtual function, the compiler updates the derived class's vtable so that it points to the overridden version of the function instead of the base version.
   - This ensures that the correct function is called based on the type of the object at runtime, even if accessed through a base class pointer.

3. **Object Instantiation and vptr Setup**:
   - When an object of a class with virtual functions is created, the compiler sets the vptr of that object to point to the class's vtable.
   - This enables the runtime system to know which specific implementation of the virtual functions to use.

4. **Function Call Resolution**:
   - When a virtual function is called on an object through a base class pointer or reference, the compiler uses the vptr to access the vtable.
   - The vtable then directs the call to the correct overridden function based on the object's dynamic (runtime) type, achieving polymorphism.

### Example of Virtual Table in Action

Consider the following example with a base class `Animal` and derived classes `Dog` and `Cat`.

```cpp
#include <iostream>

class Animal {
public:
    virtual void makeSound() {   // Virtual function
        std::cout << "Animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {  // Override base function
        std::cout << "Woof" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {  // Override base function
        std::cout << "Meow" << std::endl;
    }
};

int main() {
    Animal* animal1 = new Dog(); // animal1 points to a Dog object
    Animal* animal2 = new Cat(); // animal2 points to a Cat object

    animal1->makeSound(); // Calls Dog's makeSound
    animal2->makeSound(); // Calls Cat's makeSound

    delete animal1;
    delete animal2;
    return 0;
}
```

### Step-by-Step Breakdown of vtable Usage in the Example

1. **Compilation**:
   - During compilation, the compiler creates a vtable for each class that contains virtual functions (`Animal`, `Dog`, `Cat`).
   - Each vtable contains pointers to the `makeSound` function:
     - The `Animal` vtable has a pointer to `Animal::makeSound`.
     - The `Dog` vtable has a pointer to `Dog::makeSound`.
     - The `Cat` vtable has a pointer to `Cat::makeSound`.

2. **Object Instantiation and vptr Setup**:
   - When `animal1` (a pointer to `Animal`) is assigned a `new Dog()`, the `Dog` constructor is called, and the vptr in the `Dog` object is set to point to the `Dog` vtable.
   - Similarly, when `animal2` is assigned `new Cat()`, the `Cat` constructor sets up the vptr in the `Cat` object to point to the `Cat` vtable.

3. **Virtual Function Call Resolution**:
   - When `animal1->makeSound()` is called, the program uses the vptr in the `Dog` object, which points to the `Dog` vtable.
   - The vtable for `Dog` directs the call to `Dog::makeSound`.
   - Similarly, `animal2->makeSound()` uses the vptr in the `Cat` object, directing the call to `Cat::makeSound`.

### Important Characteristics of the vtable

- **Static Table**: The vtable itself is generated at compile-time, but it is used to resolve function calls at runtime.
- **One vtable per Class**: Each class with virtual functions has its own vtable. Objects do not store their own copies of the vtable; they only have a vptr that points to the relevant vtable.
- **Dynamic Binding**: By using vtables, C++ can perform **dynamic binding** of function calls, allowing the program to call the correct function based on the object's type at runtime.
- **Performance**: Although vtables introduce a small overhead (mainly due to the indirection via the vptr), they are optimized for efficiency by the compiler, making them a standard way of implementing polymorphism in C++.

### Common Scenarios and Uses of the vtable

- **Inheritance Hierarchies**: In complex inheritance structures where functions are overridden at multiple levels, the vtable structure is crucial for ensuring that the correct version of each virtual function is called.
- **Abstract Classes and Pure Virtual Functions**: If a class has pure virtual functions, it serves as an abstract base class. Derived classes must provide implementations for these functions, which are then stored in their respective vtables.

### Summary

The **vtable** is central to achieving runtime polymorphism in C++. By setting up a table of function pointers in each class, C++ enables dynamically bound function calls that allow derived classes to override base class functions, creating flexible and extensible code structures. Through vtables and vptrs, the correct function can be called based on the actual type of an object at runtime, fulfilling the promise of polymorphism.