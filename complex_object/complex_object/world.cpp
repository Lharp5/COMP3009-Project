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

bool World::addEffect(ParticleSystem* effect)
{

	if (getObject(effect->getId()) != NULL){
		std::cout << "Failed to add Effect" << std::endl;
		return false;
	}
	effects.push_back(effect);
	return true;
}

bool World::addShader(Shader* shader)
{
	shaders.push_back(shader);
	return true;
}

ParticleSystem* World::getEffect(std::string id)
{
	for (std::vector<ParticleSystem*>::iterator i = effects.begin(); i < effects.end(); ++i){
		if ((*i)->getId() == id)
			return (*i);
	}

	return NULL;
}


int World::render(Matrix4f projMat, Matrix4f viewMatrix)
{	
	Vector4f lightPos = viewMatrix * Vector4f(0, 0, 0, 1);
	Vector4f lightColour = Vector4f(0.612, 0.165, 0, 1.0);
	for (std::vector<Shader*>::iterator i = shaders.begin(); i < shaders.end(); ++i){
		(*i)->useProgram(1);
		(*i)->copyMatrixToShader(viewMatrix, "view");
		(*i)->copyMatrixToShader(projMat, "projection");
		(*i)->copyVectorToShader(lightPos, "light_position");
		(*i)->copyVectorToShader(lightColour, "light_colour");
	}
	for (std::vector<GraphicsObject*>::iterator i = objects.begin(); i < objects.end(); ++i){
		(*i)->render();
	}
	for (std::vector<ParticleSystem*>::iterator i = effects.begin(); i < effects.end(); ++i){
		(*i)->render();
	}
	return 0;
}