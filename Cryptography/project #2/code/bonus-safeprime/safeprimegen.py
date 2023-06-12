import random
from functools import lru_cache
from primality.primality import isprime
from time import time


# https://iopscience.iop.org/article/10.1088/1757-899X/1001/1/012064/pdf
# https://rosettacode.org/wiki/Miller–Rabin_primality_test
# https://www.geeksforgeeks.org/primality-test-set-3-miller-rabin/
def miller_rabin(n: int, t: int, s: int) -> bool:
    b = pow(random.randint(2, n - 1), t, n)
    if b == 1 or b == n - 1:
        return False
    for _ in range(s - 1):
        b = pow(b, 2, n)
        if b == 1:
            return True
        if b == n - 1:
            return False
    return True


# https://www.geeksforgeeks.org/python-program-for-sieve-of-eratosthenes/
@lru_cache(maxsize=None)  # memoize the prime table
def sieve_eratosthenes(n: int) -> list[int]:
    primes = [True for _ in range(n + 1)]
    __p = 2
    while __p * __p <= n:
        if primes[__p]:
            for __q in range(__p * __p, n + 1, __p):
                primes[__q] = False
        __p += 1
    return [pr for pr in range(2, n + 1) if primes[pr]]


# https://crypto.stackexchange.com/questions/60329/efficient-algorithm-for-finding-sophie-germain-primes
def is_prime(number: int) -> bool:
    # trial division with the first few primes
    for divisor in sieve_eratosthenes(100):
        rem = number % divisor
        # combined sieve: # https://eprint.iacr.org/2003/186.pdf
        if rem == 0 or rem == (divisor - 1) >> 1:
            return False
    # find s, t such that t * 2^s == n - 1
    s, t = 0, number - 1
    while t & 0b1 == 0b0:  # while even
        s += 1
        t = t >> 1  # t //= 2
    # run multiple miller-rabin tests
    for _ in range(4):
        if miller_rabin(number, t, s):
            return False
    return True


if __name__ == '__main__':
    # candidate 2047-bit Sophie Germain prime
    p = (random.getrandbits(2046) << 1) + 1
    epoch = time()
    while True:
        # https://math.stackexchange.com/questions/870626/fast-check-of-safe-primes-or-sophie-germain-primes
        if is_prime(p) and pow(4, p, (p << 1) + 1) == 1:
            # print(p)
            exitcode = 0
            if time() - epoch <= 3 * 60:  # ideal timeframe
                exitcode = 1
            if not isprime(p):  # ground truth
                exitcode = -1  # signal false positive
            exit(exitcode)
        p += 2
