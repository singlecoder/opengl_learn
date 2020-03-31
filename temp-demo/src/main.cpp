#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>
// #include <soil/SOIL.h>
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <camera/camera.h>

#include <iostream>

using namespace std;

// 加载纹理
GLuint loadTexture (const char* path);

int main(){
    cout << "OpenGL learn temp demo" << endl;

    return 0;
}

GLuint loadTexture (const char* path)
{
    // 创建纹理对象并且绑定
    GLuint texture;
    glGenTextures(1, &texture);

    cout << "the path is " << path << " and the id is " << texture << endl;

    // 加载图片
    int width, height, nrChennels;
    stbi_uc* data = stbi_load(path, &width, &height, &nrChennels, 0);
    if (data)
    {
        GLenum format;
        switch (nrChennels)
        {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGBA;
                break;
        }

        // 为当前绑定的纹理对象设置环绕、过滤方式，也就是采样
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, texture);
        // 将图片数据写入当前绑定的纹理对象
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        // 设置mipmap
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else
    {
        cout << "Failed to load texture" << endl;
        stbi_image_free(data);

        return -1;
    }
    
    return texture;
}
