#version 330 core

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

in vec3 vtxPos;
in vec4 vtxCol;
in vec3 vtxNorm;
in vec2 texCoord;

out Data{
	vec4 color;
	vec3 norm_interp;
	vec3 pos_interp;
	vec2 texCoord;
} Out;

void main(){
	// transform the vertex position
	gl_Position = projection * view * model * vec4(vtxPos, 1.0);

	vec4 pos = view * model * vec4(vtxPos, 1.0);
	vec4 norm =  transpose(inverse(view * model)) * vec4(vtxNorm, 1.0);
	
	Out.pos_interp = pos.xyz;
	Out.norm_interp =  norm.xyz;

	//setting the material components
	// set the colour
	Out.color = vtxCol;
	Out.texCoord = texCoord;
}