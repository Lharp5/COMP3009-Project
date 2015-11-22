#ifndef WORLD_H
#define WORLD_H

#include "graphicsObject.h"
#include <vector>
class World
{
public:
	World();
	~World();
	/* addObject
	*	In:			Pointer to the object you wish to add to the world
	*	out:		true if successful, false if not (id already matches an object assigned to the world)
	*	Purpose:	add a root object to the World, this will put the object at the top of the world heirarchy. Note gets copied over.
	*/
	bool addObject(GraphicsObject* myObject);
	GraphicsObject* getObject(std::string id);
	int render();
private:
	std::vector<GraphicsObject> objects;
};


#endif
