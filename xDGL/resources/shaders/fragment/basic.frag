#version 330 core
out vec4 FragColor;

in vec4 VertexColor;

uniform vec4 TestUniform;

void main()
{
    FragColor = VertexColor + TestUniform;
} 