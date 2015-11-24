#version 400

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

uniform float timer;

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
	
	vec4 upVector = view * model * vec4(0,1,0,1); //world up vector
	vec4 pos = model * vec4(vtxPos, 1.0);
	vec4 norm =  transpose(inverse(view * model)) * vec4(vtxNorm, 1.0);

	// Let time cycle every four seconds
	float circtime = timer - 4.0 * floor(timer / 4);
	float t = circtime; // Our time parameter
	
	// Settings for the explosion
	// Could also define these in the material file to have multiple particle systems with different settings
    float grav = 0.005; // Gravity
    float slow = 0.6; // Allows to slow down the explosion, control the speed of the explosion
	
    // Move point along normal and down with t*t (acceleration under gravity)
    pos.x += norm.x*t*slow - grav*slow*upVector.x*t*t;
    pos.y += norm.y*t*slow - grav*slow*upVector.y*t*t;
    pos.z += norm.z*t*slow - grav*slow*upVector.z*t*t;

	// transform the vertex position
	pos = view * pos;
	gl_Position = projection * pos;

	Out.pos_interp = pos.xyz;
	Out.norm_interp =  norm.xyz;

	//setting the material components
	// set the colour
	Out.color = vtxCol;
	Out.texCoord = texCoord;
}