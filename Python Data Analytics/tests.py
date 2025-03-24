def even_position_digits(number):
  return [int(d) for i, d in enumerate(str(number), start=1) if i % 2 == 0]

# Example usage
num = 123456
print(even_position_digits(num))  # Output: [2, 4, 6]