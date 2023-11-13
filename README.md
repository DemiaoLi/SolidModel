# SolidModel
三维CAD建模 --- 基于B-rep与欧拉操作的实体建模方法
实现了基本的欧拉操作以及sweep扫掠成操作
<img width="1201" alt="截屏2023-11-13 15 43 11" src="https://github.com/DemiaoLi/SolidModel/assets/107128424/ca4e7f8f-040b-4b7c-86bb-8977ef3a87a4">
按一次D键可以切换成线框的透视视角
<img width="1203" alt="截屏2023-11-13 15 44 34" src="https://github.com/DemiaoLi/SolidModel/assets/107128424/dcec00b0-c928-4005-8397-17974d6abd96">
再按一次D键可以切换成边界点的视角
<img width="1202" alt="截屏2023-11-13 15 46 56" src="https://github.com/DemiaoLi/SolidModel/assets/107128424/d77927e2-e05e-4cbf-b0d1-b7959e3b4e06">

# 项目环境及文件说明
实验环境：Xcode 本机环境：macOS Monterey 12.3.1
| EulerOperations：定义了半边数据结构以及mvfs, mev, mef, kfmrh, kemr五个基本欧拉操作 sweep扫成操作
| draw：实现了绘制操作
| Examples：实现了对0，1，8，5四个数字的绘制
| main：初始化以及打印一些关键的日志信息

注意：在EulerOperations.h文件中，用到的glm库我直接写的本机的绝对路径，运行需要根据自己的实际情况进行修改
<img width="723" alt="截屏2023-11-13 16 03 54" src="https://github.com/DemiaoLi/SolidModel/assets/107128424/96c3ab5c-939c-4a26-9360-17e56cbacd7a">

# 使用方法
在main函数中，我定义了四个数字实体：
<img width="366" alt="截屏2023-11-13 15 57 10" src="https://github.com/DemiaoLi/SolidModel/assets/107128424/26ea1ee8-9ce1-41e1-a1ce-d96de050ef13">
我们可以在drawSolidModel函数中以任意顺序传入若干个，他可以按照传入的顺序进行显示
<img width="412" alt="截屏2023-11-13 15 57 52" src="https://github.com/DemiaoLi/SolidModel/assets/107128424/9a53ed8e-690e-4cf6-a475-62cdea9e013a">
我们可以在Example.cpp中看到四个实体的构造过程，其中数字0，8是完全通过欧拉操作构造；1，5通过结合sweep扫成操作构建
