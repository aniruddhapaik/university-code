str = input("Enter a sentence: ")
splitstr = str.split()

for i in range(len(splitstr)):
  splitstr[i] = splitstr[i][0].upper() + splitstr[i][1:-1] + splitstr[i][-1].upper()

print(splitstr)