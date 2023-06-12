def F_2(__power: int, __binary: bool = False) -> list:
    if __power < 1:
        return []
    upper_bound = 2 ** __power
    elements = [x for x in range(0, upper_bound)]
    if not __binary:
        return elements
    # turn decimals into binary
    return [bin(element)[2:].zfill(__power) for element in elements]


def coords(__x: int):
    # find row and column in s-box as decimal numbers as instructed
    bits = bin(__x)[2:].zfill(6)
    row = int(bits[0] + bits[5], 2)
    col = int(bits[1] + bits[2] + bits[3] + bits[4], 2)
    return row, col


def differential_uniformity(__sub_box: list):
    # x in {0, 1}^6 - {000000}, y in {0, 1}^4, z in {0, 1}^6
    F4 = F_2(4)
    F6 = F_2(6)
    F6n = F6.copy()
    F6n.pop(0)

    # compute differential uniformities
    diffs = 0
    for x in F6n:
        for y in F4:
            norm = 0
            for z in F6:
                r1, c1 = coords(z ^ x)
                r2, c2 = coords(z)
                # S(z xor x) xor S(z)
                out = __sub_box[r1][c1] ^ __sub_box[r2][c2]
                # increment the counter of this set by one if out == y
                if out == y:
                    norm += 1
            # keep current maximum
            if diffs < norm:
                diffs = norm
    print(diffs)


if __name__ == '__main__':
    s_i = [
        [0, 2, 3, 7, 9, 12, 15, 7, 6, 15, 15, 1, 7, 3, 1, 0],
        [1, 5, 6, 13, 4, 1, 5, 11, 7, 8, 7, 1, 1, 3, 2, 13],
        [5, 3, 5, 12, 11, 1, 1, 5, 13, 0, 15, 7, 2, 2, 13, 0],
        [3, 12, 3, 11, 2, 2, 2, 4, 6, 5, 5, 0, 4, 3, 1, 0]
    ]
    differential_uniformity(s_i)
