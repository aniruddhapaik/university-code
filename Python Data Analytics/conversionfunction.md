Python provides various built-in **conversion functions** to convert data from one type to another. Here’s a categorized list:

---

### **1. String Conversions**

- `list(str)` → Converts a string to a list of characters.

  ```python
  print(list("hello"))  # ['h', 'e', 'l', 'l', 'o']
  ```

- `tuple(str)` → Converts a string to a tuple of characters.

  ```python
  print(tuple("hello"))  # ('h', 'e', 'l', 'l', 'o')
  ```

- `set(str)` → Converts a string to a set of unique characters.

  ```python
  print(set("hello"))  # {'h', 'e', 'o', 'l'}
  ```

- `frozenset(str)` → Converts a string to an immutable set.

  ```python
  print(frozenset("hello"))  # frozenset({'h', 'e', 'o', 'l'})
  ```

---

### **2. Numeric Conversions**

- `int(x)` → Converts to an integer.

  ```python
  print(int("42"))  # 42
  ```

- `float(x)` → Converts to a float.

  ```python
  print(float("3.14"))  # 3.14
  ```

- `complex(x)` → Converts to a complex number.

  ```python
  print(complex("3+4j"))  # (3+4j)
  ```

- `bool(x)` → Converts to a boolean (`False` for empty/zero values, `True` otherwise).

  ```python
  print(bool(0))  # False
  print(bool(10))  # True
  ```

---

### **3. Sequence Conversions**

- `list(iterable)` → Converts an iterable (tuple, range, set, dict keys) into a list.

  ```python
  print(list((1, 2, 3)))  # [1, 2, 3]
  ```

- `tuple(iterable)` → Converts an iterable into a tuple.

  ```python
  print(tuple([1, 2, 3]))  # (1, 2, 3)
  ```

- `set(iterable)` → Converts an iterable into a set (removes duplicates).

  ```python
  print(set([1, 2, 2, 3]))  # {1, 2, 3}
  ```

- `frozenset(iterable)` → Converts an iterable into an immutable set.

  ```python
  print(frozenset([1, 2, 3]))  # frozenset({1, 2, 3})
  ```

- `dict(iterable)` → Converts an iterable of key-value pairs into a dictionary.

  ```python
  print(dict([("a", 1), ("b", 2)]))  # {'a': 1, 'b': 2}
  ```

- `str(object)` → Converts any object into a string.

  ```python
  print(str(100))  # "100"
  ```

---

Sure! Here are more **special conversion functions** in Python:

---

### **4. Special Conversions**

- `bytes(iterable_or_string, encoding)` → Converts a string or iterable to a **bytes** object.

  ```python
  print(bytes("hello", "utf-8"))  # b'hello'
  print(bytes([65, 66, 67]))  # b'ABC'
  ```

- `bytearray(iterable_or_string, encoding)` → Converts to a **mutable byte array**.

  ```python
  print(bytearray("hello", "utf-8"))  # bytearray(b'hello')
  print(bytearray([65, 66, 67]))  # bytearray(b'ABC')
  ```

- `memoryview(bytes_object)` → Creates a **memoryview** object (used for handling large binary data efficiently).

  ```python
  mv = memoryview(b"hello")
  print(mv[0])  # 104 (ASCII value of 'h')
  ```

---

### **5. Boolean Conversions**

- `bool(x)` → Converts any object to `True` or `False` based on its truthiness.

  ```python
  print(bool([]))  # False (empty list)
  print(bool([1, 2, 3]))  # True (non-empty list)
  print(bool(""))  # False (empty string)
  ```

---

### **6. Range Conversion**

- `range(start, stop, step)` → Creates a range object (not exactly a conversion, but useful).

  ```python
  print(list(range(1, 5)))  # [1, 2, 3, 4]
  ```

---

### **7. JSON Conversions**

- `import json`
  - `json.dumps(obj)` → Converts a Python object to a JSON string.
  - `json.loads(json_string)` → Converts a JSON string to a Python object.

  ```python
  import json
  data = {"name": "Alice", "age": 25}
  json_string = json.dumps(data)  # '{"name": "Alice", "age": 25}'
  print(json.loads(json_string))  # {'name': 'Alice', 'age': 25}
  ```

---

### **8. Object Conversion Using `__str__` and `__repr__`**

- Custom objects can be converted to strings using `__str__` and `__repr__`:

  ```python
  class Person:
      def __str__(self):
          return "Person Object"

  p = Person()
  print(str(p))  # "Person Object"
  ```

---

### **Summary Table**

| Conversion Function             | Description                           |
| ------------------------------- | ------------------------------------- |
| `int(x)`                        | Converts to integer                   |
| `float(x)`                      | Converts to float                     |
| `complex(x)`                    | Converts to complex number            |
| `bool(x)`                       | Converts to boolean (`True/False`)    |
| `str(x)`                        | Converts to string                    |
| `list(iterable)`                | Converts to list                      |
| `tuple(iterable)`               | Converts to tuple                     |
| `set(iterable)`                 | Converts to set                       |
| `frozenset(iterable)`           | Converts to immutable set             |
| `dict(iterable)`                | Converts to dictionary                |
| `bytes(iterable, encoding)`     | Converts to bytes                     |
| `bytearray(iterable, encoding)` | Converts to bytearray                 |
| `memoryview(bytes_obj)`         | Creates a memory view                 |
| `json.dumps(obj)`               | Converts Python object to JSON string |

| `json.loads(json_string)`
