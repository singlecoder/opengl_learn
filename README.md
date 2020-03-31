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
1.6-hello-coordinate|坐标系：局部空间(modelMatrix)、世界空间(viewMatrix)、观察空间(projectionMatrix+透视除法)、裁剪空间(视口变换)、屏幕空间|
1.6.1-hello-coordinate-more3d|坐标系：MVP矩阵的应用|
1.7-hello-camera|摄像机：位置、方向、右轴、上轴、LookAt矩阵|
2.1-light-color|光照：反射|
2.2-light-phong-lighting-model|冯氏光照模型：环境(ambient)、漫反射(diffuse)、镜面(specular)光照|



