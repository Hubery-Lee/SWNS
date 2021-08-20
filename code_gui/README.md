<!--
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-14 11:42:06
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-07-22 19:44:42
-->
# 项目说明



## 目的

开发一个基于Geant4和Root框架的应用程序，实现输入中子源能谱，通过设计屏蔽方案，获得模拟现场中子谱的功能，用于分析通过屏蔽方案与中子谱之间的关系，达到根据现场中子谱和中子源谱快速设计屏蔽配置方案的目的。



## 项目文件说明



doc 使用说明文件

macs 用户输入需要进行的相关设置

- 射线源设置
- 几何设置
- 数据读出设置

output 软件计算的屏蔽体后面的中子谱

gui 用于用户设置的图像交互界面软件



data 模拟现场中子谱相关数据

- 中子源能谱
- 现场中子谱

bin 

- SWNS 可执行文件
- SWNS.root 数据存储文件



## 参考：
example/extended/eventgenerator  文件设置射线源
example/extended/persistency/P03  ASCII文件构建几何体
example/extended/physicslists  文件设置物理过程