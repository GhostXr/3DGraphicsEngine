#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float ourPosition;

out vec3 ourColor;
out vec2 texCoord;
out vec3 position;

void main()
{
    gl_Position = vec4(aPos.x+ourPosition, aPos.y, aPos.z, 1.0);
    position = aPos;
    texCoord = aTexCoord;
    ourColor = aColor;
}
