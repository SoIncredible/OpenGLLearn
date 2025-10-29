#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f)); // 正确：片段位置转换到世界空间
    
    // 关键修复：将法线转换到世界空间（处理缩放导致的法线变形）
    // mat3 normalMatrix = transpose(inverse(mat3(model)));
    // Normal = normalMatrix * aNormal; // 法线从模型空间→世界空间

    Normal = model * vec4(aNormal, 1.0f); // 法线从模型空间→世界空间
}