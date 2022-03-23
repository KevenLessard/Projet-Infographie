#version 330

uniform samplerCube EnvMap;

in vec3  texCoords;
out vec4 outColor;


void main ()
{
   
    outColor = texture(EnvMap, texCoords);
}
