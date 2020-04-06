#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;

out vec4 FragColor;

// 材质结构体
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    // sampler2D emission;
    float shininess;
};

// 光源结构体，表示光源对每个分量的影响
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 定向光(平行光)
    vec3 direction;
    // 聚光
    vec3  position;
    float cutOff;
    float outerCutOff;

    // 光源衰减
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

void main()
{
    vec3 diffuseColor = vec3(texture(material.diffuse, TexCoords));
    vec3 specularColor = vec3(texture(material.specular, TexCoords));
    // vec3 emissionColor = vec3(texture(material.emission, TexCoords));

    // 光源衰减
    float distance = length(LightPos - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                light.quadratic * (distance * distance));

    // 环境光照
    vec3 ambient = light.ambient * diffuseColor;
    ambient *= attenuation;

    // 漫反射光照
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    
    // 聚光 
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * diffuseColor);
    diffuse *= intensity;

    // 镜面光照
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * specularColor);
    specular *= intensity;

    // if (theta > light.cutOff)
    // {
    //     vec3 result = ambient + diffuse + specular;
    //     FragColor = vec4(result, 1.0);
    // }
    // else
    // {
    //     FragColor = vec4(ambient, 1.0);
    // }

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}

