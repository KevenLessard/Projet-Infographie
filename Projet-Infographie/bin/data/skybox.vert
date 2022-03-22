#version 330

out vec3  texcoord;

void main() 
{
 	vec4 texcoord0 = gl_ModelViewMatrix * gl_Vertex;
	//texcoord = texcoord0.xyz;
	texcoord = normalize(gl_Vertex.xyz);

    gl_Position    = ftransform();
   
}
