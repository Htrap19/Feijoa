#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
// Attribute a_Model
layout (location = 1) in vec4 a_Model1;
layout (location = 2) in vec4 a_Model2;
layout (location = 3) in vec4 a_Model3;
layout (location = 4) in vec4 a_Model4;
// =================
layout (location = 5) in vec4 a_Color;
layout (location = 6) in vec2 a_TexCoord;
layout (location = 7) in float a_TexIndex;

uniform mat4 u_Projection;
uniform mat4 u_View;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = u_Projection * u_View * mat4(a_Model1, a_Model2, a_Model3, a_Model4) * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	int texIndex = int(v_TexIndex);
	if (texIndex < 31 && texIndex >= 0)
		color = texture(u_Textures[texIndex], v_TexCoord) * v_Color;
	else
		color = v_Color;
}