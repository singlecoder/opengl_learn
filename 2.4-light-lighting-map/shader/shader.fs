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
    sampler2D emission;
    float shininess;
};

// 光源结构体，表示光源对每个分量的影响
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
    vec3 diffuseColor = vec3(texture(material.diffuse, TexCoords));
    vec3 specularColor = vec3(texture(material.specular, TexCoords));
    vec3 emissionColor = vec3(texture(material.emission, TexCoords));

    // 环境光照
    vec3 ambient = light.ambient * diffuseColor;

    // 漫反射光照
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * diffuseColor);

    // 镜面光照
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * specularColor);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result * emissionColor, 1.0);
}


// #version 330 core
// out vec4 FragColor;

// struct Material {
//     sampler2D diffuse;
//     sampler2D specular;
//     float     shininess;
// };  

// struct Light {
//     vec3 position;

//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
// };

// in vec3 FragPos;  
// in vec3 Normal;  
// in vec2 TexCoords;
  
// uniform vec3 viewPos;
// uniform Material material;
// uniform Light light;

// void main()
// {
//     // ambient
//     vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
//     // diffuse 
//     vec3 norm = normalize(Normal);
//     vec3 lightDir = normalize(light.position - FragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
    
//     // specular
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);  
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     vec3 specular = light.specular * spec * (vec3(texture(material.specular, TexCoords))); // here we inverse the sampled specular color. Black becomes white and white becomes black.
        
//     FragColor = vec4(ambient + diffuse + specular, 1.0);  
// } 