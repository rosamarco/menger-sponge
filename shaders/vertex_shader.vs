#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;
layout (location = 4) in mat4 amodel;

out vec2 TexCoord;
out vec3 color;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * amodel * vec4(aPos, 1.0);
    color = aColor;
	TexCoord = aTexCoord;
}
