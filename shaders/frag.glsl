#version 410 core
out vec4 outColor;
in vec3 vpos;
uniform vec3 color = vec3(0.0);
void main()
{
    outColor = vec4(vpos, 0.5);
}