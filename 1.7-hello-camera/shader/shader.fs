#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 ourCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{  
    FragColor = mix(texture(texture0, ourCoord), texture(texture1, ourCoord), 0.3);
}

