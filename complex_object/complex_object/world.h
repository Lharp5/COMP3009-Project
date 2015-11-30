#ifndef WORLD_H
#define WORLD_H

#include "graphicsObject.h"
#include <vector>
#include "particle_system.h"
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
	bool addEffect(ParticleSystem* effect);
	bool addShader(Shader* shader);
	GraphicsObject* getObject(std::string id);
	ParticleSystem* getEffect(std::string id);
	int render(Matrix4f projMat, Matrix4f viewMatrix);
private:
	std::vector<GraphicsObject*> objects;
	std::vector<ParticleSystem*> effects;
	std::vector<Shader*> shaders;
};


#endif
