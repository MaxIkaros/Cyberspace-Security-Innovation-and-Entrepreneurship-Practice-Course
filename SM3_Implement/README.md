网络空间安全学院 2020级4班 陈思宇 202000460119
<br />
=
SM3算法相关原理概述：
=
对于长度小于2的64次方比特的消息m，SM3算法首先将输入的消息转换为ASCII码的形式，并进行数据填充，使得其长度为512比特倍数。在此之后，我们需要对得到的消息进行迭代压缩，并生成哈希值的结果。而在这之中，迭代压缩包含了消息扩展和消息压缩两个部分。其中，消息扩展部分主要包含了循环左移、异或以及置换操作，压缩函数主要涉及到循环左移、模加运算、异或、置换以及布尔函数。**本题用到的初始值IV和常量如下图所示：**

![截图1](https://user-images.githubusercontent.com/109191115/181049817-f725ccb2-e5a7-4df1-b221-074ed4f2330a.png)

代码运行结果：
=
**注：本次结果输入数据值分别为str[0]="abcdefghikjlmnopqrstuvwxyz"和str[1]="abcdabcdabcdabcdabcdabcd"，可在SM3_Implement.cpp文件中的第333和334行代码根据需要进行修改，本次示例对应结果为示例1（str[0]="abcdefghikjlmnopqrstuvwxyz"）和示例2(str[1]="abcdabcdabcdabcdabcdabcd")。**

示例1代码运行结果如下：
-
![截图2](https://user-images.githubusercontent.com/109191115/181052540-b8c74b9f-f579-491b-a62f-7a6efff3410c.png)
![截图3](https://user-images.githubusercontent.com/109191115/181052588-7a27df70-4bf2-4855-94ff-29469da6ea0e.png)
示例2代码运行结果如下：
-
![截图4](https://user-images.githubusercontent.com/109191115/181053003-0b69a2d1-a42d-4bd3-ad1f-37a4c5653312.png)
![截图5](https://user-images.githubusercontent.com/109191115/181053053-92fd9f46-35dd-45f9-9911-460976229cfc.png)

具体贡献：
=
SM3_Implement文件夹中的SM3_Implement相关的代码均由陈思宇同学单独完成，其他小组成员如有做SM3实现的实验项目，则相关的代码及运行相关说明情况均在其他文件夹中，本文件夹中文件均为陈思宇同学单独完成的SM3_Implement版本。
-

代码参考链接：
-

**https://blog.csdn.net/qq_35699583/article/details/113060927?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~default-1-113060927-blog-121555000.pc_relevant_multi_platform_whitelistv1_exp2&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~default-1-113060927-blog-121555000.pc_relevant_multi_platform_whitelistv1_exp2&utm_relevant_index=1**
**（SM3相关介绍及部分实现）**