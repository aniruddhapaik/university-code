def isprime():
  primecount = 0
  for n in range(2, 100):
    prime = True
    for d in range(2, int(n**0.5)+1):
      if n % d == 0:
        prime = False
        break
    if prime:
      print(n)
      primecount+=1
  print("Number of Prime numbers: ", primecount)

isprime()