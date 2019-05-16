#version 330 core
out vec4 FragColor;

in vec3 position;
in vec2 texCoord;
in vec3 noraml;
in vec3 FragPos;

uniform sampler2D texture0;
uniform vec3 lightColor;
uniform vec4 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec4 texColor = texture(texture0, texCoord);
    vec3 norm = normalize(noraml);
    vec3 lightDir = normalize(lightPos - FragPos);
    
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec4 result = vec4(ambient + diffuse + specular, 1.0) * objectColor;
    FragColor = texColor * result;
}
