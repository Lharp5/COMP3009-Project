#pragma once
#include "HierarchicalObject.h"
class robot :
	public HierarchicalObject
{
public:
	robot();
	~robot();
	int create();
	int robot::create(Shader shader);

};

