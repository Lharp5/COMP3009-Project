#include "particle_system.h"

ParticleSystem::ParticleSystem()
{

}

ParticleSystem::~ParticleSystem()
{

}

int ParticleSystem::createSphere(int numLong, int numLat, Vertices &vtx, Indices &ind, Vector4f colour)

{
	int i, j, k;
	int numRows;
	int numCols;
	int numVtx;
	int numTriangles;
	Vector3f pos;
	Vector4f col;
	Vector3f norm;
	Vector2f texCoord;
	float alpha;
	float beta;
	float deltaAlpha;
	float deltaBeta;

	Vector4f noColour = (-1, -1, -1, -1);

	numRows = numLat * 2;  // number of horizonal slabs
	numCols = numLong;	// number of vertical slabs

	numVtx = (numRows + 1) * (numCols + 1);
	vtx.resize(numVtx);
	std::cout << "   the vector's size is: " << vtx.size() << std::endl;
	std::cout << "   the vector's capacity is: " << vtx.capacity() << std::endl;
	std::cout << "   the vector's maximum size is: " << vtx.max_size() << std::endl;


	numTriangles = numRows * numCols * 2;
	ind.resize(numTriangles * 3);

	// Fill the vertex buffer with positions
	k = 0;
	alpha = 0.0f;  // angle of latitude starting from the "south pole"
	deltaAlpha = (float)90.0 / numLat; // increment of alpha
	beta = 0;   // angle of the longtidute 
	deltaBeta = (float)360.0 / (numLong);	// increment of beta
	float dTexX = 1.0 / numCols;
	float dTexY = 1.0 / numRows;

	for (i = 0, alpha = -90; i <= numRows; i++, alpha += deltaAlpha) {
		for (j = 0, beta = 0; j <= numCols; j++, beta += deltaBeta) {
			pos.x = cos(DegreeToRadians(alpha))*cos(DegreeToRadians(beta));
			pos.y = cos(DegreeToRadians(alpha))*sin(DegreeToRadians(beta));
			pos.z = sin(DegreeToRadians(alpha));

			//spheres normals are just the point - the center, but the center is at 0,0 so we just normalize the point
			norm = Vector3f(pos.x, pos.y, pos.z);
			norm.normalize();

			texCoord = Vector2f(j*dTexX, i*dTexY);

			if (colour == noColour){
				vtx[k] = Vertex(pos, Vector4f(pos, 1.0), norm, texCoord);
			}
			else{
				vtx[k] = Vertex(pos, colour, norm, texCoord);
			}

			k++;
		}
	}

	// fill the index buffer
	//is this needed?
	/*k = 0;
	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			// fill indices for the quad
			// change by making a quad function
			ind[k++] = i * (numCols + 1) + j;
			ind[k++] = i * (numCols + 1) + j + 1;
			ind[k++] = (i + 1) * (numCols + 1) + j + 1;

			ind[k++] = i * (numCols + 1) + j;
			ind[k++] = (i + 1) * (numCols + 1) + j + 1;
			ind[k++] = (i + 1) * (numCols + 1) + j;
		}
	}*/

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


	/* NOT NEEDED???!?!?!*/
	//create particle buffer
	//glGenBuffers(1, &indVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, indVBO);
	//glBufferData(GL_ARRAY_BUFFER, ind.size() * sizeof(GLuint), ind.data(), GL_STATIC_DRAW);
	// store the number of indices
	//numIndices = ind.size();
	numIndices = 0;

	//end creation
	glBindVertexArray(0);

err:
	return(rc);
}

int ParticleSystem::render(Matrix4f base)
{
	int ret = -1;
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	ret = GraphicsObject::render(base);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	return ret;
}