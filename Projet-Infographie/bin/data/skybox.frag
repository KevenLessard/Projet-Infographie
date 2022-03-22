#version 330

uniform samplerCube EnvMap;

in vec3  texcoord;
out vec4 outColor;


void main (void)
{
   
    vec3 envColor = vec3 (texture(EnvMap, texcoord));
	//vec3 envColor = vec3 (texture(EnvMap, gl_TexCoord[0]));

  

    outColor = vec4(envColor.rgb, 1.0);
}
