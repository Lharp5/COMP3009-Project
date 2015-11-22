#version 330 core

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

in vec4 vtxPos;
in vec4 vtxCol;
in vec4 vtxNorm;

out Data{
	vec4 color;
	vec3 norm_interp;
	vec3 pos_interp;
} Out;

void main(){
	// transform the vertex position
	gl_Position = projection * view * model * vtxPos;

	vec4 pos = view * model * vtxPos;
	vec4 norm =  transpose(inverse(view * model)) * vtxNorm;
	Out.pos_interp = pos.xyz;
	Out.norm_interp =  norm.xyz;

	//setting the material components
	// set the colour
	Out.color = vtxCol;
}