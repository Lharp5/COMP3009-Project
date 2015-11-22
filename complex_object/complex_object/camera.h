#ifndef CAMERA_H
#define CAMERA_H

#include "nuss_math.h"
#include "nuss_matrix.h"
#include "nuss_vector.h"

class Camera
{
public:
	Camera();
	~Camera();

	void setCamera(Vector3f position, Vector3f lookAtPoint, Vector3f upVector);

	void setOrientation(Vector3f lookAtVector, Vector3f upVector);
	void roll(float degrees);
	void yaw(float degrees);
	void pitch(float degrees);


	void setPosition(float x, float y, float z);
	void setPosition(Vector3f v);

	void move(float dx, float dy, float dz);
	void move(Vector3f v);

	void moveForward(float units);
	void moveBack(float units);
	void moveRight(float units);
	void moveLeft(float units);

	Matrix4f getViewMatrix();

private:
	Vector3f position;
	Vector3f upVector;
	Vector3f lookAtVector;

	void updateOrientation(Matrix4f rotMat);
};

#endif //CAMERA_H