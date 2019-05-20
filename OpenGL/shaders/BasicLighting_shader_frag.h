#version 330 core
out vec4 FragColor;

in vec3 position;
in vec2 texCoord;
in vec3 noraml;
in vec3 FragPos;

struct Material{
    //    vec3 ambinet;
    //    vec3 diffuse;
    //    vec3 specular;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light{
    vec3 ambinet;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
    vec3 position;
    
    //点光源
//    float linear;
//    float quadratic;
    
    //聚光
    float cutOff;
    float epsilon;
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
//    vec3 lightDir = normalize(-light.direction);
    
//    vec3 ambient = light.ambinet * material.ambinet;
    vec3 ambient = light.ambinet * vec3(texture(material.diffuse, texCoord));
    
    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    vec3 specular = light.specular * material.specular * spec;
    vec3 specular = light.specular * vec3(texture(material.specular, texCoord)) * spec;
    
    //光线衰减
//    float distance    = length(light.position - FragPos);
//    float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));
//    ambient *= attenuation;
//    diffuse *= attenuation;
//    specular *= attenuation;

    //聚光
    vec3 spotDir = normalize(-light.direction);
    float t = dot(lightDir, spotDir);
    vec4 result = vec4(0.0, 0.0, 0.0, 1.0);
    if(t >= light.cutOff)
    {
        float intensity = (t - light.cutOff)/light.epsilon;
        ambient *= intensity;
        diffuse *= intensity;
        specular *= intensity;
        result = vec4(ambient + diffuse + specular, 1.0) * objectColor;
    }
//    FragColor = texColor * result;
    FragColor = result;
}
