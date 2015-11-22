#version 330 core

uniform sampler2D texture;

uniform vec4 light_position;
uniform vec4 light_colour;

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform float shine;

uniform float ambientOn;
uniform float diffuseOn;
uniform float specularOn;


in Data{
	vec4 color;
	vec3 norm_interp;
	vec3 pos_interp;
	vec2 texCoord;
}In;

out vec4 color;

void calculate_light(in vec3 light_pos, inout float Id, inout float Is)
{

	// Phong shading

	vec3 N; // Interpolated normal for fragment
	vec3 L; // Light-source direction
	vec3 V; // View direction
	vec3 R; // Refelction Vector


	//calculating normal
    N = normalize(In.norm_interp);

	//light position
	L = (light_pos - In.pos_interp);
	L = normalize(L);

	//diffuse lighting
	Id += max(dot(N, L), 0.0);
	
	//Specular component
	V = - In.pos_interp; // Eye position is (0, 0, 0) in view coordinates
    V = normalize(V);

	//reflection vector
    R = -L + 2 *dot(L, N) * N; // reflection vector
    R = normalize(R);

	//spec_angle_cos
    float spec_angle_cos = max(dot(V, R), 0.0);
	
	//specular lighting
	Is += pow(spec_angle_cos, shine);
}

void main()
{
	float Id = 0;
	float Is = 0;
	vec4 colour_val = vec4(0,0,0,1);

	calculate_light(light_position.xyz, Id, Is);
	// output the colour
	if(ambientOn == 1.0){
		colour_val += texture2D(texture, In.texCoord) * ambient;
	}
	if(diffuseOn == 1.0){
		colour_val += texture2D(texture, In.texCoord) * diffuse*Id * light_colour;
	}
	if(specularOn == 1.0){
		colour_val +=  specular*Is * light_colour;  //is this needed?
	}
	color = colour_val;
	//color = texture2D(texture, In.texCoord);
}