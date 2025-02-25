def fact(num):
  if num == 0:
    return 1
  else :
    return num * fact(num-1)

def main():
  x = int(input("Enter value for x, numerator: "))
  n = int(input("Enter value for n, limit: "))
  print("Calculating series: x-(x^2)/2!+(x^3)/3!-(x^4)/4!+...(x^n)/n!")
  sum = 0.0
  
  print("Sum of ", end='')
  for i in range(1, n+1):
    sign = 1
    if i%2 == 0: sign = -1
    else: sign = 1
    
    newelem = sign*((x**i)/fact(i))
    print(f"{i}) {newelem:.3f}", end=' ')
    sum = sum + newelem
  
  print(" = ", f"{sum:.5f}")

main()