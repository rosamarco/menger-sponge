#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 color;

uniform sampler2D myTexture1;

void main()
{   
    vec3 objectColor = vec3(0.98, 0.58, 0.23);
    FragColor = texture(myTexture1, TexCoord) * vec4(color, 1.0);
}

