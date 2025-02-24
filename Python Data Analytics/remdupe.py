def remdupe(str):
  strtwo = list(str)
  track = {}
  for i in range(len(str)):
    if str[i] in track:
      strtwo[i] = ' '
    else :
      track[str[i]] = True
  return strtwo

def main():
  str = input("Enter string: ")
  obj = remdupe(str)
  print("Original String:    ", str)
  print("Duplicates removed: ",''.join(obj))

main()