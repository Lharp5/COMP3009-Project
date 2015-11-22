#pragma once
#include "graphicsObject.h"
#include "vector"


class HierarchicalObject : public GraphicsObject
{
public:
	HierarchicalObject();
	~HierarchicalObject();

private:
	std::vector<HierarchicalObject *> children;
public:
	int render(Shader shader, Matrix4f parentMat);
	int setGeometry(Shader shader, Vertices &vtx, Indices &ind);
	int addChild(HierarchicalObject * child);
	int render(Shader shader);
};

typedef std::vector<HierarchicalObject *> vHierarChildren;
