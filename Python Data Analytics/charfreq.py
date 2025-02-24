def counter(str):
  tracker = {}
  for c in str:
    if(c in tracker) :
      tracker[c] += 1
    else :
      tracker[c] = 1
  return tracker

def main():
  str = input("Enter a string: ")
  obj = counter(str)
  print(obj)

main()