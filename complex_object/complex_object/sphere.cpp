
//=============================================================================
// sphere.c
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. creates a sphere object. 
//
//
// Description:
//--------------
//  Creates sphere geometry.  Currently it is used only to create a geometry of a sphere. It can be converted to a stand alone function. 
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


#include "sphere.h"
#include <iostream>
using namespace std;



Sphere::Sphere()
{
}

Sphere::Sphere(std::string id) : GraphicsObject(id)
{
}

Sphere::~Sphere()
{
}






/*
// Function creates a sphere geometry

input:
numLong - number of longitudes
numLat - number of latituudes.  Note that the number of latitudes is defined only for the northern hemishphere


*/

int Sphere::createSphere(int numLong, int numLat, Vertices &vtx, Indices &ind)
{
	return createSphere(numLong, numLat, vtx, ind, Vector4f(-1, -1, -1, -1));
}

int Sphere::createSphere(int numLong, int numLat, Vertices &vtx, Indices &ind, Vector4f colour)

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
	cout << "   the vector's size is: " << vtx.size() << endl;
	cout << "   the vector's capacity is: " << vtx.capacity() << endl;
	cout << "   the vector's maximum size is: " << vtx.max_size() << endl;


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

	k = 0;
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
	}

	return(0);

}





/*********************************************************************************/

/*
int Sphere::render(Shader shader)
{
	Matrix4f rotMat;  // rotation matrix;
	Matrix4f scaleMat; // scaling matrix;
	Matrix4f transMat;	// translation matrix
	Matrix4f modelMat;	// final model matrix

	// set the transformation matrix - the model transfomration
	modelMat = Matrix4f::identity(); // = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);

	// set the scaling - this is model space to model space transformation
	scaleMat = Matrix4f::scale(scale.x, scale.y, scale.z);
	modelMat = scaleMat * modelMat;

	// set the rotation  - this is model space to model space transformation
	cout << "ROLL: "<<rollAngle << " PITCH: "<<pitchAngle <<" yaw: "<<yawAngle  <<endl;
	rotMat = Matrix4f::rotateRollPitchYaw(rollAngle, pitchAngle, yawAngle, 1);
	// note that we always multiply the new matrix on the left
	modelMat = rotMat * modelMat;

	// set the orientation  - this is model space to model space transformation 
	// Add code here


	// set the translation - this is model space to world space transformation
	transMat = Matrix4f::translation(position);
	modelMat = transMat * modelMat;

	// move matrix to shader
	shader.copyMatrixToShader(modelMat, "model");


	// bind the vao
	glBindVertexArray(vao);

	// draw using indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

	// unbind the vao
	glBindVertexArray(0);

	return 0;
}
*/




/*******************************************************************************/
// future funcdtion to create internal representation of a sphere

int Sphere::createGeom(int numLongs, int numLat)
{
//	int numLong, int numLat, float radius, struct sphereVertex **vtx, int *numVtx1, GLuint **ind, int *numInd1
	return 0;
}


