#version 330 core

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

in vec4 vtxPos;
in vec4 vtxCol;
in vec4 vtxNorm;

out Data{
	vec4 color;
} Out;

void main(){

	// transform the vertex position
	gl_Position = projection * view * model * vtxPos;

	// set the colour
	Out.color = vtxCol;
}