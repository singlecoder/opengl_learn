## 前言
OpenGL学习，[参考链接](http://daringfireball.net/projects/markdown/syntax)

每个子目录为一个单独的demo，其中temp-demo为模版demo，其他目录均从模版目录拷贝，模版目录提供基本的开发环境，其他demo只需要在main.cpp中编写自己代码即可

## 我的开发环境
mac: 10.14.6

cmake: 3.14.5

vscode: 1.41.1

## 运行
```
1、进入一个demo的目录
2、cmake .
3、make
4、./main
```

## demo简介
目录                 | 说明              |
--------------------|------------------|
temp-demo           |模版demo，提供开发环境|
1.1-hello-window    |窗口显示、清除颜色缓冲区|
1.2-hello-triangle  |绘制三角形：VAO、VBO|
