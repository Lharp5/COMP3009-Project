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

void World::setLight(Vector3f pos, Vector4f col)
{
	lightPos = pos;
	lightColour = col;
}

int World::render(Matrix4f projMat, Matrix4f viewMatrix)
{
	for (std::vector<Shader*>::iterator i = shaders.begin(); i < shaders.end(); ++i){
		(*i)->useProgram(1);
		(*i)->copyMatrixToShader(viewMatrix, "view");
		(*i)->copyMatrixToShader(projMat, "projection");
		(*i)->copyVectorToShader(viewMatrix * Vector4f(lightPos, 1.0f), "light_position");
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

void World::update(int frame)
{
	float timer = frame * 0.05;

	for (std::vector<Shader*>::iterator i = shaders.begin(); i < shaders.end(); ++i){
		(*i)->useProgram(1);
		(*i)->copyFloatToShader(timer, "timer");
	}
	
}