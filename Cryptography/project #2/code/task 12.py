from myfuncs import trial_division, decryptRSA


def euler_totient(__num: int) -> int:
    phi = __num * 1.0
    for factor in trial_division(__num):
        phi *= 1 - (1 / factor)
    return int(phi)


def find_secret_key(__e: int, __modulus: int) -> int:
    # brute force
    for d in range(__modulus):
        if (__e * d) % __modulus == 1:
            return d
    return 0


def main():
    ciphertext = [
        3203, 909, 3143, 5255, 5343, 3203, 909, 9958,
        5278, 5343, 9958, 5278, 4674, 909, 9958, 792,
        909, 4132, 3143, 9958, 3203, 5343, 792, 3143, 4443
    ]
    N = 11413
    e = 19
    phi = euler_totient(N)
    # find d
    d = find_secret_key(e, phi)
    if d != 0:
        print('Secret key is {}'.format(d))
        print('Decrypted message: \'{}\''.format(decryptRSA(ciphertext, d, N)))
    else:
        print('Secret key not found')


if __name__ == '__main__':
    main()
