from random import randint
from math import gcd


def F(__x: int, __modulus: int) -> int:
    return (__x * __x + 1) % __modulus


def pollard_floyd_factorization(__num: int) -> int:
    x = y = randint(2, __num - 1)
    divisor = 0
    while divisor == 0 or __num % divisor != 0:
        x = F(x, __num)
        y = F(F(y, __num), __num)
        divisor = abs(x - y)
        if 1 < gcd(divisor, __num) < __num:
            return divisor
    return -1


def main():
    number = 2 ** 257 - 1
    d = -1
    while d == -1:
        d = pollard_floyd_factorization(number)
    print(d)
    print('This factor is {}trivial'.format('' if d == number or d == 1 else 'non-'))
    # returns:
    # 58688966023081812065444977579774915030964767283763622307777403750890279429696


if __name__ == '__main__':
    main()
