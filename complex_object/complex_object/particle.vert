#version 400 core

uniform mat4 model; 
uniform mat4 view; 


uniform float timer;

in vec3 vtxPos;
in vec4 vtxCol;
in vec3 vtxNorm;
in vec2 texCoord;

out vec4 particle_colour;
out float particle_id;

// Define some useful constants
const float pi = 3.1415926536;
const float pi_over_two = 1.5707963268;
const float two_pi = 2.0*pi;

void main(){
	
	vec3 upVector = vec3(0,1,0);
	vec3 pos = vtxPos;
	
	particle_id = vtxCol.r;

	// Define time in a cyclic manner
    float phase = two_pi*particle_id; // Start the sin wave later depending on the particle_id
	float param = timer / 5.0 + phase; // The constant that divides "timer" adjusts the "speed" of the fire
	float rem = mod(param, pi_over_two); // Use the remainder of dividing by pi/2 so that we are always in the range [0..pi/2] where sin() gives values in [0..1]
	float circtime = sin(rem); // Get time value in [0..1], according to a sinusoidal wave
	
	// Set up parameters of the particle motion
    float t = abs(circtime)*(0.3 + abs(vtxNorm.y)); // Our time parameter
    float accel = 1.2; // An acceleration applied to the particles coming from some attraction force
    float slow = 0.98; // Allows us to slow down the motion, control its speed

    pos += slow*upVector*accel*t*t; // Particle moves up

	// transform the vertex position
	gl_Position = view *  model * vec4(pos, 1.0);	

	// Define amount of blending depending on the cyclic time    
	float alpha = 1.0 - circtime*circtime;
	particle_colour = vec4(1.0, 1.0, 1.0, alpha);
}