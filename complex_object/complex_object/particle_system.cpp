#include "particle_system.h"

ParticleSystem::ParticleSystem()
{

}

ParticleSystem::~ParticleSystem()
{

}

int ParticleSystem::createSphere(int numParticles, float maxspray, Vertices &vtx, Indices &ind)

{
	int i;
	Vector3f pos;
	Vector3f norm;
	Vector2f texCoord;
	Vector4f colour;
	Vector3f wander;

	vtx.resize(numParticles);
	std::cout << "   the vector's size is: " << vtx.size() << std::endl;
	std::cout << "   the vector's capacity is: " << vtx.capacity() << std::endl;
	std::cout << "   the vector's maximum size is: " << vtx.max_size() << std::endl;

	ind.resize(0);

	srand(time(0));
	float trad = 0.4; // Defines the starting point of the particles
	/* Create a set of points which will be the particles */
	/* This is similar to drawing a torus: we will sample points on the surface of the torus */

	float u, v, w, theta, phi, spray; // Work variables
	for (int i = 0; i < numParticles; i++){
			
		// Randomly select two numbers to define a point on the torus
		u = ((double) rand() / (RAND_MAX));
        v = ((double) rand() / (RAND_MAX));
            
		// Use u and v to define the point on the torus
        theta = u * 2.0f*M_PI;
		phi = v * 2.0f*M_PI;
        norm = Vector3f(cos(theta)*cos(phi), sin(theta)*cos(phi), sin(phi));

		pos = Vector3f(norm.x*trad, norm.y*trad, norm.z*trad);
		colour = Vector4f(((float)i) / ((float)numParticles), 0.0f, 1.0f - (((float)i) / ((float)numParticles)), 1.0f);
		texCoord = Vector2f(0, 0); //not used for particels
		// Now sample a point on a sphere to define a direction for points to wander around
		u = ((double) rand() / (RAND_MAX));
        v = ((double) rand() / (RAND_MAX));
		w = ((double) rand() / (RAND_MAX));
			
		theta = u * 2*M_PI;
		phi = acos(2.0*v * -1.0);
		spray = maxspray*pow((float) w, (float) (1.0/3.0)); // Cubic root
		wander = Vector3f(spray*sin(theta)*sin(phi), spray*cos(theta)*sin(phi), spray*cos(phi));

		norm = wander;
		vtx[i] = Vertex(pos, colour, norm, texCoord);
	}

	return(0);

}

int ParticleSystem::createCone(int numParticles, float maxspray, Vertices &vtx, Indices &ind)

{
	int i;
	Vector3f pos;
	Vector3f norm;
	Vector2f texCoord;
	Vector4f colour;
	Vector3f wander;

	vtx.resize(numParticles);
	std::cout << "   the vector's size is: " << vtx.size() << std::endl;
	std::cout << "   the vector's capacity is: " << vtx.capacity() << std::endl;
	std::cout << "   the vector's maximum size is: " << vtx.max_size() << std::endl;

	ind.resize(0);

	srand(time(0));
	/* Create a set of points which will be the particles */
	/* This is similar to drawing a torus: we will sample points on the surface of the torus */
	float u, v, w, theta, phi, spray; // Work variables
	for (int i = 0; i < numParticles; i++){

		// Randomly select two numbers to define a point on the torus
		u = ((double)rand() / (RAND_MAX));
		v = ((double)rand() / (RAND_MAX));

		//Angle we are going to use for our base
		theta = u * 2.0f*M_PI;
		phi = v * 2.0f*M_PI;

		pos = Vector3f((1 - (v / 1.0))* cos(theta), v, (1 - (v / 1.0)) * sin(theta));
		colour = Vector4f(((float)i) / ((float)numParticles), 0.0f, 1.0f - (((float)i) / ((float)numParticles)), 1.0f);
		texCoord = Vector2f(0, 0); //not used for particels
		// Now sample a point on a sphere to define a direction for points to wander around
		u = ((double)rand() / (RAND_MAX));
		v = ((double)rand() / (RAND_MAX));
		w = ((double)rand() / (RAND_MAX));

		theta = u * 2 * M_PI;
		phi = acos(2.0*v * -1.0);
		spray = maxspray*pow((float)w, (float)(1.0 / 3.0)); // Cubic root
		wander = Vector3f(spray*sin(theta)*sin(phi), spray*cos(theta)*sin(phi), spray*cos(phi));

		norm = wander;
		vtx[i] = Vertex(pos, colour, norm, texCoord);
	}

	return(0);

}

int ParticleSystem::createVAO(Shader newShader, Vertices vtx, Indices ind)
{
	int rc = 0;

	GLint location;		// location of the attributes in the shader;

	shader = newShader;

	//create vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//create vertex buffer object
	glGenBuffers(1, &vtxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vtxVBO);
	glBufferData(GL_ARRAY_BUFFER, vtx.size() * sizeof(Vertex), vtx.data(), GL_STATIC_DRAW);

	//copy the vertex position
	location = glGetAttribLocation(shader.getProgId(), "vtxPos");
	if (location == -1) {
		rc = -1;
		goto err;
	}
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

	//copy the vertex color
	location = glGetAttribLocation(shader.getProgId(), "vtxCol");
	//	if (location == -1) {
	//	rc = -2;
	//goto err;
	//}
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));

	//copy the vertex normal
	location = glGetAttribLocation(shader.getProgId(), "vtxNorm");
	//	if (location == -1) {
	//	rc = -2;
	//goto err;
	//}
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));

	// copy the texture coords
	location = glGetAttribLocation(shader.getProgId(), "texCoord");
	//	if (location == -1) {
	//	rc = -2;
	//goto err;
	//}
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	//create index buffer
	glGenBuffers(1, &indVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(GLuint), ind.data(), GL_STATIC_DRAW);
	// store the number of indices
	numIndices = vtx.size();
	//numIndices = ind.size();


	//end creation
	glBindVertexArray(0);

err:
	return(rc);
}

int ParticleSystem::render()
{
	Matrix4f modelMat;	// final model matrix
	
	//passing in the material information
	if (materialUsed){
		material.render(shader);
	}

	//passing the texture sample information
	if (textureUsed){
		texture.bindToTextureUnit();
		texture.setTextureSampler(shader, "texture");
	}

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	modelMat = getTransformationMatrix();

	// move matrix to shader
	shader.useProgram(1);
	shader.copyMatrixToShader(modelMat, "model");


	// bind the vao
	glBindVertexArray(vao);

	// draw using indices
	glDrawArrays(GL_POINTS, 0, numIndices);

	// unbind the vao
	glBindVertexArray(0);

	renderChildren(modelMat);
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	return 0;
}
