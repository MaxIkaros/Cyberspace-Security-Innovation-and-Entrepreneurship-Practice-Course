import random

T_j = []
for i in range(0, 16):
    T_j.append(0)
    T_j[i] = 0x79cc4519
for i in range(16, 64):
    T_j.append(0)
    T_j[i] = 0x7a879d8a

iv = int("7380166f4914b2b9172442d7da8a0600a96f30bc163138aae38dee4db0fb0e4e", 16)
arr = []
for i in range(0, 8):
    arr.append(0)
    arr[i] = (iv >> ((7 - i) * 32)) & 0xFFFFFFFF
iv = arr


def str_2_byte(msg):  # string to bytes
    ml = len(msg)
    msg_byte = []
    msg_bytearray = msg.encode('utf-8')
    for i in range(ml):
        msg_byte.append(msg_bytearray[i])
    return msg_byte


def byte_2_str(msg):  # bytes to string
    ml = len(msg)
    str1 = b""
    for i in range(ml):
        str1 += b'%c' % msg[i]
    return str1.decode('utf-8')


def hex_2_byte(msg):  # hex to bytes
    ml = len(msg)
    if ml % 2 != 0:
        msg = '0' + msg
    ml = int(len(msg) / 2)
    msg_byte = []
    for i in range(ml):
        msg_byte.append(int(msg[i * 2:i * 2 + 2], 16))
    return msg_byte


def byte_2_hex(msg):  # bytes to hex
    ml = len(msg)
    hexstr = ""
    for i in range(ml):
        hexstr = hexstr + ('%02x' % msg[i])
    return hexstr


def shift_left(a, num):
    num = num % 32
    return ((a << num) & 0xFFFFFFFF) | ((a & 0xFFFFFFFF) >> (32 - num))


def FF_j(X, Y, Z, j):
    if 0 <= j and j < 16:
        ret = X ^ Y ^ Z
    elif 16 <= j and j < 64:
        ret = (X & Y) | (X & Z) | (Y & Z)
    return ret


def GG_j(X, Y, Z, j):
    if 0 <= j and j < 16:
        ret = X ^ Y ^ Z
    elif 16 <= j and j < 64:
        # ret = (X | Y) & ((2 ** 32 - 1 - X) | Z)
        ret = (X & Y) | ((~ X) & Z)
    return ret


def P_0(X):
    return X ^ (shift_left(X, 9)) ^ (shift_left(X, 17))


def P_1(X):
    return X ^ (shift_left(X, 15)) ^ (shift_left(X, 23))


def CF(V, B):
    W_j = []
    for i in range(16):
        const = 0x1000000
        temp_ctr = 0
        for k in range(i * 4, (i + 1) * 4):
            temp_ctr = temp_ctr + B[k] * const
            const = int(const / 0x100)
        W_j.append(temp_ctr)

    for j in range(16, 68):
        W_j.append(0)
        W_j[j] = P_1(W_j[j - 16] ^ W_j[j - 9] ^ (shift_left(W_j[j - 3], 15))) ^ (shift_left(W_j[j - 13], 7)) ^ W_j[
            j - 6]

    W_1 = []
    for j in range(0, 64):
        W_1.append(0)
        W_1[j] = W_j[j] ^ W_j[j + 4]

    A, B, C, D, E, F, G, H = V

    for j in range(0, 64):
        SS1 = shift_left(((shift_left(A, 12)) + E + (shift_left(T_j[j], j))) & 0xFFFFFFFF, 7)
        SS2 = SS1 ^ (shift_left(A, 12))
        TT1 = (FF_j(A, B, C, j) + D + SS2 + W_1[j]) & 0xFFFFFFFF
        TT2 = (GG_j(E, F, G, j) + H + SS1 + W_j[j]) & 0xFFFFFFFF
        D = C
        C = shift_left(B, 9)
        B = A
        A = TT1
        H = G
        G = shift_left(F, 19)
        F = E
        E = P_0(TT2)

        A = A & 0xFFFFFFFF
        B = B & 0xFFFFFFFF
        C = C & 0xFFFFFFFF
        D = D & 0xFFFFFFFF
        E = E & 0xFFFFFFFF
        F = F & 0xFFFFFFFF
        G = G & 0xFFFFFFFF
        H = H & 0xFFFFFFFF

    V_i = []
    V_i.append(A ^ V[0])
    V_i.append(B ^ V[1])
    V_i.append(C ^ V[2])
    V_i.append(D ^ V[3])
    V_i.append(E ^ V[4])
    V_i.append(F ^ V[5])
    V_i.append(G ^ V[6])
    V_i.append(H ^ V[7])
    return V_i


def hash_val(msg):
    length = len(msg)
    reserve_val = length % 64
    msg.append(0x80)
    reserve_val = reserve_val + 1
    const = 56
    if reserve_val > const:
        const = const + 64

    for i in range(reserve_val, const):
        msg.append(0x00)

    length2 = (length) * 8
    length3 = [length2 % 0x100]
    for i in range(7):
        length2 = int(length2 / 0x100)
        length3.append(length2 % 0x100)
    for i in range(8):
        msg.append(length3[7 - i])

    group_num = round(len(msg) / 64)

    B = []
    for i in range(0, group_num):
        B.append(msg[i * 64:(i + 1) * 64])

    V = []
    V.append(iv)
    for i in range(0, group_num):
        V.append(CF(V[i], B[i]))

    y = V[i + 1]
    result = ""
    for i in y:
        result = '%s%08x' % (result, i)
    return result


def SM3(msg, Hex_or_str=0) -> object:
    if (Hex_or_str):
        msg_byte = hex_2_byte(msg)
    else:
        msg_byte = str_2_byte(msg)
    return hash_val(msg_byte)


lst = set()
flag = 1
while (flag):
    i = str(random.randint(0, 2 ** 256))
    a = SM3(i, 0)
    b = a[0:16]
    if (b in lst):
        flag = 0
        print(b)
    else:
        lst.add(b)