def summer():
  sum = 0
  num = int(input("Enter number: "))
  while (num):
    last = num % 10
    sum = sum + last
    num = int(num / 10)
  print(sum)

summer()