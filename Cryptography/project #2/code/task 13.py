from myfuncs import mod_pow, decryptRSA


def continued_fraction(__numerator: int, __denominator: int) -> list:
    # thanks to https://planetcalc.com/8456/
    coefficients = []
    while __denominator != 0:
        rem = __numerator % __denominator
        coefficients.append((__numerator - rem) // __denominator)
        __numerator = __denominator
        __denominator = rem
    return coefficients


def convergent_ratio(__coefficients: list):
    # thanks to https://planetcalc.com/8456/
    length = len(__coefficients)
    n = __coefficients.pop()
    d = 1
    while length > 1:
        r = d
        d = n
        length -= 1
        n = __coefficients[length - 1] * n + r
    return n, d


def wiener_attack(__e: int, __modulus: int) -> int:
    coefficients = continued_fraction(__e, __modulus)
    for i in range(2, len(coefficients) + 1):
        num, den = convergent_ratio(coefficients[:i])
        if mod_pow(2, __e * den, __modulus) == 2:
            return den
    return 0  # fail


def main():
    N = 194749497518847283
    e = 50736902528669041
    d = wiener_attack(e, N)
    # decoded from base64 using https://www.base64decode.org
    C = [
        47406263192693509, 51065178201172223, 30260565235128704, 82385963334404268,
        8169156663927929, 47406263192693509, 178275977336696442, 134434295894803806,
        112111571835512307, 119391151761050882, 30260565235128704, 82385963334404268,
        134434295894803806, 47406263192693509, 45815320972560202, 174632229312041248,
        30260565235128704, 47406263192693509, 119391151761050882, 57208077766585306,
        134434295894803806, 47406263192693509, 119391151761050882, 47406263192693509,
        112111571835512307, 52882851026072507, 119391151761050882, 57208077766585306,
        119391151761050882, 112111571835512307, 8169156663927929, 134434295894803806,
        57208077766585306, 47406263192693509, 185582105275050932, 174632229312041248,
        134434295894803806, 82385963334404268, 172565386393443624, 106356501893546401,
        8169156663927929, 47406263192693509, 10361059720610816, 134434295894803806,
        119391151761050882, 172565386393443624, 47406263192693509, 8169156663927929,
        52882851026072507, 119391151761050882, 8169156663927929, 47406263192693509,
        45815320972560202, 174632229312041248, 30260565235128704, 47406263192693509,
        52882851026072507, 119391151761050882, 111523408212481879, 134434295894803806,
        47406263192693509, 112111571835512307, 52882851026072507, 119391151761050882,
        57208077766585306, 119391151761050882, 112111571835512307, 8169156663927929,
        134434295894803806, 57208077766585306
    ]
    if d != 0:
        print(decryptRSA(C, d, N))
    else:
        print('Secret key not found')


if __name__ == '__main__':
    main()
