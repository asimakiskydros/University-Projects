def mu(number):
  if number < 2:
    return number == 1
  return (-1) ** len(factor(number))

num = 10
print(
   sum(mu(d) * 2 ** (num / d) for d in divisors(num)) / num
)