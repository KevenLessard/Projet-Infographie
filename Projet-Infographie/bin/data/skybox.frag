#version 330

out vec4 outColor;

in vec3  texCoords;

uniform samplerCube EnvMap;

void main ()
{
    outColor = texture(EnvMap, texCoords);
}
