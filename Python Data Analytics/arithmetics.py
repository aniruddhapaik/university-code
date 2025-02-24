import os

def add():
  a, b = int(input("Enter two numbers to add separated by spaces: "))
  print(a, b, sep=" ")

def sub():
  pass

def mul():
  pass

def div():
  pass

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
    choice = int(input("Enter choice:"))
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

menu()