#version 330 core

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

in vec3 vtxPos;
in vec4 vtxCol;
in vec3 vtxNorm;

out Data{
	vec4 color;
} Out;

void main(){

	// transform the vertex position
	gl_Position = projection * view * model * vec4(vtxPos, 1.0);

	// set the colour
	Out.color = vtxCol;
}