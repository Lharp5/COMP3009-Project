#pragma once
#ifndef SOLUTION_HEADER
#define SOLUTION_HEADER



//=============================================================================
// solution.h
//
//Author: Doron Nussbaum (C) 2015 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. solution framework for assignments
//
//
// Description:
//--------------
// A simple framework for drawing objecs 
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




#include "glew.h"
#include "glut.h"

#include "Shader.h"
#include "sphere.h"
#include "cylinder.h"
#include "world.h"
#include "camera.h"
#include "campfire.h"
#include "Surface.h"
#include "sign.h"
#include <time.h>



#define UPDATE_RENDERRED_OBJECTS 1000
#define FRAME_TIME 30

class Solution
{
public:
	Solution();
	~Solution();
	// initializing the opengl functions and windows
	int initOpenGL();


	// static callback function 
	static void renderCB();
	static void keyboardCB(unsigned char key, int x, int y);
	static void specialKeyboardCB(int key, int x, int y);
	static void winResizeCB(int width, int height);
	static void timerCB(int operation);

	static void setSolution(Solution * _sol);

	// generaL shader that will be used by all objects
	// initialization of the solution
	int initSolution();

	Camera camera;
	World world;
	Shader particleShader;
	Shader phongShader;

	int numFrames;
	static Solution *sol;

	void render();
	void keyboard(unsigned char key, int x, int y);
	void specialKeyboard(int key, int x, int y);
	void winResize(int width, int height);
	int timer(int operation);

	int updateObjects(int numFrames);
};



#endif