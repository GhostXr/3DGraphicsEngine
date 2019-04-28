#version 330 core
out vec4 FragColor;

in vec3 position;
in vec2 texCoord;
in vec3 ourColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blendOffset;

void main()
{
    vec4 texColor1 = texture(texture1, texCoord);
    vec4 texColor2 = texture(texture2, vec2(-texCoord.x, texCoord.y));
    FragColor = mix(texColor1, texColor2, blendOffset) * vec4(ourColor, 1.0);
}
