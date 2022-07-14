#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float offset;
uniform float Th;

void main()
{
	gl_Position = vec4(aPos.x*cos(Th + aPos.y) + offset, aPos.x*sin(Th + aPos.y), 0.0f, 1.0f);
	ourColor = aColor;
}