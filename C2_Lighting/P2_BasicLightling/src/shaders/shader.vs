#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // 法线向量被认为是放在顶点数据里面的

out vec3 Normal;
out vec3 FragPos;

// 模型矩阵
uniform mat4 model;

uniform mat4 view;

// 透视矩阵
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = aNormal;
} 