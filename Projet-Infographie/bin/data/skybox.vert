#version 330

layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 ModelView;
uniform mat4 ModelProjection;


void main() 
{
 	texCoords = aPos;
	vec4 pos = ModelProjection * ModelView * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
   
}
