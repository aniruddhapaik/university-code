def top(n:int, c=1) -> None:
  for i in range(c, n):
    print(' '+'🔥..'*i)

def bottom(n:int, c=1) -> None:
  for j in range(n, c-1, -1):
    print(' '+'🔥..'*j)

def fire(n:int, c=1) -> None:
  if c > n or c < 1:
    return
  top(n, c)
  bottom(n, c)

fire(10, 5)