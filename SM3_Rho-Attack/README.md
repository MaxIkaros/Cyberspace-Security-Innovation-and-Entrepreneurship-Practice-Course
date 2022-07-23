# SM3的rho方法攻击

## 库依赖
密码算法库：
[snowland-smx · PyPI](https://pypi.org/project/snowland-smx/)

## 说明
按照常理，该方法简单粗暴

但相关资料很少，于是参考为数不多的项目

发现其并没有rho方法概念中的“从一个初始值出发，不断计算SM3值”

于是写了 rho_attack_f 函数，正确性存疑。