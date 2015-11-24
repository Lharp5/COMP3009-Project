#version 400

// Definition of the geometry shader
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

// Attributes passed from the vertex shader
in vec3 vertex_colour[];

// Attributes passed with the material file
uniform mat4 projection_mat;
uniform float particle_size;

// Attributes passed to the fragment shader
out vec4 frag_colour;


void main(void){

	// Get the position of the particle
	vec4 position = gl_in[0].gl_Position;

	// Define the positions of the four vertices that will form a quad 
	// The positions are based on the position of the particle and its size
	// We simply add offsets to the position (we can think of it as the center of the particle),
	// since we are already in camera space
	vec4 v[4];
	v[0] = vec4(position.x - 0.5*particle_size, position.y - 0.5*particle_size, position.z, 1.0);
    v[1] = vec4(position.x + 0.5*particle_size, position.y - 0.5*particle_size, position.z, 1.0);
    v[2] = vec4(position.x - 0.5*particle_size, position.y + 0.5*particle_size, position.z, 1.0);
    v[3] = vec4(position.x + 0.5*particle_size, position.y + 0.5*particle_size, position.z, 1.0);

    // Create the new geometry: a quad with four vertices from the vector v
    for (int i = 0; i < 4; i++){
		gl_Position = projection_mat * v[i];
		frag_colour = vec4(vertex_colour[0], 1.0);
        EmitVertex();
     }

	 EndPrimitive();
}