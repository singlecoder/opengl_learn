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
1.2-hello-triangle  |绘制三角形：VAO、VBO、EBO(IBO)|
1.3.1-hello-shader-uniform|动态更新三角形颜色：uniform|
1.3.2-hello-shader-interpolation|片段插值|
1.3.3-hello-shader-class|封装着色器类|
1.4.1-hello-texture|纹理的使用：环绕、过滤|
1.4.2-hello-texture-multiple-sample|纹理的使用：纹理单元|
1.5-hello-matrix|矩阵与向量：glm、缩放、旋转、平移|


