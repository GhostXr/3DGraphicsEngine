#version 330 core
out vec4 FragColor;

in vec3 position;
in vec2 texCoord;
in vec3 color;

uniform vec4 objectColor;

void main()
{
    FragColor = objectColor;
}
