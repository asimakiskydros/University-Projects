from myfuncs import mod_pow


def actor(__name: str, __g: int, __p: int, __secret_key: int, __power: int = None) -> int:
    print('[{}]: knows {},{}, chooses {} as their secret key.'.format(__name, __g, __p, __secret_key))

    if __power is None:
        __power = mod_pow(__g, __secret_key, __p)
        print('[{}]: computes and publishes {}.'.format(__name, __power))
        return __power
    else:
        print('[{}]: receives {}.'.format(__name, __power))
        shared_key = mod_pow(__power, __secret_key, __p)
        __other_power = mod_pow(__g, __secret_key, __p)
        print('[{}]: computes and publishes {}.'.format(__name, __other_power))
        print('\nShared key is now {}. '.format(shared_key))
        return __other_power


def main():
    base = 3
    prime = 101
    message_alice = actor('Alice', base, prime, 77)
    actor('Bob', base, prime, 91, message_alice)


if __name__ == '__main__':
    main()
