#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
using namespace std;

#define WIDTH 800
#define HEIGHT 600

const GLchar* vertexShaderSource = 
    "#version 330 core                                    \n"
    "layout(location = 0) in vec3 aPos;                   \n"
    "layout(location = 1) in vec3 aColor;                 \n"
    "out vec3 ourColor;                                   \n"
    "void main()                                          \n"
    "{                                                    \n"
    "    gl_Position = vec4(aPos, 1.0);                   \n"
    "    ourColor = aColor;                               \n"
    "}                                                    \n";

const GLchar* fragmentShaderSource = 
    "#version 330 core                             \n"
    "in vec3 ourColor;                             \n"
    "out vec4 FragColor;                           \n"
    "void main()                                   \n"
    "{                                             \n"
    "    FragColor = vec4(ourColor, 1.0f);         \n"
    "}                                             \n";

// 窗口大小改变的回调函数
void framebuffer_size_callback (GLFWwindow* window, int width, int height);
// 按键输入处理
void processInput (GLFWwindow* window);

int main ()
{
    // 初始化glfw
    glfwInit();

    // 配置glfw各项参数
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "hello shader interpolation", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    // 将窗口上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // 初始化glad，必须在调用任何 OpenGL 的api之前完成，glfwGetProcAddress：加载系统相关的OpenGL函数指针地址的函数
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // 注册窗口大小改变的回调函数，窗口第一次显示的时候回调函数也会被调用
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 创建着色器对象，这里创建一个顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 着色器源码附加到着色器对象上
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译着色器
    glCompileShader(vertexShader);

    // 检测编译是否成功
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;

        return -1;
    }

    // 片段着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 检测
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;

        return -1;
    }

    // 创建程序对象
    GLuint shaderProgram = glCreateProgram();

    // 把shader加到程序对象上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // 链接shader
    glLinkProgram(shaderProgram);
    
    // 检测链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;

        return -1;
    }

    // 链接后，就不需要着色器对象了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 激活程序对象
    glUseProgram(shaderProgram);

    // 绘制三角形相关
    float vertices[] = {
        // 位置              // 颜色
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    // 创建缓冲对象对象
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // 创建顶点数组
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    
    // 绘制三角形
    glBindVertexArray(VAO);
    // 把缓冲对象绑定到 GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将数据复制到指定目标的缓冲区中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 设置openGL如何解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    // 启用顶点属性
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // 设置清空屏幕所用颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空屏幕颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查触发事件(键盘输入、鼠标点击、窗口大小改变等)，并调用对应的回调函数
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
    // 设置OpenGL渲染窗口大小
    glViewport(0, 0, width, height);
}

void processInput (GLFWwindow* window)
{
    // 返回键则关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
