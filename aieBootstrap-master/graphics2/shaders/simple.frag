// a simple flat colour shader
#version 410

uniform vec3 kd;

out vec4 FragColour;

void main() 
{
FragColour = vec4(kd, 1);
}