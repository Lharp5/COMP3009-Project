#ifndef CAMPFIRE_H
#define CAMPFIRE_H

#include "graphicsObject.h"
#include "cylinder.h"
#include "sphere.h"
class Campfire: public GraphicsObject{
public:
	Campfire();
	~Campfire();

	void setupCampfire(Shader* logShader, Texture* logTexture, Shader *fireShader, Texture* fireTexture);
	int render();
	void update();
private:

};

#endif