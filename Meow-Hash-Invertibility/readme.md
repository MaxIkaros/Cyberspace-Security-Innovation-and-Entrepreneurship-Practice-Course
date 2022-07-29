# [Meow Hash: Invertibility](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/Meow-Hash-Invertibility)

## 题目对应

![image-20220725151357310](README/assets/image-20220725151357310.png)

Find a key with hash value “*sdu_cst_20220610*” under a message composed of *your name* followed by *your student ID*. For example, “*San Zhan 202000460001*”.

## 项目代码说明

参照[meow_hash_x64_aesni.h](meow_hash_x64_aesni.h)中的`MeowHash`函数，对Hash过程进行逆序（犹以其中的AES为最）而诞生了main.cpp中的`InvToGetKey`函数。

![image-20220729152126265](README/assets/image-20220729152126265.png)

上图中从左到右为不足32 Bytes的`message`的Hash过程（姓名+学号的内容一般不足32 Bytes），因而`InvToGetKey`函数是从右到左实现上图的过程的。

- 实际上，该代码对<姓氏全拼><空格><名字全拼><空格><12位学号>总体小于32 Bytes的`message`有效。

## 运行指导

方法1：点击[Meow-Hash-Invertibility.exe](Meow-Hash-Invertibility.exe)运行；

方法2：在Visual Studio 2022中打开[Meow-Hash-Invertibility.sln](Meow-Hash-Invertibility.sln)，先Ctrl+Shift+B后Ctrl+F5。

## 代码运行全过程截图

![image-20220729151641311](README/assets/image-20220729151641311.png)

其中：

- `Message`：需要Hash的信息，题目所要求的是“姓名+学号”；
- `Hashed Message`：Hash值，此处固定为`sdu_cst_20220610`；
- `Generated key`：经过程序运行后所得到的key，为16进制的格式（中间空格不是key的一部分）（由于每次填充的内容不同，因而所生成的Generated key不同）；
- `Hash of the message above`：验证所生成的key是否可行。显而易见，可行。

## 具体贡献说明及贡献排序

全部代码及对应思路：[葛萧遥-202000460091](https://github.com/MaxIkaros)。

## 参考资料

1. [Meow hash 0.5/calico](https://github.com/cmuratori/meow_hash)；
2. [Cryptanalysis of Meow Hash](https://peter.website/meow-hash-cryptanalysis)；
3. [Intel AES-NI使用入门](https://www.anquanke.com/post/id/260323)；
4. 2022年6月10日上课时的课件和录屏。
