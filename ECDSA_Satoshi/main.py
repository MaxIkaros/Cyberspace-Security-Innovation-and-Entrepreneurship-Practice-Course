# ECDSA_Satoshi
# 思路参考（部分）：https://qa.1r1g.com/sf/ask/2175192071/

import random
import math
from collections import namedtuple

# Create a simple Point class to represent the affine points.
Point = namedtuple("Point", "x y")

# The point at infinity (origin for the group law).
# O = 'Origin'
O = Point(0, 0)

# 椭圆曲线参数
p = 17
a = 2
b = 2
G = Point(5, 1)
n = 19


def gcd(aa, bb):
    """
    # 求最大公因子
    # math.gcd(eval(aa), eval(bb))

    :param aa:
    :param bb:
    :return: gcd(aa, bb)
    """
    while aa != 0:
        aa, bb = bb % aa, aa
    return bb


def IntModInverse(bb, _n, show=False):
    """
    # 求模逆的扩展欧几里得算法
    # calc : b^(-1) mod m

    :param bb: 要增长模逆的数
    :param _n: 模数
    :param show: 用于表示是否需要打印过程出来
    :return: bb^(-1) mod _n
    """
    while bb <= 0:
        bb += _n
    if gcd(_n, bb) != 1: # 若_n和bb不互质
        return None # 则不存在模逆
    a1, a2, a3 = 1, 0, _n
    b1, b2, b3 = 0, 1, bb
    if show:
        print('-' * 54)
        print("|{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}|".format("Q", "A1", "A2", "A3", "B1", "B2", "B3"))
        print("|{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}|".format("-", a1, a2, a3, b1, b2, b3))
    while True:
        q = a3 // b3
        b1, b2, b3, a1, a2, a3 = (a1 - q * b1), (a2 - q * b2), (a3 - q * b3), b1, b2, b3
        if show:
            print("|{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}\t{:^5}|".format(q, a1, a2, a3, b1, b2, b3))
        if b3 == 0:
            return None
        elif b3 == 1:
            break
    if show:
        print("-" * 54)
    return b2 % _n


def isValid(P):
    """
    Determine whether we have a valid representation of a point
    on our curve.  We assume that the x and y coordinates
    are always reduced modulo p, so that we can compare
    two points for equality with a simple ==.

    :param P: Point P
    :return: True / False
    """
    if P == O:
        return True
    else:
        return (P.y ** 2 - (P.x ** 3 + a * P.x + b)) % p == 0 and 0 <= P.x < p and 0 <= P.y < p


def EccInv(P):
    """
    点P在椭圆曲线上的对称点（关于y轴对称）

    :param P: 椭圆曲线上的点P
    :return: P在椭圆曲线上的对称点
    """
    if P == O:
        return P
    return Point(P.x, (-P.y) % p)


def EccAdd(P, Q):
    """
    # 椭圆曲线上的加法
    # calc : P + Q

    :param P: 椭圆曲线上的P点
    :param Q: 椭圆曲线上的Q点
    :return: P + Q
    """
    if not (isValid(P) and isValid(Q)):
        raise ValueError("Invalid inputs of Point P or Q")

    # Deal with the special cases where either P, Q, or P + Q is
    # the origin.
    if P == O:
        res = Q
    elif Q == O:
        res = P
    elif Q == EccInv(P):
        res = O
    else:  # Cases not involving the origin.
        if P == Q:
            dydx = ((3 * P.x ** 2 + a) * IntModInverse(2 * P.y, p)) % p
        else:
            dydx = ((Q.y - P.y) * IntModInverse(Q.x - P.x, p)) % p
        x = (dydx ** 2 - P.x - Q.x) % p
        y = (dydx * (P.x - x) - P.y) % p
        res = Point(x, y)

    # The above computations *should* have given us another point
    # on the curve.
    assert isValid(res)
    return res


def EccPointMul(k, P):
    """
    椭圆曲线上点的数乘

    :param k: 数值
    :param P: 点
    :return: k * P
    """
    if k == 0:
        return 0
    if k == 1:
        return P
    Result = P
    while k >= 2:
        Result = EccAdd(Result, P)
        k -= 1
    return Result


def Sign(m_essage):
    """
    ECDSA——Sign

    :param m_essage: m
    :return:
    """
    global n, G, d
    k = random.randint(1, n - 1)
    R = EccPointMul(k, G)
    r = R.x % n
    if r == 0:
        raise ValueError("Invalid inputs of r")
    e = hash(m_essage)
    s = (IntModInverse(k, n) * (e + d * r)) % n
    Signature = Point(r, s)
    return Signature


def Verify(_Signature):
    """
    验证签名（正常步骤）
    ECDSA——Verify

    :param _Signature: 生成的签名(r, s)
    :return: True / False
    """
    # global KG_P, n, G, m
    # e = hash(m)
    # w = IntModInverse(_Signature.y, n) # w = s^(-1) mod n
    # hokaSignature = EccAdd(EccPointMul((e * w) % n, G), EccPointMul((_Signature.x * w) % n, KG_p))
    # if hokaSignature != O and hokaSignature.x % n == _Signature.x:
    #     return True
    # else:
    #     return False
    global m
    e = hash(m)
    return Verify_without_e(e, _Signature)  # 反正都一样，放一块儿了


def Verify_without_e(e, _Signature):
    """
    验证（伪造）签名

    :param e: = hash(m)
    :param _Signature: (r, s)
    :return: True / False
    """
    global KG_P, n, G
    w = IntModInverse(_Signature.y, n)  # w = s^(-1) mod n
    hokano_signature = EccAdd(EccPointMul((e * w) % n, G), EccPointMul((_Signature.x * w) % n, KG_P))
    if hokano_signature != O and hokano_signature.x % n == _Signature.x:
        return True
    else:
        return False


def ForgeSign(_Signature):
    """
    伪造签名

    :param _Signature: (r, s)
    :return: True / False
    """
    global n, G, KG_P
    u, v = random.randint(1, n - 1), random.randint(1, n - 1)
    RR = EccAdd(EccPointMul(u, G), EccPointMul(v, KG_P))

    rr = RR.x % n
    ee = (rr * u * IntModInverse(v, n)) % n
    ss = (rr * IntModInverse(v, n)) % n
    hokano_signature = Point(rr, ss)

    print("\tu = {} \n\tv = {}".format(u, v))

    if Verify_without_e(ee, hokano_signature):
        return True
    else:
        return False


if __name__ == '__main__':
    # 信息参数
    m = "Satoshi"
    e = hash(m)
    d = 7
    KG_P = EccPointMul(d, G)

    # 正常签名流程
    Signature = Sign(m)
    print("Initial Signature: \n\tr = {}\n\ts = {}\n".format(Signature.x, Signature.y))
    # 正常签名验证
    print("Verify Signature: ")
    if Verify(Signature):
        print("\tTRUE\n")
    else:
        print("\tFALSE\n")

    # 伪造签名并验证
    print("Forge Signature: ")
    if ForgeSign(Signature):
        print("\tTRUE\n")
    else:
        print("\tFALSE\n")


