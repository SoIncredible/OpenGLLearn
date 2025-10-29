#version 330 core

in vec3 Normal;
in vec3 FragPos; // 世界空间

out vec4 FragColor;

uniform vec3 lightPos; // 世界空间
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
    // 计算环境光
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // 计算漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f); // 这里之前写成dot(norm, lightDir)了, 是不对的
    vec3 diffuse = diff * lightColor;

    // 计算高光
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); // 计算反射方向
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;
    // vec3 specular = vec3(1.0f, 1.0f, 1.0f); // 直接设置为白色，不依赖计算
    vec3 result = (ambient + diffuse + specular) * objectColor;
    // vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);

    // FragColor = vec4((norm + 1.0f) / 2.0f, 1.0f); // 法线向量[-1,1]映射到[0,1]颜色
}