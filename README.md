# Winuc-EasyWebsite
一个可以搭建网站的~~赤石~~简易工具

## 文件列表
```
|-webpage
|     |-网页等文件
|-main.cpp   
|-list.txt  
|-其他文件
```
## 文件说明
`webpage`：自动查找区  
`main.cpp`：源文件  
`list.txt`：页面列表

## 使用说明
在`list.txt`里说明网页与文件映射关系、传输时`Content-Type`类型，具体格式如下：
```
网站路径（/xxx，主页面为/，可以叠加） 对应`Content-Type`对应文件地址
```

或者在`webpage`文件夹里把网页等文件放进去，程序会自动按路径寻找（主页面收到请求为`GET /`，实际文件路径为`webpage/.html`，以此类推）
## 注意事项
1. 这个项目基于`Windows API`制作，在其他系统上无法运行  
2. 目前只支持`GET`请求，其他请求会陆续制作  
3. `webpage`文件夹里请不要乱改文件名后缀，自动寻找时会误判对应`Content-Type`！！！  
4. `list.txt`里网站路径、对应`Content-Type`、对应文件地址不能有空格！
