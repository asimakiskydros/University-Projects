from myfuncs import trial_division
from math import gcd, sqrt
from numpy import cbrt
from random import getrandbits
import multiprocessing


def lehman_factoring(__num: int) -> int:
    cbrt_num = cbrt(__num * 0.1)
    cbrt_num2 = cbrt_num * cbrt_num * 0.5
    for factor in trial_division(__num):
        if factor < cbrt_num:
            return factor
    for k in range(1, int(cbrt_num) + 1):
        kn4 = 4 * k * __num
        sqrt_kn4 = 2 * sqrt(k * __num)
        for a in range(int(sqrt_kn4) + 1, int((kn4 + cbrt_num2) / sqrt_kn4) + 1):
            b = sqrt(a * a - kn4)
            if b.is_integer():
                factor = gcd(a - int(b), __num)
                if factor != 1 and factor != __num:  # ignore trivial factors
                    return factor
    return __num  # number is prime, return itself


def test_lehman(__tests: int, __bit_length: int, __timeframe: int):
    success = 0
    for _ in range(__tests):
        # build a random 100-bit odd integer
        number = getrandbits(__bit_length)
        number += int(number % 2 == 0)
        # run the algorithm in a thread so that we can terminate it early
        # > 10 seconds means failure so there's no point in waiting
        proc = multiprocessing.Process(target=lehman_factoring, name="lehman", args=(number,))
        proc.start()
        proc.join(__timeframe)
        if proc.is_alive():
            # manual termination; lehman failed the test
            proc.terminate()
            proc.join()
        else:
            # lehman passed the test
            success += 1
    print('success ratio: {}/{}'.format(success, __tests))
    print('lehman\'s method scores {:.2f}%'.format(success * 100 / __tests))


if __name__ == '__main__':
    # test_lehman(1000, 100, 10)  # 189/1000
    test_lehman(1000, 100, 20)  # 206/1000
