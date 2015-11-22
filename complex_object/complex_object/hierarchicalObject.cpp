#include "HierarchicalObject.h"


HierarchicalObject::HierarchicalObject()
{
}


HierarchicalObject::~HierarchicalObject()
{
}


int HierarchicalObject::render(Shader shader, Matrix4f parentMat)
{
	Matrix4f mat;
	vHierarChildren::iterator it;

	mat = parentMat * modelToWorldMat();

	GraphicsObject::render(shader, parentMat);
	for (it = children.begin(); it != children.end(); it++) {
		(*it)->render(shader, mat);
	}
	return 0;
}


int HierarchicalObject::setGeometry(Shader shader, Vertices &vtx, Indices &ind)
{
	// create the first object a sphere
	createVAO(shader, vtx, ind);
	return 0;
}


int HierarchicalObject::addChild(HierarchicalObject *child)
{
	
	children.push_back(child);
	return 0;
}


int HierarchicalObject::render(Shader shader)
{
	GraphicsObject::render(shader);
	return 0;
}
