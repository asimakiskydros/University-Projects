from math import log, exp

EULER_CONST = exp(0.5772156649015328606) * 0.5


def divisors(__num: int) -> list:
    return [d for d in range(1, __num + 1) if __num % d == 0]


def main():
    for n in range(3, 2 ** 20, 2):
        sigma = sum(divisors(n))
        natural_log = log(log(n))
        ineq = sigma * natural_log < (EULER_CONST * natural_log * natural_log + 0.74) * n
        if ineq is False:
            print('Inequality breaks for', n)
            return
    print('Inequality was true for all tested odd integers')


if __name__ == '__main__':
    main()
