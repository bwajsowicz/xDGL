#version 330 core
out vec4 FragColor;

in vec4 VertexColor;
in vec2 TexCoords;

uniform vec4 TestUniform;
uniform sampler2D testTexture;

void main()
{
    FragColor = texture(testTexture, TexCoords) + VertexColor + TestUniform;
} 