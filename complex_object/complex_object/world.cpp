#include "world.h"

World::World()
{
}

World::~World()
{
}

bool World::addObject(GraphicsObject* obj)
{
	
	if (getObject(obj->getId()) != NULL){
		std::cout << "Failed to add Object" << std::endl;
		return false;
	}
	objects.push_back(obj);
	return true;
}

GraphicsObject* World::getObject(std::string id)
{
	for (std::vector<GraphicsObject*>::iterator i = objects.begin(); i < objects.end(); ++i){
		if ((*i)->getId() == id)
			return (*i);
	}

	return NULL;
}


int World::render()
{	
	for (std::vector<GraphicsObject*>::iterator i = objects.begin(); i < objects.end(); ++i){
		(*i)->render();
	}
	return 0;
}