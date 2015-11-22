#version 330 core

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;

//light info
uniform vec4 light_position; //camera space

//material shine data
uniform float shine;

//vertex info
in vec4 vtxPos; //model space
in vec4 vtxCol; 
in vec4 vtxNorm; //model space

//variables stored after doing transformations
vec3 position; //camera space
vec3 normal; //camera space

//data passed to the vector
out Data{
	vec4 color;
	float diffuseIntensity;
	float specularIntensity;
} Out;

void calculate_light(in vec3 light_pos, inout float Id, inout float Is)
{

	// Phong shading

	vec3 N; // Interpolated normal for fragment
	vec3 L; // Light-source direction
	vec3 V; // View direction
	vec3 R; // Refelction Vector


	//calculating normal
    N = normalize(normal);

	//light position
	L = (light_pos - position);
	L = normalize(L);

	//diffuse lighting
	Id += max(dot(N, L), 0.0);
	
	//Specular component
	V = normalize(-position); // Eye position is (0, 0, 0) in view coordinates

	//reflection vector
    R = -L + 2 *dot(L, N) * N; // reflection vector
    R = normalize(R);

	//spec_angle_cos
    float spec_angle_cos = max(dot(V, R), 0.0);
	
	//specular lighting
	Is += pow(spec_angle_cos, shine);
}

void main(){
	float Id = 0;
	float Is = 0;
	

	// transform the vertex position
	gl_Position = projection * view * model * vtxPos;

	vec4 pos = view * model * vtxPos;
	vec4 norm = transpose(inverse(view * model))* vtxNorm;
	
	position = pos.xyz;
	normal = norm.xyz;

	calculate_light(light_position.xyz, Id, Is);

	Out.diffuseIntensity = Id;
	Out.specularIntensity = Is;
	Out.color =  vtxCol;
}