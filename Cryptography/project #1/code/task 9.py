from Crypto.Cipher import AES
import random


def test(__cipher, __messages: list) -> float:
    hits = 0
    xor_length = 0
    msgs_length = len(__messages)
    for i in range(msgs_length - 1):
        # encrypt and get ciphertext in bytes
        ctb1 = __cipher.encrypt(__messages[i].to_bytes(256, 'little'))
        ctb2 = __cipher.encrypt(__messages[i + 1].to_bytes(256, 'little'))
        # convert to integers
        cti1 = int.from_bytes(ctb1, 'little')
        cti2 = int.from_bytes(ctb2, 'little')
        # xor of ciphertexts show in how many bits they differ
        # '1' -> bit pair differed (by definition)
        xor = bin(cti1 ^ cti2)
        xor_length = max(xor_length, len(xor))
        hits += xor.count('1')
    # return hit ratio
    return hits * 100 / xor_length / msgs_length


def main():
    # generate 100 256-bit messages such that each differs
    # from its neighbors in one random bit
    messages = [random.getrandbits(256)]
    for _ in range(100):
        pos = random.randint(0, 255)
        msg = messages[-1] ^ (1 << pos)
        messages.append(msg)
    # create AES ciphers and run the tests
    key = b'nan ichir gelair'
    iv = b'ochedin valannor'
    AES_ECB = AES.new(key, AES.MODE_ECB)
    AES_CBC = AES.new(key, AES.MODE_CBC, iv)
    print('avalanche effect on AES using ECB: {:.2f}%'.format(test(AES_ECB, messages)))
    print('avalanche effect on AES using CBC: {:.2f}%'.format(test(AES_CBC, messages)))


if __name__ == '__main__':
    main()
