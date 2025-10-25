#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;
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
    float diff = max(dot(norm, lightColor), 0.0f);
    vec3 diffuse = diff * lightColor;
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

    // 计算高光
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}