class Student:
  def __init__(self, reg: int, name: str, sub1: int, sub2: int, sub3: int):
    self.register = reg
    self.name = name
    self.sub1 = sub1
    self.sub2 = sub2
    self.sub3 = sub3
    self.totalmarks = self.calc_totalmarks()
  
  def calc_totalmarks(self)->int:
    return self.sub1 + self.sub2 + self.sub3
  
  def display(self)->None:
    print(f"Register: {self.register}")
    print(f"Name: {self.name}")
    print(f"Total Marks: {self.totalmarks}")
    print("-"*20)

def main():
  s1 = Student(890, "Bob", 90, 95, 98)
  s2 = Student(805, "Tim", 80, 85, 88)
  s3 = Student(900, "Jack", 85, 92, 90)

  s1.display()
  s2.display()
  s3.display()

main()
