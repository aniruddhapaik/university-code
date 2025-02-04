def isprime():
  primecount = 0
  for n in range(2, 100):
    notprime = False
    for d in range(2, int(n/2)+1):
      if n % d == 0:
        notprime = True
        break
    if notprime:
      continue
    print(n)
    primecount+=1
  print("Number of Prime numbers: ", primecount)

isprime()