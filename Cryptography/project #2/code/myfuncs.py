def mod_pow(__base: int, __exponent: int, __modulus: int) -> int:
    # based on the implementation shown in the textbook
    result = 1
    while __exponent > 0:
        if __exponent % 2 == 1:
            result = (result * __base) % __modulus
        __exponent //= 2
        __base = (__base * __base) % __modulus
    return result


def decryptRSA(__ciphertext: list[int], __secret_key: int, __modulus: int) -> str:
    plaintext = [mod_pow(code, __secret_key, __modulus) for code in __ciphertext]
    # print message
    message = ''
    for code in plaintext:
        message += chr(code)
    return message


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
