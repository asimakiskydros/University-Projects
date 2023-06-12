from alphabet_cipher import alphabet_table, inv_table


def schedulerRC4(__seed: list) -> list:
    length = len(__seed)
    # initialize s to the identity list
    s = [i for i in range(256)]
    # construct transfer array s
    j = 0
    for i in range(256):
        j = (j + s[i] + __seed[i % length]) % 256
        # swap
        s[i], s[j] = s[j], s[i]
    return s


def keystreamRC4(__s: list, __plaintext_length: int) -> list:
    plen = __plaintext_length
    # generate keystream
    i = j = 0
    keystream = []
    while plen > 0:
        i = (i + 1) % 256
        j = (j + __s[i]) % 256
        # swap
        __s[i], __s[j] = __s[j], __s[i]
        keystream.append(__s[(__s[i] + __s[j]) % 256])
        plen -= 1
    # normalize to "bytes" (bit length 5)
    return [k % 32 for k in keystream]


def RC4(__plaintext: str, __key: str) -> str:
    # get codes of plaintext
    plainbits = [alphabet_table.get(letter) for letter in __plaintext]
    # spawn scheduler seed from initial key
    seed = [alphabet_table.get(letter) for letter in __key]
    # generate keystream
    keystream = keystreamRC4(schedulerRC4(seed), len(__plaintext))
    # byte-wise xor
    ciphertext = ''
    for byte, key in zip(plainbits, keystream):
        # translate the xor back to letters and add to ciphertext
        ciphertext += inv_table.get(byte ^ key)
    return ciphertext


def main():
    # declare message
    plaintext = "MISTAKESAREASSERIOUSASTHERESULTSTHEYCAUSE"
    key = "HOUSE"
    print(" original: ", plaintext)

    # encrypt
    ciphertext = RC4(plaintext, key)
    print("encrypted: ", ciphertext)

    # decrypt and check validity
    msg = RC4(ciphertext, key)
    print("decrypted: ", msg)
    print("correct decryption: ", plaintext == msg)


if __name__ == '__main__':
    main()
