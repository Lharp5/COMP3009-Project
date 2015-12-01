#ifndef SIGN_H
#define SIGN_H

#include "graphicsObject.h"
#include "cylinder.h"
#include "sphere.h"
#include <math.h>
#include "particle_system.h"
#include "Surface.h"
class Sign: public GraphicsObject{
public:
	Sign();
	~Sign();

	void setupSign(Shader* woodShader, Texture* woodTexture, Shader* signShader, Texture* signTexture);
	void update();
private:
};

#endif //SIGN_H