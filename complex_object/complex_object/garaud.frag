#version 330


uniform vec4 light_colour;

//controls
uniform float ambientOn;
uniform float diffuseOn;
uniform float specularOn;

//material info
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;

in Data{
	vec4 color;
	float diffuseIntensity;
	float specularIntensity;
}In;

out vec4 color;

void main()
{
	// output the colour
	vec4 colour_val = vec4(0,0,0,0);

	// set the colour
	if(ambientOn == 1.0){
		colour_val += In.color * ambient;
	}
	if(diffuseOn == 1.0){
		colour_val += In.color * diffuse* In.diffuseIntensity * light_colour;
	}
	if(specularOn == 1.0){
		colour_val +=  specular*In.specularIntensity * light_colour;
	}

	color = colour_val;
	//gl_FragColor=vec4(1.0,0.0,0.0,0.0);
}