#ifndef PARTICLE_H
#define PARTICLE_H

#include "glew.h"
#include "glut.h"
#include "nuss_math.h"
#include "Shader.h"
#include "graphicsObject.h"
#include <time.h>

class ParticleSystem: public GraphicsObject{
public:
	ParticleSystem();
	~ParticleSystem();
	int ParticleSystem::createVAO(Shader newShader, Vertices vtx, Indices ind);
	static int ParticleSystem::createSphere(int numParticles, float maxspray, Vertices &vtx, Indices &ind);
	static int ParticleSystem::createCone(int numParticles, float maxspray, Vertices &vtx, Indices &ind);
	virtual int render();
private:

};

#endif //PARTICLE_H