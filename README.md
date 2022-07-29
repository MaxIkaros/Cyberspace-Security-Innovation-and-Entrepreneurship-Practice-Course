# Cyberspace Security Innovation and Entrepreneurship Practice Course

山东大学网络空间安全学院（研究院）2022年网络空间安全创新创业实践课程相关project代码

------

## 小组成员：

| 小组成员姓名 | <!--小组成员学号--> |                        Github账户名称                        |
| :----------: | :-----------------: | :----------------------------------------------------------: |
|    葛萧遥    |     <!--2020-->     |    [**MaxIkaros** Max Kot](https://github.com/MaxIkaros)     |
|    贾晨铮    |     <!--2020-->     |    [**cipeizheng** Ci_pei](https://github.com/cipeizheng)    |
|    陈思宇    |     <!--2020-->     |     [**2001AlexChen**](https://github.com/2001AlexChen)      |
|    郝子睿    |     <!--2020-->     | [**guoanbumingzhentan**](https://github.com/guoanbumingzhentan) |

## 项目及完成情况：

（右4列为小组成员每个人的贡献）

| 项目序号 | 项目名称                                                     | 文件夹对应                                                   | 葛萧遥 | 贾晨铮 | 陈思宇 | 郝子睿 |
| :------: | ------------------------------------------------------------ | ------------------------------------------------------------ | ------ | ------ | ------ | ------ |
|    1     | Implement the naïve birthday attack of reduced SM3           | 贾晨铮：[SM3_Birthday-Attack](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM3_Birthday-Attack)；陈思宇：[SM3_BirthdayAttack](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM3_BirthdayAttack) |        | ✅      | ✅      |        |
|    2     | Implement the Rho method of reduced SM3                      |                                                              |        | ✅      | ✅      |        |
|    3     | Implement length extension attack for SM3, SHA256, etc       |                                                              |        | ✅      |        |        |
|    4     | Do your best to optimize SM3 implementation (software)       |                                                              |        | ✅      |        |        |
|    5     | Impl Merkle Tree following RFC6962                           |                                                              |        |        |        |        |
|    6     | Try to Implement this scheme                                 |                                                              |        |        | ✅      |        |
|    7     | Report on the application of this deduce technique in Ethereum with ECDSA | 陈思宇：[SM2_Report on Ethereum with ECDSA](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM2_Report%20on%20Ethereum%20with%20ECDSA) |        |        | ✅      |        |
|    8     | Impl sm2 with RFC6979                                        | 贾晨铮：[SM2_implement](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM2_implement) |        | ✅      |        |        |
|    9     | Verify the above pitfalls with proof-of-concept code         |                                                              |        |        |        |        |
|    10    | Implement the above ECMH scheme                              |                                                              |        |        |        |        |
|    11    | Implement a PGP scheme with SM2                              |                                                              |        |        |        |        |
|    12    | Implement sm2 2P sign with real network communication        |                                                              |        |        |        |        |
|    13    | Implement sm2 2P decrypt with real network communication     |                                                              |        |        |        |        |
|    14    | PoC impl of the scheme, or do implement analysis by Google   |                                                              |        |        |        |        |
|    15    | Send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself |                                                              |        |        |        |        |
|    16    | Forge a signature to pretend that you are Satoshi            |                                                              |        |        |        |        |
|    17    | Research report on MPT                                       |                                                              |        |        |        |        |
|    18    | Find a key with hash value `sdu_cst_20220610` under a message composed of your name followed by your student ID. For example, `San Zhan 202000460001` | 葛萧遥：[Meow-Hash-Invertibility](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/Meow-Hash-Invertibility) | ✅      |        |        |        |
|    19    | Find a 64-byte message under some k fulfilling that their hash value is symmetrical | 葛萧遥：[Meow-Hash-Symmetry](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/Meow-Hash-Symmetry) | ✅      |        |        |        |
|   20.1   | Write a circuit to prove that your CET6 grade is larger than 425.（a. Your grade info is like `(cn_id, grade, year, sig_by_moe)`. These grades are published as commitments onchain by MoE. b. When you got an interview from an employer, you can prove to them that you have passed the exam without letting them know the exact grade.） |                                                              |        |        |        |        |
|   20.2   | The commitment scheme used by MoE is SHA256-based.（`commit` = `SHA256(cn_id, grade, year, sig_by_moe, r)`） |                                                              |        |        |        |        |
|    21    | Impl sm4（上课时有提及但课件中无）                           | 葛萧遥&贾晨铮：[SM4_Unoptimization](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM4_Unoptimization)、[SM4_Optimization](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM4_Optimization)；陈思宇：[SM4_Implement＆Optimization](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM4_Implement＆Optimization) | 🟢      | 🟢      | 🟢      |        |

其中：

- ✅：独立完成项目；
- 🟢：合作完成项目；
- <留空>：未完成项目。
