#version 330 core
out vec4 FragColor;

in vec3 position;
in vec2 texCoord;
in vec3 color;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec4 objectColor;

void main()
{
    vec4 texColor = texture(texture1, texCoord);
    FragColor = vec4(lightColor, 1.0) * texColor * vec4(color, 1.0) * objectColor;
}
