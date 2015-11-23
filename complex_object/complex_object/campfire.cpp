#include "campfire.h"

Campfire::Campfire()
{

}
Campfire::~Campfire()
{

}

void Campfire::setupCampfire(Shader *logShader, Texture* logTexture)
{
	Vertices vtx;
	Indices ind;

	Cylinder log;
	//our campfire does not have any base geometry itself so we have no indices
	numIndices = 0;

	Cylinder::createCylinder(200, vtx, ind, Vector4f(0, 0, 1, 1));
	log.setId("log1");
	log.setMaterial(material);
	log.setTexture(*logTexture);
	log.createVAO(*logShader, vtx, ind);
	log.setInitialPosition(0, 0, 0);
	log.setInitialRotations(0, 90, 0);
	log.setScale(0.25, 0.25, 1);
	addChild(&log);

}

void Campfire::update()
{

}