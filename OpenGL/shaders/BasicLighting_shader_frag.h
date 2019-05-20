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

struct DirectionLight{
    vec3 ambinet;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

struct PointLight
{
    vec3 ambinet;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    //点光源
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 ambinet;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    vec3 direction;
    //聚光
    float cutOff;
    float epsilon;
};

uniform Material material;
uniform DirectionLight directionLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform sampler2D texture0;
uniform vec4 objectColor;
uniform vec3 viewPos;

vec3 calculatorDirctionLight()
{
    vec4 texColor = texture(texture0, texCoord);
    vec3 norm = normalize(noraml);
    vec3 lightDir = normalize(-directionLight.direction);
    
    vec3 ambient = directionLight.ambinet * vec3(texture(material.diffuse, texCoord));
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directionLight.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = directionLight.specular * vec3(texture(material.specular, texCoord)) * spec;
    return ambient + diffuse + specular;
}

vec3 calculatorPointLight()
{
    vec4 texColor = texture(texture0, texCoord);
    vec3 norm = normalize(noraml);
    vec3 lightDir = normalize(pointLight.position - FragPos);
    
    vec3 ambient = pointLight.ambinet * vec3(texture(material.diffuse, texCoord));
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * vec3(texture(material.specular, texCoord)) * spec;
    
    //光线衰减
    float distance    = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (1.0 + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ambient + diffuse + specular;
}

//聚光
vec3 calculatorSpotLight()
{
    vec4 texColor = texture(texture0, texCoord);
    vec3 norm = normalize(noraml);
    vec3 lightDir = normalize(spotLight.position - FragPos);
    
    vec3 ambient = spotLight.ambinet * vec3(texture(material.diffuse, texCoord));
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * vec3(texture(material.specular, texCoord)) * spec;
    
    vec3 spotDir = normalize(-spotLight.direction);
    float t = dot(lightDir, spotDir);
    float intensity = 0.0;
    if(t >= spotLight.cutOff)
    {
        intensity = (t - spotLight.cutOff)/spotLight.epsilon;
    }
    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;
    return ambient + diffuse + specular;
}

void main()
{
    
//    vec4 texColor = texture(texture0, texCoord);
//    vec3 norm = normalize(noraml);
//    vec3 lightDir = normalize(light.position - FragPos);
//    //    vec3 lightDir = normalize(-light.direction);
//
//    //    vec3 ambient = light.ambinet * material.ambinet;
//    vec3 ambient = light.ambinet * vec3(texture(material.diffuse, texCoord));
//
//    float diff = max(dot(norm, lightDir), 0.0);
//    //    vec3 diffuse = light.diffuse * diff * material.diffuse;
//    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
//
//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    //    vec3 specular = light.specular * material.specular * spec;
//    vec3 specular = light.specular * vec3(texture(material.specular, texCoord)) * spec;
//
//    //    FragColor = texColor * result;
//
//    FragColor = vec4(result, 1.0) * objectColor;
//    FragColor = result;
    
    vec3 result = vec3(0.0);
    
    if(directionLight.ambinet.x != 0.0)
        result += calculatorDirctionLight();

    if(pointLight.ambinet.x != 0.0)
        result += calculatorPointLight();

    if(spotLight.ambinet.x != 0.0)
        result += calculatorSpotLight();
    
    FragColor = vec4(result, 1.0);
}
