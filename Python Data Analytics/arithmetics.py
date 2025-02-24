import os

def add():
  a, b = map(int, input("Enter two numbers to ADD separated by space: ").split())
  print("Sum of",a,"and",b, "is", a+b, sep=" ", end="\n")

def sub():
  a, b = map(int, input("Enter two numbers to SUBTRACT Second from First separated by space: ").split())
  print("Subtraction",b,"from",a, "is", a-b, sep=" ", end="\n")

def mul():
  a, b = map(int, input("Enter two numbers to MULTIPLY separated by space: ").split())
  print("Multiplication of",a,"and",b, "is", a*b, sep=" ", end="\n")

def div():
  a, b = map(int, input("Enter two numbers to DIVIDE First by Second separated by space: ").split())
  print("Division of",a,"by",b, "is", a/b, sep=" ", end="\n")

def clear():
  os.system("cls")

def menu():
  while (True):
    choice = 0
    print("=== Arithmetic Menu ===")
    print("1. Add")
    print("2. Subtract")
    print("3. Multiply")
    print("4. Divide")
    print("5. Clear Screen")
    print("6. Exit")
    choice = int(input("Enter choice: "))
    match choice:
      case 1:
          add()
      case 2:
          sub()
      case 3:
          mul()
      case 4:
          div()
      case 5:
          clear()
      case 6:
          return
    print("\n")

menu()