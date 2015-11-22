#include "camera.h"

Camera::Camera()
{
}
Camera::~Camera()
{
}

void Camera::setCamera(Vector3f position, Vector3f lookAtPoint, Vector3f upVector)
{
	this->position = position;
	this->upVector = upVector;
	lookAtVector = lookAtPoint - position;

	lookAtVector.normalize();
	this->upVector.normalize();
}

void Camera::setOrientation(Vector3f lookAtVector, Vector3f upVector)
{
	lookAtVector = lookAtVector;
	upVector = upVector;
}

void Camera::roll(float degrees)
{
	Vector3f rotVector = -lookAtVector;
	Matrix4f mat;
	mat = mat.rotateVector(rotVector, degrees, 1);
	updateOrientation(mat);
}
void Camera::yaw(float degrees)
{
	Vector3f rotVector = upVector;
	Matrix4f mat;
	mat = mat.rotateVector(rotVector, degrees, 1);
	updateOrientation(mat);
}
void Camera::pitch(float degrees)
{
	//the side vector to rotate on.
	Vector3f rotVector = Vector3f::cross(lookAtVector, upVector);
	Matrix4f mat;
	mat = mat.rotateVector(rotVector, degrees, 1);
	updateOrientation(mat);
}

void Camera::updateOrientation(Matrix4f rotMat)
{
	Vector4f u;
	u = rotMat * lookAtVector;
	lookAtVector = u.to3D();
	lookAtVector.normalize();
	u = rotMat * upVector;
	upVector = u.to3D();
	upVector.normalize();
	
}

void Camera::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Camera::setPosition(Vector3f v)
{
	setPosition(v.x, v.y, v.z);
}

void Camera::move(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Camera::move(Vector3f v)
{
	move(v.x, v.y, v.z);
}

void Camera::moveForward(float units)
{
	position += lookAtVector * units;
}

void Camera::moveBack(float units)
{
	moveForward(-units);
}

void Camera::moveRight(float units)
{
	Vector3f side = lookAtVector.cross(lookAtVector, upVector);
	position += side * units;
}

void Camera::moveLeft(float units)
{
	moveRight(-units);
}

Matrix4f Camera::getViewMatrix()
{
	return Matrix4f::cameraMatrix(position, position + lookAtVector, upVector);
}