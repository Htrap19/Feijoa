#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_VP;

void main()
{
	gl_Position = u_VP * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout (location = 0) out vec4 color;

void main()
{
	color = vec4(1.0);
}