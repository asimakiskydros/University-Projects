from myfuncs import mod_pow


def main():
    base = 5
    exponent = 77
    modulus = 19
    power = mod_pow(base, exponent, modulus)
    print('({}^{}) mod {} is {}'.format(base, exponent, modulus, power))


if __name__ == '__main__':
    main()
