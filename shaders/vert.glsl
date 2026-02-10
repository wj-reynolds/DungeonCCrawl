#version 410 core
layout (location = 0) in vec3 position;
out vec3 vpos;
void main()
{
    vpos = position + vec3(0.5, 0.5, 0);
    gl_Position = vec4(position, 1.0);
}