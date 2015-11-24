#pragma once

#ifndef SHADER_HEADER
#define SHADER_HEADER


//=============================================================================
// shader.h
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. wrap around opengl shaders. 
//
//
// Description:
//--------------
//  The wrap around helps in checking the code for errors since this is a simple repetetive task.

//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================


#include <windows.h>


#include "glew.h"
#include "nuss_matrix.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif

#include "gl/gl.h"

class Shader
{
public:
	Shader(void);
	~Shader(void);

	// creates a shader program from files vsFileName and fsFileName
	int createShaderProgram(char * vsFileName, char * fsFileName, char* gsFileName = "_NOT_INCLUDED_");
	GLuint	getProgId() const { return shaderProgramid; }

	int printShaderStatus(void);
	void useProgram(int useProg);
	int copyMatrixToShader(const Matrix4f matrix, const char* name);
	//drops the W from the vector
	int copyVectorToShader(const Vector4f vector, const char* name);
	int copyVectorToShader(const Vector3f vector, const char* name);
	int copyFloatToShader(const float num, const char* name);

private:
	GLuint vertShaderid;
	GLuint fragShaderid;
	GLuint shaderProgramid;
	GLuint geoShaderid;
	char * readCode(char * fileName);
	int createShaderObj(char* fileName, int shaderType, GLuint *shaderid);
	// functions creates a shader program.  The two shader programs (vertex and fragment) were already compiled.
	GLint ceateShaderProgram(GLint vertShaderid, GLint fragShaderid, GLint geoShaderid, GLuint *shaderProgId);
	int createShaderProgram(char * vsFileName, char * fsFileName, GLuint *shaderProgramid);



};


#endif