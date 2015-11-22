#pragma once
#include "graphicsObject.h"
class Surface :
	public GraphicsObject
{
public:
	Surface();
	~Surface();

	static int createSurface(int numLong, int numLat, float height, float width, Vertices &vtx, Indices &ind);

};

