from random import randint
from math import gcd
from myfuncs import mod_pow


def is_carmichael(__num: int) -> bool:
    for alpha in range(2, __num):
        if gcd(alpha, __num) == 1:
            if mod_pow(alpha, __num - 1, __num) != 1:
                return False
    return True


def is_carmichael_monte_carlo(__num: int, __cycles: int) -> bool:
    for _ in range(__cycles):
        alpha = randint(2, __num - 1)
        if gcd(alpha, __num) == 1 and mod_pow(alpha, __num - 1, __num) != 1:
            return False
    return True


def blind_search(__start: int, __cycles: int = 0) -> int:
    while True:
        __start += 2
        if (__cycles < 1 and is_carmichael(__start)) or \
                is_carmichael_monte_carlo(__start, __cycles):
            return __start


def main():
    # test for carmichael-ity
    n1 = 9999109081
    n2 = 6553130926752006031481761
    # print(is_carmichael_monte_carlo(n1, 1000000))
    # print(is_carmichael_monte_carlo(n2, 1000000))
    print('{} is{} a carmichael number'.format(n1, '' if is_carmichael(n1) else ' not'))
    print('{} is{} a carmichael number'.format(n2, '' if is_carmichael(n2) else ' not'))
    # brute force each larger odd integer for carmichael-ity
    print('Next largest carmichael number: {}'.format(blind_search(n2, 1000000)))


if __name__ == '__main__':
    main()
