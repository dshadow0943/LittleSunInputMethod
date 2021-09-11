# LittleSunInputMethod

## 简介
该系统软件为可运行在uos操作系统和linux操作系统的一款可同时支持拼音输入和手写输入的软键盘输入法

## 开发

在开发过程中围绕uos桌面操作系统展开，全程在uos桌面操作系统中进行开发

qt版本: 5.11

输入法框架: fcitx4

与插件交互方式: dbus服务

插件地址: https://github.com/dshadow0943/fcitx-littlesun

为增加系统易移植性，此系统开发为两部分，分别为与用户交互的客户端界面和输入法插件，客户端软件部分与系统不进行任何的直接交互，所有交互都通过插件间接交互

所有功能和界面皆为自主开发，无任何第三方库引用

## 功能

目前该系统目前已完成
拼音中文汉字输入、
手写中文汉字输入、
手写数字输入、
手写字母输入、
数字输入、字母输入、
符号输入、
联想输入、
键盘移动、
键盘大小适应等功能。
聚焦自动弹出键盘失焦自动关闭deng

可通过插件可在用户聚焦时自动启动客户端软件、用户输入时可自动向用户聚焦的目标位置输出字符以及删除字符、关闭后为直接终止客户端软件运行，不会在后台驻留，节省系统内存空间。

## 安装及使用

### 安装包下载

   客户端: https://github.com/dshadow0943/LittleSunInputMethod/releases/tag/v1.0.2

   插件: https://github.com/dshadow0943/fcitx-littlesun/releases/tag/v1.0.1

### 安装

1. 可自行下载deb安装自行安装

    dpkg命令： sudo dpkg -i fcitx-littlesun-1.0.1-linux.deb
   
    其中 fcitx-littlesun-1.0.1-linux.deb 为安装包名
    
2. 源码编译安装

注： 该软件分为客户端软件和插件两部分，只有两个软件包都安装后且系统默认输入框加为fcitx小企鹅输入法框架才可正常使用，安装顺序无要求，
其中客户端安装包命名为littlesun, 插件命名为fcitx-littlesun

插件地址: https://github.com/dshadow0943/fcitx-littlesun

## 部分设计图

![avatar](images/littlesunDFD图.png)

![avatar](images/功能模块图.png)

![avatar](images/系统层次图.png)

## 界面图

![avatar](images/界面1.png)

![avatar](images/界面2.png)

![avatar](images/界面3.png)

![avatar](images/界面4.png)

![avatar](images/界面5.png)

![avatar](images/界面6.png)

![avatar](images/界面7.png)

![avatar](images/界面8.png)

![avatar](images/界面9.png)

![avatar](images/界面10.png)

![avatar](images/界面11.png)

![avatar](images/界面12.png)

## 手写实例

![avatar](images/手写1.png)

![avatar](images/手写2.png)

![avatar](images/手写3.png)

![avatar](images/手写4.png)

![avatar](images/手写5.png)

![avatar](images/手写6.png)

![avatar](images/手写7.png)

![avatar](images/手写8.png)

![avatar](images/手写9.png)

![avatar](images/手写10.png)

![avatar](images/手写11.png)

![avatar](images/手写12.png)

![avatar](images/手写13.png)

![avatar](images/手写14.png)

![avatar](images/手写15.png)
