//simple post processing vertex shader
#version 410

layout( location = 0) in vec2 Position;

out vec2 vTexCoord;

void main(){
//generate texture coords
vec2 texSize = textureSize( colourTexture,0);
vec2 texelSize = 1.0f / texSize;

vec2 scale = (texSize - texelSize) / texSize;
texCoord = vTexCoord / scale + texelSize * 0.5f;

vTexCoord = Position * 0.5f + 0.5f;
gl_Position = vec4(Position, 0, 1);
}