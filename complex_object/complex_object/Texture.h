#pragma once

#include "glew.h"
#include "glut.h"
#include "geometry_common.h"
#include "Shader.h"



class Texture
{
	

	GLuint texId;  // the texture handle
	int textureUnit;	// the texture unit which will be used for the sampler

public:
	Texture();
	~Texture();

	void loadTextures(char *imageFileName, GLuint texTarget, int texUnit);
	void bindToTextureUnit(int textureUnit);
	GLuint setTextureSampler(Shader shader, char *sampleName, GLuint samplerId);
	void bindToTextureUnit();
	GLuint setTextureSampler(Shader shader, char *sampleName);

	GLuint getTexId();
};

