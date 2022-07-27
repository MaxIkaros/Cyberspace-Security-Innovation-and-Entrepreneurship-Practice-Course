网络空间安全学院 2020级4班 陈思宇 202000460119
<br />
=
Rho攻击相关原理：
=
我们从一个随机生成的初始值出发，在每一次循环中通过迭代函数生成一个新的值，并对其进行SM3函数运算，若前n位结果已经存在于结果数组中，则证明寻找Rho碰撞成功；若结果不在数组中，则将该结果加入到数组中，继续进行下一次循环。若找到一堆碰撞，则证明已成环。本题所用迭代函数为f(x)=2x，且已预先安装相关SM3函数环境，环境安装相关操作链接见下文。

Rho攻击原理概述：
=
a=SM3(m),b=SM3(SM3(n))

if a == b:

    print("寻找n比特碰撞成功")
    
**当碰撞比特数为8bit时，代码运行情况如下：**
![截图1](https://user-images.githubusercontent.com/109191115/180974142-6d0193e0-3293-4339-8c74-f0c8cf776c94.png)
**当碰撞比特数为16bit时，代码运行情况如下：**
![截图2](https://user-images.githubusercontent.com/109191115/180974265-69b7c59a-ed69-4f4a-a235-33df064d39b9.png)
**当碰撞比特数为32bit时，代码运行情况如下：**
![截图3](https://user-images.githubusercontent.com/109191115/180974210-2a3eb314-fd68-4737-b531-504563eedb65.png)

实验结论：
=
碰撞比特数越大，寻找到一对碰撞的所用时间越长。

**注：由于作者SM3实现相关代码为C++语言，本题SM3_RhoMethod代码为Python语言，为了编写方便，故导入了pysmx模块的SM3函数进行编译，所以代码运行用时会比引用自己编写的SM3程序更短，但不影响本实验相关结论**

SM3_RhoMethod相关的SM3环境安装操作如下图所示：
-

**1、首先输入cmd进入命令提示符：**
![截图1](https://user-images.githubusercontent.com/109191115/180785289-3575d690-b084-481f-a544-577d162de337.jpg)

**2、输入pip install snowland-smx进行安装（本实验相关环境在截图前已预先安装成功）：**
![截图2](https://user-images.githubusercontent.com/109191115/180785303-2d507bf7-f33f-4e84-865d-85114b2f9829.jpg)


具体贡献：
=
SM3_RhoMethod文件夹中的SM3_RhoMethod相关的代码均由陈思宇同学单独完成，其他小组成员如有做SM3_RhoMethod相关实验项目，则相关的代码及运行相关说明情况均在其他文件夹中，本文件夹中文件均为陈思宇同学单独完成的SM3_RhoMethod版本。
-

参考链接：
-
**参考链接1：https://gitee.com/snowlandltd/snowland-smx-python/**
**（装SM3相关环境）**

**参考链接2：https://xz.aliyun.com/t/2780?page=1**
**（Pollard Rho算法简析）**
