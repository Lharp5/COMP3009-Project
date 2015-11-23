#ifndef CAMPFIRE_H
#define CAMPFIRE_H

#include "graphicsObject.h"
#include "cylinder.h"

class Campfire: public GraphicsObject{
public:
	Campfire();
	~Campfire();

	void setupCampfire(Shader* logShader, Texture* logTexture);

	void update();
private:

};

#endif