# 多功能计算器——大一下C++大作业
by 朱华彬、马骁、李政民
[TOC]
## (一)实现的功能
### 1. 大数运算
#### 功能
实现了一个高精度实数类，可以做大数的加法、减法、乘法、除法、阶乘、幂运算、开n次方、取模、比较大小等运算，并重载了相关的运算符。

可以用int型、double型、string型、char*型的参数来初始化一个大数对象。

#### 算法
实现了2种大数乘法的算法，一种是模拟竖式乘法，一种是分治法。

幂运算用的是快速幂算法。

开方运算用的是牛顿迭代法。

### 2. 算术表达式求值
#### 功能
输入一个合法的算术表达式，对该表达式求值，并输出结果。
#### 算法
改进版的调度场算法，把原始表达式转换为逆波兰表达式，再进行求值。

### 3. 解线性方程组
#### 功能
输入线性方程组的增广矩阵，程序会给出方程组的解。矩阵的元素可以以整数、实数、分数的形式输入，如`14`, `-8.93`, `-1/16`

齐次方程组：若只有零解，则将零解打印出来。若有无穷多解，则打印方程组的一个通解。

非齐次方程组：若无解，则告知用户无解。若有唯一解，则打印唯一解。若有无穷多解，则打印方程组的一个通解。

求解结束后，可以选择输出变换后的行简化阶梯阵。

#### 算法
用高斯-约当消元法，通过初等变换，将增广矩阵变换成行简化阶梯阵，即可求解。

### 4. 命题逻辑演算
#### 功能
输入一个命题逻辑表达式，程序会给出表达式的真值表、主合取范式、主析取范式。具备语法检查功能，可以检测表达式是否合法。

#### 算法
改进版的调度场算法，把原始表达式转换为逆波兰表达式，再进行求值。

主合取范式和主析取范式是通过真值表法求出来的。

### 5. 矩阵运算
实现了矩阵的加法、减法、数乘、乘法、转置、求逆、求行列式等运算。

### 6. 进制和编码转换
功能

### 7. 切换配色
可以切换控制台窗口的配色方案，默认配色是白底紫字。

## (二)项目文件
### 头文件
```
BigNumber.h 高精度实数类
BigNumberCalcu.h 调用大数运算的有关函数
Equation.h 线性方程组
Fraction.h 分数类
LogicalExpression.h 命题逻辑
OtherMode.h 模式切换
Theme.h 配色切换
```
### 源文件
```
BigNumber.cpp 高精度实数类
BigNumberCalcu.cpp 调用大数运算的有关函数
Equation.cpp 线性方程组
Fraction.cpp 分数类
LogicalExpression.cpp 命题逻辑
OtherMode.cpp 模式切换
Theme.cpp 配色切换
main.cpp 包含main()函数
```

# (三)分工
- 朱华彬：大数运算、解线性方程组、命题逻辑演算、配色切换
- 李政民：算术表达式求解
- 马骁：矩阵运算、进制和编码转换

# (四)测试样例
## 解线性方程组
```
齐次:
4 6
1 2 1 1 1 0
2 4 3 1 1 0
-1 -2 1 3 -3 0
0 0 2 4 -2 0

4  5
1 -1 5 -1 0
1 1 -2 3 0
3 -1 8 1 0
1 3 -9 7 0

3 5
1 1 -1 1 0
1 -1 -1 1 0
2 1 1 3 0

非齐次:
4 6
1 -1 -1 0 3 -1
2 -2 -1 2 4 -2
3 -3 -1 4 5 -3
1 -1 1 1 8 2

4 6
1 1 1 0 0 0
1 1 -1 -1 -2 1
2 2 0 -1 -2 1
5 5 -3 -4 -8 4
```
## 命题逻辑演算
```
P>(Q>R)
(Q>P&!P)&(R>P&!P)
P|(Q>R&!P)~Q|!S
(P&Q)|(!P&R)
!!P&Q
```