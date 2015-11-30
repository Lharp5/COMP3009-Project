#ifndef CAMPFIRE_H
#define CAMPFIRE_H

#include "graphicsObject.h"
#include "cylinder.h"
#include "sphere.h"
#include <math.h>
#include "particle_system.h"
class Campfire: public GraphicsObject{
public:
	Campfire();
	~Campfire();

	void setupCampfire(Shader* logShader, Texture* logTexture, Shader *fireShader, Texture* fireTexture, Shader* rockShader, Texture* rockTexture);
	void update();
private:
	void setupRocks(Shader* rockShader, Texture* rockTexture);
};

#endif