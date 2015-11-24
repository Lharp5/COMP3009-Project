#ifndef PARTICLE_H
#define PARTICLE_H

#include "glew.h"
#include "glut.h"
#include "Shader.h"
#include "graphicsObject.h"

class ParticleSystem: public GraphicsObject{
public:
	ParticleSystem();
	~ParticleSystem();
	int ParticleSystem::createVAO(Shader newShader, Vertices vtx, Indices ind);
	static int ParticleSystem::createSphere(int numLong, int numLat, Vertices &vtx, Indices &ind, Vector4f colour);
	virtual int render(Matrix4f base);
private:

};

#endif //PARTICLE_H