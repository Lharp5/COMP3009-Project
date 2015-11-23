#include "Texture.h"
#include "SOIL.h"



/**************************************************************************************/


Texture::Texture() :texId(-1)
{
}


/**************************************************************************************/




Texture::~Texture()
{
}



/**************************************************************************************/
//  load a texture


void Texture::loadTextures( char *imageFileName, GLuint texTarget, int texUnit)
{

	int width, height;
	unsigned char* image = NULL;

	textureUnit = texUnit;

	// add the code
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	image = SOIL_load_image(imageFileName, &width, &height, 0, SOIL_LOAD_RGB);
	
	if (image != NULL){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		SOIL_free_image_data(image);
		image = NULL;
	}

	//set the repeat behavoiur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set the sampling behaviour
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


/**********************************************************************************/

void Texture::bindToTextureUnit(int textureUnit)
{

	// add the code
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, texId);

}

void Texture::bindToTextureUnit()
{

	// add the code
	glActiveTexture(GL_TEXTURE0 + texId);
	glBindTexture(GL_TEXTURE_2D, texId);

}


/**********************************************************************************/

GLuint Texture::getTexId()
{
	return(texId);
}
/**********************************************************************************/

// the sampler id should correspond to the textureUnit

GLuint Texture::setTextureSampler(Shader shader, char *sampleName, GLuint samplerId)
{
	int location;
	int rc = 0;
	

	// add the code
	location = glGetUniformLocation(shader.getProgId(), sampleName);
	glUniform1i(location, samplerId - GL_TEXTURE0);

	err:
	return(rc);
}

GLuint Texture::setTextureSampler(Shader shader, char *sampleName)
{
	int location;
	int rc = 0;


	// add the code
	location = glGetUniformLocation(shader.getProgId(), sampleName);
	glUniform1i(location, texId);

err:
	return(rc);
}