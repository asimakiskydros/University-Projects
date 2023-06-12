from myfuncs import trial_division


def main():
    n1 = 2 ** 62 - 1
    n2 = 2 ** 102 - 1
    print('{}: {}'.format(n1, trial_division(n1)))
    print('{}: {}'.format(n2, trial_division(n2)))


if __name__ == '__main__':
    main()
