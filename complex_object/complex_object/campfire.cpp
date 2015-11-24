#include "campfire.h"

Campfire::Campfire()
{

}
Campfire::~Campfire()
{

}

void Campfire::setupCampfire(Shader *logShader, Texture* logTexture, Shader *fireShader, Texture* fireTexture, Shader* rockShader, Texture* rockTexture)
{
	Vertices vtx;
	Indices ind;

	Cylinder *log1, *log2, *log3, *log4;
	log1 = new Cylinder();
	log2 = new Cylinder();
	log3 = new Cylinder();
	log4 = new Cylinder();
	//our campfire does not have any base geometry itself so we have no indices
	numIndices = 0;
	Material logMat, fireMat;
	logMat.setShine(200);
	logMat.setSpecular(Vector4f(0.1, 0.1, 0.1, 1));

	//creating the logs

	Cylinder::createCylinder(200, vtx, ind, Vector4f(0, 0, 1, 1));
	log1->setId("log1");
	log1->setMaterial(logMat);
	log1->setTexture(*logTexture);
	log1->createVAO(*logShader, vtx, ind);
	log1->setInitialPosition(0, 0, 0.25);
	log1->setInitialRotations(0, 60, 0);
	log1->setScale(0.125, 0.125, 0.5);
	addChild(log1);

	log2->setId("log2");
	log2->setMaterial(logMat);
	log2->setTexture(*logTexture);
	log2->createVAO(*logShader, vtx, ind);
	log2->setInitialPosition(0, 0, -0.25);
	log2->setInitialRotations(0, -60, 0);
	log2->setScale(0.125, 0.125, 0.5);
	addChild(log2);

	log3->setId("log3");
	log3->setMaterial(logMat);
	log3->setTexture(*logTexture);
	log3->createVAO(*logShader, vtx, ind);
	log3->setInitialPosition(0.25, 0, 0);
	log3->setInitialRotations(0, 90, 30);
	log3->setScale(0.125, 0.125, 0.5);
	addChild(log3);

	log4->setId("log4");
	log4->setMaterial(logMat);
	log4->setTexture(*logTexture);
	log4->createVAO(*logShader, vtx, ind);
	log4->setInitialPosition(-0.25, 0, 0);
	log4->setInitialRotations(0, 90, -30);
	log4->setScale(0.125, 0.125, 0.5);
	addChild(log4);

	//TODO replace with particle effect
	ParticleSystem *fire = new ParticleSystem();
	ParticleSystem::createSphere(60, 30, vtx, ind, Vector4f(1, 0, 0, 1));
	//Sphere *fire = new Sphere();
	//Sphere::createSphere(200, 100, vtx, ind, Vector4f(1, 0, 0, 1));

	fireMat.setAmbient(Vector4f(1, 1, 1, 1));
	
	fire->setId("fire");
	fire->setMaterial(fireMat);
	fire->createVAO(*fireShader, vtx, ind);
	fire->setInitialPosition(0, 0, 0);
	fire->setInitialRotations(0, 90, 0);
	fire->setScale(0.15, 0.15, 0.15);
	fire->setTexture(*fireTexture);
	addChild(fire);

	//circle of rocks around my campfire
	setupRocks(rockShader, rockTexture);
}

void Campfire::update()
{

}

void Campfire::setupRocks(Shader* rockShader, Texture* rockTexture)
{
	Sphere* rock[10];
	Material rockMat;
	Vertices vtx;
	Indices ind;

	float radius = 0.55; //radius of the campfire
	float angle = (M_PI * 2) / 10;

	Sphere::createSphere(200, 100, vtx, ind, Vector4f(1, 0, 0, 1));

	for (int i = 0; i < 10; i++){
		rock[i] = new Sphere();
		rock[i]->setId("rock" + std::to_string(i));
		rock[i]->setMaterial(rockMat);
		rock[i]->createVAO(*rockShader, vtx, ind);
		rock[i]->setInitialPosition(radius*sin(i*angle), -0.3, radius*cos(i*angle));
		rock[i]->setInitialRotations(0, 0, 0);
		rock[i]->setScale(0.15, 0.15, 0.15);
		rock[i]->setTexture(*rockTexture);
		addChild(rock[i]);
	}
}
