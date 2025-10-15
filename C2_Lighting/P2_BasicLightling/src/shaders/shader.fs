#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

// in vec2 TexCoord;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightColor), 0.0f);
    vec3 diffuse = diff * lightColor;
    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}