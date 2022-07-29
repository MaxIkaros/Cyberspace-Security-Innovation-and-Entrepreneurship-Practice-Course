from pysmx.SM3 import SM3
#本题已预先安装相关SM3环境
#SM3安装环境相关参考链接见小组repo中SM3_RhoMethod文件夹里面的README文件
#SM3国密算法的具体实现代码为C++语言编写，见小组SM3_Implement.cpp文件，该文件作者为陈思宇（Siyu Chen）
import random
import time
func=SM3()
L=[]
def RhoMethod(n):#实现Rho Method的前n比特碰撞
    a=random.randint(0,0xfffff)
    b=str(a)#转换为字符串形式，以便于满足SM3函数要求
    List=[]
    for i in range(pow(2,32)):   
        func.update(b)
        c=func.hexdigest()
        L.append(c)
        char=L[0][:n]#对SM3得到的结果进行前n位切片，用char表示
        List.append(char)#每生成一个SM3切片结果，就在列表中增加一个元素
        a=2*a
        if char in List:
#每次生成一个char就对列表进行寻找，如果发现已经存在，则表明已经找到碰撞，形成了环
            print("寻找",n,"比特碰撞成功")
            return;
        print("寻找碰撞失败")
if __name__ == '__main__':
    startime=time.time()#开始时间
    RhoMethod(8)#可根据需要更改碰撞比特数
    endtime=time.time()#结束时间
    time=endtime-startime#Rho Method花费的总时间
    time=time*1000#为了时间表示得更精确，本题选用毫秒来表示所用时间
    print("所用的时间为：", time, "ms")
=======
from pysmx.SM3 import SM3
#本题已预先安装相关SM3环境
#SM3安装环境相关参考链接见小组repo中SM3_RhoMethod文件夹里面的README文件
#SM3国密算法的具体实现代码为C++语言编写，见小组SM3_Implement.cpp文件，该文件作者为陈思宇（Siyu Chen）
import random
import time
func=SM3()
L=[]
def RhoMethod(n):#实现Rho Method的前n比特碰撞
    a=random.randint(0,0xfffff)
    b=str(a)#转换为字符串形式，以便于满足SM3函数要求
    List=[]
    for i in range(pow(2,32)):   
        func.update(b)
        c=func.hexdigest()
        L.append(c)
        char=L[0][:n]#对SM3得到的结果进行前n位切片，用char表示
        List.append(char)#每生成一个SM3切片结果，就在列表中增加一个元素
        a=2*a
        if char in List:
#每次生成一个char就对列表进行寻找，如果发现已经存在，则表明已经找到碰撞，形成了环
            print("寻找",n,"比特碰撞成功")
            return;
        print("寻找碰撞失败")
if __name__ == '__main__':
    startime=time.time()#开始时间
    RhoMethod(8)#可根据需要更改碰撞比特数
    endtime=time.time()#结束时间
    time=endtime-startime#Rho Method花费的总时间
    time=time*1000#为了时间表示得更精确，本题选用毫秒来表示所用时间
    print("所用的时间为：", time, "ms")

