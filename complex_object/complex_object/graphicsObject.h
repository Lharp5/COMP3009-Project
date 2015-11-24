#pragma once
#ifndef GRPHICS_IOBJECT_HEADER
#define GRPHICS_IOBJECT_HEADER

//=============================================================================
// graphicsObject.h
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


#include "glew.h"
#include "glut.h"
#include "Shader.h"
#include "geometry_common.h"
#include "nuss_vector.h"
#include "nuss_matrix.h"
#include <vector>
#include <string>
#include "material.h"
#include "Texture.h"

class GraphicsObject
{
public:
	GraphicsObject();
	GraphicsObject(std::string newId);
	virtual ~GraphicsObject();
	int createVAO(Shader shader);
	virtual int GraphicsObject::createVAO(Shader newShader, Vertices vtx, Indices ind);
	virtual int render();
	virtual int render(Matrix4f base);

	std::string getId();

	/* AddChild
	* In:		a pointer to the graphics object you wish to add as a child
	*out:		true for success, False for fail (only fails if you try to add a child with same id of another child)
	*Purpose:	Adds a child to the graphics object
	*/
	bool addChild(GraphicsObject* child);

	/*	getChild
	*	In:			ID: The id of the object you wish to find
	*	Out:		the child that you wish to find (Null if not found)
	*	Purpose:	to retrieve a child of this graphics object
	*/
	GraphicsObject* getChild(std::string id);

	/*	setID
	*	in:			string, the new id to be set
	*	Purpose:	To Set a newID (replaces a default numberical string value)
	*/
	void setId(std::string newID);

	/*	setMaterial
	*	in:			Material to be set
	*	Purpose:	To set the Material file to be used, if shader supports materials. Note: Copies the Material data over.
	*/
	void setMaterial(const Material material);

	/*	setTexture
	*	in:			Texture to be set
	*	Purpose:	To set the Texture to be used, if shader supports materials. Note: Copies the Texture data over.
	*/
	void setTexture(const Texture texture);
	
	/*	getMaterial
	*	out:		a pointer to our material
	*	Purpose:	to manipulate the material
	*/
	Material* const getMaterial();

	/*	setShader
	*	in:			shader to be set
	*	Purpose:	To set the shader
	*/
	void setShader(const Shader shader);

	/* getShader
	*	out:		shader that you wish to access
	*	Purpose:	to retrieve the shader of the specific object
	*/
	Shader* const getShader();

protected:
	static int id;
	std::string name;
	GLuint vtxVBO;  // the vertex buffer object which holds the vertices data
	GLuint vao;  // the vertex array object which holds all the data required for renderring.
	GLuint indVBO;	// index buffer for drawing the geometry
	float rollAngle;	// rotation around the z-axis
	float pitchAngle;	// rotation around the x-axis
	float yawAngle;		// rotation around the y-axis
	Vector3f position; //position relative to parent
	Vector3f scale;
	int numIndices;
	Material material;
	Shader shader;
	Texture texture;
	bool materialUsed;
	bool textureUsed;

	//rendering Children with our location as their start point
	void renderChildren(Matrix4f base);
	
	//heirarchical graphics rendering
	std::vector<GraphicsObject> children;

public:
	void setInitialRotations(float rollAngle, float pitchAngle, float yawAngle);
	void setInitialPosition(Vector3f position);
	void setInitialPosition(float x, float y, float z);
	void incrementRotations(float rollAngle, float pitchAngle, float yawAngle);
	void incrementPosition(Vector3f position);
	void incrementPosition(float deltaX, float deltaY, float deltaZ);
	void setScale(Vector3f position);
	void setScale(float x, float y, float z);
	void GraphicsObject::incrementScale(float scaleX, float scaleY, float scaleZ);



};

#endif