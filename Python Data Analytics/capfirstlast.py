str = input("Enter a sentence: ")

for word in str.split() :
  print(word[0].upper() + word[1:-1] + word[-1].upper(), end=" ")