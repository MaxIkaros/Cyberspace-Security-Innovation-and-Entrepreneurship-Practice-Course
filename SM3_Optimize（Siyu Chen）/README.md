网络空间安全学院 2020级4班 陈思宇 202000460119
<br />
=
SM3优化原理：
=
在SM3代码的消息压缩函数中，有多处用到了LeftShift(A, 12)的值。其中，字符串A为初始向量IV（在本代码中为示例字符串str[1]，str[1]具体见[SM3_Implement](https://github.com/MaxIkaros/Cyberspace-Security-Innovation-and-Entrepreneurship-Practice-Course/tree/main/SM3_Implement/SM3_Implement.cpp)代码第334行)的前八位字符串截取。为了对SM3程序进行优化，我们创建临时变量Res，用来存储LeftShift(A, 12)，即字符串A循环左移12位的结果，并用于后续带入，避免每次用到该结果时重复计算，以进行程序优化。

代码运行结果：
=
**注：本次优化后程序和优化前程序的SM3输入数据均为str[0]="abcdefghikjlmnopqrstuvwxyz"和str[1]="abcdabcdabcdabcdabcdabcd"。**

我们分别运行SM3优化后和优化前的程序，并对这两个程序用GetTickCount()函数得到程序运行前后的当前时间，通过结束时间和起始时间相减得到运行时间，结果如下图所示。

**优化后程序运行时间：**
![优化后截图](https://user-images.githubusercontent.com/109191115/181959194-70dcd6c9-8112-43c8-a6bc-a890a57febd6.png)
**优化前程序运行时间：**
![优化前截图](https://user-images.githubusercontent.com/109191115/181959535-5dea432f-b153-4c81-b386-58ae26c05316.png)

我们可以看到，SM3优化后程序运行时间缩短了7％左右，运行效率得到了提升。
-
具体贡献：
=
SM3_Optimize（Siyu Chen）文件夹中的SM3优化相关的代码均由陈思宇同学单独完成，其他小组成员如有做SM3优化相关实验项目，则相关代码及运行相关说明情况均在其他文件夹中，本文件夹为陈思宇同学单独完成的SM3优化版本。
-
参考链接：
=
无
-
