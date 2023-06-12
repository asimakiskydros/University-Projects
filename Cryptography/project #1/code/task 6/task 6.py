def trial_division(__num: int):
    # based on the implementation shown in the textbook
    L = []
    while __num % 2 == 0:
        L.append(2)
        __num //= 2
    factor = 3
    while factor * factor <= __num:
        if __num % factor == 0:
            L.append(factor)
            __num //= factor
        else:
            factor += 2
    if __num != 1:
        L.append(__num)
    return L


def divisors(__num: int) -> list:
    return [d for d in range(1, __num + 1) if __num % d == 0]


def mu(__num: int) -> int:
    if __num < 2:
        return __num == 1
    return (-1) ** len(trial_division(__num))


def N_2(__num: int):
    print(
        sum(mu(d) * 2 ** (__num / d) for d in divisors(__num)) / __num
    )


if __name__ == '__main__':
    N_2(10)
