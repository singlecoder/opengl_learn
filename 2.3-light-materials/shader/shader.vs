#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform mat4 model;
uniform mat4 normalModel;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
    // 法线矩阵 = 模型矩阵的逆矩阵的转置矩阵，逆矩阵运算开销大，每个顶点都需要进行运算，实际中可以CPU中计算好，然后uniform传入
    // Normal = mat3(transpose(inverse(model))) * aNormal;
    Normal = mat3(view * normalModel) * aNormal;

    FragPos = vec3(view * model * vec4(aPos, 1.0));
    LightPos = vec3(view * vec4(lightPos, 1.0f));

    // 在世界空间计算冯氏光照的话，亮光不是很明显
}

