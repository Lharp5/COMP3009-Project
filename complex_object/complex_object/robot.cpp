#include "robot.h"
#include "sphere.h"
#include "cylinder.h"


robot::robot()
{
}


robot::~robot()
{
}


int robot::create()
{

	return 0;
}


int robot::create(Shader shader)
{
	Vertices vtx;
	Indices ind;


	// create the first object a sphere
	Sphere::createSphere(20, 10, vtx, ind);
	createVAO(shader, vtx, ind);

	return 0;
}
