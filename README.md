## 1. 项目简介

该项目为作者实验室无人艇的地面控制站，完全由个人从零开始开发，主要功能有主页的设备管理（mainwindow.cpp）以及具体设备页(statusviewrubbishboat3.cpp)的无人艇位置信息(amap5.html、mapWidget)、摄像头实时画面(videoPlayWidget)、无人艇巡航任务设置与下发(amap5.html、mapWidget)、无人艇船载传感器信息显示（panelWidget.cpp）等功能。

![image-20220614145424035](C:\Users\47444\AppData\Roaming\Typora\typora-user-images\image-20220614145424035.png)

![image-20220614145432733](C:\Users\47444\AppData\Roaming\Typora\typora-user-images\image-20220614145432733.png)

## 2. 项目技术细节

### A.地图页面

地图方案分为本地瓦片图和在线地图两种，由于项目时间紧、工作量大，因此选择使用接口齐全的在线地图。地图网页由QT的QWebEngine加载，巡航任务交互在网页中完成。QT和网页信息传递通过QWebChannel传输。

### B.摄像头直播页面

由vlc-qt完成，通过播放实验室同学提供的摄像头推流地址，vlc拉流完成。

### C.状态栏显示

里面的空间主要是参考“飞扬青云”的控件仓库完成。

最后：

该项目还涉及设备与控制站连接协议选择、摄像头直播协议的选择、船体GPS坐标系和高德地图坐标系船体与控制站控制数据帧格式定义等问题、。

## 3. cpp文件对应功能

| 文件名                                       | 功能描述                                 |
| -------------------------------------------- | ---------------------------------------- |
| mainwindow.cpp、amap_main.html               | 主页的设备管理                           |
| statusviewrubbishboat3.cpp(下简称statusview) | 具体设备页                               |
| amap5.html、statusview->mapWidget            | 无人艇位置信息，无人艇巡航任务设置与下发 |
| statusview->videoPlayWidget                  | 摄像头实时画面                           |
| statusview->panelWidget.cpp                  | 无人艇船载传感器信息显示                 |

`项目里面有一些历史迭代版本没有删`