

//=============================================================================
// graphicsObject.c
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. generic class for graphics objects. 
//
//
// Description:
//--------------
//  sub classes of objects can be inherited.  The class does the main funcionality of setting and rendering objects.

//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================




#include "GraphicsObject.h"


//setting the id counter
int GraphicsObject::id = 0;
/***************************************************************************/

GraphicsObject::GraphicsObject() : vtxVBO(-1), vao(-1), indVBO(-1)
, rollAngle(0)
, numIndices(0),
name(std::to_string(id)),
materialUsed(false)
{
}

GraphicsObject::GraphicsObject(std::string newId) : vtxVBO(-1), vao(-1), indVBO(-1)
, rollAngle(0)
, numIndices(0),
name(newId)
{
}

/***************************************************************************/



GraphicsObject::~GraphicsObject()
{
}


/***************************************************************************/


void GraphicsObject::setId(std::string newId)
{
	name = newId;
}

/***************************************************************************/


std::string GraphicsObject::getId()
{
	return name;
}

bool GraphicsObject::addChild(GraphicsObject* child)
{

	if (getChild(child->getId()) != NULL){
		std::cout << "Failed to add Child" << std::endl;
		return false;
	}
	children.push_back(child);
	return true;
}

GraphicsObject* GraphicsObject::getChild(std::string id)
{
	for (std::vector<GraphicsObject*>::iterator i = children.begin(); i < children.end(); ++i){
		if ((*i)->getId() == id)
			return (*i);
	}

	return NULL;
}

/***************************************************************************/


int GraphicsObject::createVAO(Shader shader)
{
	return 0;
}


/***************************************************************************/


int GraphicsObject::createVAO(Shader newShader, Vertices vtx, Indices ind)
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
	numIndices = ind.size();

	//end creation
	glBindVertexArray(0);

	err:
	return(rc);
}



/*********************************************************************************/

int GraphicsObject::render()
{
	return render(Matrix4f::identity());
}

int GraphicsObject::render(Matrix4f parentMatrix)
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix

	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity();
	
	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation 
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle,pitchAngle,yawAngle,1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;

	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;


	//applying parent transformation
	modelMat = parentMatrix * modelMat;

	// move matrix to shader
	shader.useProgram(1);
	shader.copyMatrixToShader(modelMat, "model");


	// bind the vao
	glBindVertexArray(vao);

	// draw using indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

	// unbind the vao
	glBindVertexArray(0);

	//passing in the material information
	if (materialUsed){
		material.render(shader);
	}

	//passing the texture sample information
	if (textureUsed){
		texture.bindToTextureUnit();
		texture.setTextureSampler(shader, "texture");
	}

	renderChildren(modelMat);

	return 0;
}

void GraphicsObject::renderChildren(Matrix4f base)
{
	for (std::vector<GraphicsObject*>::iterator i = children.begin(); i < children.end(); ++i){
		(*i)->render(base);
	}
}

void GraphicsObject::setMaterial(const Material material)
{
	materialUsed = true;
	this->material = material; 
}

void GraphicsObject::setTexture(const Texture texture)
{
	textureUsed = true;
	this->texture = texture;
}

Material* const GraphicsObject::getMaterial()
{
	if (!materialUsed){
		std::cerr << "WARN: A Material has not been set, returning default material, this material is not used" << std::endl;
	}
	return &material;
}

void GraphicsObject::setShader(const Shader shader)
{
	this->shader = shader;
}

/* getShader
*	out:		shader that you wish to access
*	Purpose:	to retrieve the shader of the specific object
*/
Shader* const GraphicsObject::getShader()
{
	return &shader;
}


/*************************************************************/
// sets the initial orientation

void GraphicsObject::setInitialRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->rollAngle = rollAngle;
	this->pitchAngle = pitchAngle;
	this->yawAngle = yawAngle;

}

/*************************************************************************/

// set the initial position

void GraphicsObject::setInitialPosition(Vector3f position)
{
	this->position = position;
}

/*************************************************************************/

// set the initial position

void GraphicsObject::setInitialPosition(float x, float y, float z)
{
	this->position = Vector3f(x, y, z);
}

/*************************************************************/
// increment the courrent rotation by the given amounts

void GraphicsObject::incrementRotations(float rollAngle, float pitchAngle, float yawAngle)
{
	this->rollAngle += rollAngle;
	this->pitchAngle += pitchAngle;
	this->yawAngle += yawAngle;

}

/*************************************************************************/

// increment positin by delta position

void GraphicsObject::incrementPosition(Vector3f deltaPosition)
{
	this->position += deltaPosition;
}

/*************************************************************************/

// increment position by delta

void GraphicsObject::incrementPosition(float deltaX, float deltaY, float deltaZ)
{
	this->position += Vector3f(deltaX, deltaY, deltaZ);
}


/*************************************************************************/

// set the initial position

void GraphicsObject::setScale(Vector3f scale)
{
	this->scale = scale;
}

/*************************************************************************/

// set the initial position

void GraphicsObject::setScale(float scaleX, float scaleY, float scaleZ)
{
	this->scale = Vector3f(scaleX, scaleY, scaleZ);
}

void GraphicsObject::incrementScale(float scaleX, float scaleY, float scaleZ)
{
	scale.x += scaleX;
	scale.y += scaleY;
	scale.z += scaleZ;
	scale.x = (scale.x > 10) ? scale.x : 10;
	scale.y = (scale.y > 10) ? scale.y : 10;
	scale.z = (scale.z> 10) ? scale.z : 10;

}
