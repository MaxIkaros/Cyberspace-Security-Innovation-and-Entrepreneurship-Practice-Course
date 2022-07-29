# [Meow Hash: Symmetry](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/Meow-Hash-Symmetry)

## 对应题目

![image-20220725151623889](README/assets/image-20220725151623889.png)

Find a 64-byte message under some *k* fulfilling that their hash value is symmetrical.

## 项目代码说明

### 总体思路

如上图所示，在已经合并非对称长度字段之后但在合并任何消息字节之前使状态对称（即为全0），然后逆向运行Meow Hash的Absorption function，从而构造出一个全新的密钥，该密钥将在长度被吸收后达到对称状态。同时，`message`要保证是abc-symmetrical的。

![image-20220729154238475](README/assets/image-20220729154238475.png)

上图为64 Bytes的信息的Hash过程。

- 实际上，该代码对长度为32、64、96、128、160、192、224 Bytes的`message`均可运行。

### 细节注意

对于

```c
#define aesdec(A, B)        A = _mm_aesdec_si128(A, B)
```

的逆向，不是直接`aesenc`

```c
#define aesenc(A, B)	    A = _mm_aesenc_si128(A, B)
```

就可以了的，而是需要`inv_aesdec`

```c
static meow_u128 xmm_allzero = _mm_setzero_si128(); // All zero
#define pxor(A, B)          A = _mm_xor_si128(A, B)
#define inv_mixcol(A)		A = _mm_aesimc_si128(A) // AES-128-ECB invert mix columns
#define MixColumns(A)		A = _mm_aesdeclast_si128(A, xmm_allzero); A = _mm_aesenc_si128(A, xmm_allzero) // AES-128-ECB mix columns

#define inv_aesdec(A, B) \
pxor(A, B);\ /*异或*/
MixColumns(A);\ /*列混合*/
aesenc(A, xmm_allzero);\ /*行移位、S盒置换、列混合（最后的“异或”操作是与全0串进行的，不改变最终结果）*/
inv_mixcol(A) /*逆列混合*/
```

才能保证逆向。因为对于`_mm_aesdec_si128`来说，它是这样运行的：

```c
a[127:0] := InvShiftRows(a[127:0])
a[127:0] := InvSubBytes(a[127:0])
a[127:0] := InvMixColumns(a[127:0])
dst[127:0] := a[127:0] XOR RoundKey[127:0]
```

而`_mm_aesenc_si128`是这样运行的：

```c
a[127:0] := ShiftRows(a[127:0])
a[127:0] := SubBytes(a[127:0])
a[127:0] := MixColumns(a[127:0])
dst[127:0] := a[127:0] XOR RoundKey[127:0]
```

显然`_mm_aesdec_si128`不是直接地逆向运行`_mm_aesenc_si128`的，而是采用“等价解密算法”的方式来实现解密的，在此不作过多讲述。因而我们需要另行实现对`_mm_aesdec_si128`的逆向运行，如`inv_aesdec`所示。

## 运行指导

方法1：点击[Meow-Hash-Symmetry.exe](Meow-Hash-Symmetry.exe)运行；（默认message为`“abcdefghabcdefghaijklmnhaijklmnhopqrstuvopqrstuvowxyz01vowxyz01v”`）

方法2：在Visual Studio 2022中打开[Meow-Hash-Symmetry.sln](Meow-Hash-Symmetry.sln)，先Ctrl+Shift+B后Ctrl+F5。

## 代码运行全过程截图

当message满足`“abcdefghabcdefghaijklmnhaijklmnhopqrstuvopqrstuvowxyz01vowxyz01v”`的格式（其中，以上出现的26个字母和“0”“1”两个数字分别代表28个不同的字符（可以相同））即为“abc-symmetrical message”。

![image-20220729150327087](README/assets/image-20220729150327087.png)

![image-20220729150743531](README/assets/image-20220729150743531.png)

![image-20220729150807765](README/assets/image-20220729150807765.png)

其中：

- `Message`：需要Hash的信息，需要满足abc-symmetrical；
- `Message size`：`Message`的长度（单位为Byte），题目所要求的是64；
- `Generated key`：经过程序运行后所得到的key，为16进制的格式（中间空格不是key的一部分）；
- `Hash of the message above`：`Message`Hash之后的结果，为16进制的格式（中间空格不是key的一部分），显然是对称的。

## 具体贡献说明及贡献排序

全部代码及对应思路：[葛萧遥-202000460091](https://github.com/MaxIkaros)。

## 参考资料

1. [Meow hash 0.5/calico](https://github.com/cmuratori/meow_hash)；
2. [Cryptanalysis of Meow Hash](https://peter.website/meow-hash-cryptanalysis)；
3. [Intel AES-NI使用入门](https://www.anquanke.com/post/id/260323)；
4. 2022年6月10日上课时的课件和录屏。
