from random import getrandbits


def circular_shift(__bits: str, __positions: int) -> str:
    while __positions > 0:
        __bits = __bits[1:] + __bits[0]
        __positions -= 1
    return __bits


def encrypt(__plaintext: str) -> str:
    p = int(__plaintext, 2)
    p6 = int(circular_shift(__plaintext, 6), 2)
    p10 = int(circular_shift(__plaintext, 10), 2)
    ciphertext = p ^ p6 ^ p10
    # return the ciphertext in its binary representation,
    # without the '0b' prefix and at a fixed 16-bits length
    return bin(ciphertext)[2:].zfill(16)


def decrypt(__ciphertext: str) -> str:
    c = [int(bit) for bit in __ciphertext]
    # receive: c = C0C1C2C3C4....C15
    # return: m = M0M1M2....M15
    plaintext = ''
    for i in range(16):
        mi = c[(i - 4) % 16] ^ c[(i - 2) % 16] ^ c[i] ^ c[(i + 2) % 16] ^ c[(i + 4) % 16]
        plaintext += str(mi)
    return plaintext


def main():
    plaintext = bin(getrandbits(16))[2:].zfill(16)
    print(" original: ", plaintext)
    ciphertext = encrypt(plaintext)
    print("encrypted: ", ciphertext)
    m = decrypt(ciphertext)
    print("decrypted: ", m)
    print("correct decryption: ", plaintext == m)


if __name__ == '__main__':
    main()
