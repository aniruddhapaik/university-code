## 1. Which of the following is true about constructors.

1. They cannot be virtual.
2. They cannot be private.
3. They are automatically called by new operator.

A. All 1, 2, and 3\
**B. only 1 and 3**\
C. Only 1 and 2\
D. only 2 and 3

---

## 2. Find output of the following code:

```c++
class Test {
  int x;
};

int main() {
  Test t;
  cout << t.x;
  return 0;
}
```

A. 0\
B. Garbage Value\
**C. Compiler Error**\
D. Runtime Error

---

## 3. Which of the following is true?

1. All objects of a class share all data members of class
2. Objects of a class do not share non-static members. Every object has its own copy.
3. Objects of a class do not share codes of non-static methods, they have their own copy.

A. All 1, 2, and 3\
B. Only 1\
**C. Only 2**\
D. None of the above

---

## 4. A C++ class belongs to **\_\_\_\_** data type.

**a) User defined derived data type**\
b) Derived data type\
c) Fundamental data type\
d) Atomic data type

---

## 5. Find output of the following code:

```c++
#include<iostream
using namespace std;

class Test {
  static int x;
  int *ptr;
  int y;
};

int main() {
  Test t;
  cout << sizeof(t) << ' ';
  cout << sizeof(Test*);
}
```

A. 12 4\
B. 12 12\
**C. 8 4**\
D. 8 8

---

## 6. Which of the following cannot be passed to a function in C++?

A. Constant\
B. Structure\
C. Array\
**D. Header file**

---

## 7. Which of the following is a correct statement?

**A. Composition is a strong type of association between two classes with full ownership.**\
B. Composition is a strong type of association between two classes with partial ownership.\
C. Composition is a weak type of association between two classes with partial ownership.\
D. Composition is a weak type of association between two classes with strong ownership.

---

## 8. When a method in a subclass has the same name and type signatures as a method in the superclass, then the method in the subclass **\_\_\_\_** the method in the superclass.

**A. Overrides**\
B. Overloads\
C. Friendships\
D. Inherits

---

## 9. It is possible to define a class within a class termed as nested class. There are **\_\_\_\_** types of nested classes.

**A. 2**\
B. 3\
C. 4\
D. 5

---

## 10. The direct member access operator cannot be used to access the **\_\_\_\_** member.

a) public\
b) private\
c) protected\
**d) both private & protected**

---

## 11. The objects are also called as **\_\_\_\_**

a) member of the class\
b) asociate of the class\
c) attribute of the class\
**d) instance of the class**

---

## 12. When the inheritance is private, the private methods in base class are **\_\_\_\_** in the derived class (in C++).

**A. inaccessible**\
B. accessible\
C. protected\
D. public

---

## 13. Polymorphism using the operator function is also called as **\_\_\_\_**

a) function overloading\
b) object overloading\
c) member overloading\
**d) operator overloading**

---

## 14. Which of the following operators can't be overloaded?

**a) ::**\
b) +\
c) -\
d) []

---

## 15. Find output of the following code:

```c++
#include<iostream>
using namespace std;
class Base1 {
public:
  Base1() {
    cout<< "Base1's constructor called" << endl;
  }
};

class Base2: {
public:
  Base2() {
    cout << "Base2's constructor called" << endl;
  }
};

class Derived: public Basel, public Base2 {
public:
  Derived() {
    cout << "Derived's contructor called" << endl;
  }
};

int main() {
  Derived d;
  return 0;
}
```

A. Basel's constructor called\
B. Base2's constructor called\
C. Derived's constructor called\
**D. All of the above in order A, B, C**

---

## 16. The data members and functions of base class can be made inaccessible by the derived class by using **\_\_\_\_** access specifier.

**a) private**\
b) protected\
c) public\
d) both private and protected

---

## 17. Inline functions are useful when

**A. Function is small and we want to avoid function call overhead.**\
B. Function is large with many nested loops\
C. Function has many static valiables\
D. None of the above

---

## 18. A virtual function in C++ causes **\_\_\_\_**.

**a) All the functions which are declared in the class and are re-defined/overridden by the derived class**\
b) All functions that are derived from the base class\
c) All the members that are accessing base class data members\
d) Any member function of a class

---

## 19. A member function can always access the data in **\_\_\_\_** (in C++)

**A. the class of which it is member**\
B. the object of which it is a member\
C. the public part of its class\
D. the private part of its class

---

## 20. What is a pure virtual function?

a) A virtual function defined inside the base class\
b) A virtual function that is defined inside the derived class\
**c) A virtual function that has no definition relative to the base class**\
d) Any function that is made virtual
