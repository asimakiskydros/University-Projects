from random import randint
from math import gcd
from myfuncs import mod_pow


def fermat_test(__num: int):
    COMPOSITE = True
    PROB_PRIME = False
    base = randint(2, __num - 1)
    if gcd(base, __num) > 1:
        return COMPOSITE, 0
    if mod_pow(base, __num - 1, __num) == 1:
        return PROB_PRIME, base
    return COMPOSITE, 0


def fermat_monte_carlo(__num: int, __cycles: int):
    COMPOSITE = True
    PRIME = False
    j = 0
    for i in range(1, __cycles + 1):
        base = randint(2, __num - 1)
        if gcd(base, __num) > 1:
            return COMPOSITE, 1
        if mod_pow(base, __num - 1, __num) == 1:
            j += 1
            if j == __cycles:
                return PRIME, 1 - 2 ** (-__cycles)
    return COMPOSITE, 1


def main():
    body = 835335 * (2 ** 39014)
    state1, respect1 = fermat_test(body - 1)
    state2, respect2 = fermat_test(body + 1)
    print('p1 is {}'.format('composite' if state1 else 'probable prime'))
    print('p2 is {}'.format('composite' if state2 else 'probable prime'))
    # they are both probable primes


if __name__ == '__main__':
    main()
