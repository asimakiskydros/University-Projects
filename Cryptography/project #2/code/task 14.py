from myfuncs import mod_pow


def main():
    N = 899
    e = 839
    message = 3
    signature = 301
    alpha = mod_pow(signature, e, N)
    print('Given signature for message {} is: {}'.format(message, signature))
    print('Validation gives: {}'.format(alpha))
    print('\nDigital signature is {}valid'.format('' if alpha == message else 'in'))


if __name__ == '__main__':
    main()
