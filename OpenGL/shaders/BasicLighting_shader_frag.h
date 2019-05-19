#version 330 core
out vec4 FragColor;

in vec3 position;
in vec2 texCoord;
in vec3 noraml;
in vec3 FragPos;

struct Material{
    vec3 ambinet;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 ambinet;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};

uniform Material material;
uniform Light light;
uniform sampler2D texture0;
uniform vec4 objectColor;
uniform vec3 viewPos;

void main()
{
    vec4 texColor = texture(texture0, texCoord);
    vec3 norm = normalize(noraml);
    vec3 lightDir = normalize(light.position - FragPos);
    
    vec3 ambient = light.ambinet * material.ambinet;
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (material.specular * spec);
    
    vec4 result = vec4(ambient + diffuse + specular, 1.0) * objectColor;
    FragColor = result;
}
