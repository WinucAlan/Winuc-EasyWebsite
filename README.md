# Winuc-EasyWebsite
一个可以搭建网站的~~赤石~~简易工具

## 文件列表
```
|-main.cpp  
|-main.exe  
|-list.txt  
|-其他文件
```
## 文件说明
`main.cpp`：源文件  
`main.exe`：可执行文件（已编译）  
`list.txt`：页面列表

## 使用说明
在`list.txt`里说明网页与文件映射关系、传输时`Content-Type`类型，具体格式如下：
```
网站路径（/xxx，主页面为/，可以叠加） 对应Content-Type 对应文件地址
```
**注意：网站路径/对应文件地址不能有空格！**

## 注意事项
1. 这个项目基于Windows API制作，在其他系统上无法运行  
2. 目前只支持`GET`请求，其他请求会陆续制作
