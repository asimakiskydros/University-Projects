from random import randint
from alphabet_cipher import alphabet_table, inv_table


def text2bits(__text: str, __block_size: int, __table: dict) -> str:
    bits = ''
    for letter in __text:
        # convert the code into binary and then add these bits to m
        bits += bin(__table.get(letter))[2:].zfill(__block_size)
    return bits


def bits2text(__bits: str, __block_size: int, __table: dict) -> str:
    text = ''
    block = ''
    for bit in __bits:
        # gather a "byte", do the conversion to decimal, append the letter
        # to the output and then continue to the next "byte"
        block += bit
        if len(block) == __block_size:
            text += __table.get(int(block, 2))
            block = ''
    return text


def OTP(__plaintext: str, __key: str = None):
    # get bits of plaintext
    plainbits = text2bits(__plaintext, 5, alphabet_table)
    length = len(plainbits)
    # if no key is given, generate one
    # note that decrypting using otp demands the correct key to be given
    key = randint(0, 2 ** length - 1) if __key is None else int(__key, 2)
    cipherbits = bin(int(plainbits, 2) ^ key)[2:].zfill(length)
    return bin(key)[2:].zfill(length), bits2text(cipherbits, 5, inv_table)


def main():
    # declare message and get bits
    plaintext = 'SOMETIMES-YOU-STILL-LOSE'
    print(" original: ", plaintext)

    # encrypt message
    key, ciphertext = OTP(plaintext)
    print("encrypted: ", ciphertext)

    # decrypt message and check validity
    dummy, msg = OTP(ciphertext, key)
    print("decrypted: ", msg)
    print("correct decryption: ", msg == plaintext)


if __name__ == '__main__':
    main()
