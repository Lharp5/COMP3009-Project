

//=============================================================================
// solution.c
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






#include "Solution.h"

Solution *Solution::sol = NULL;

/****************************************************************************/

Solution::Solution() : numFrames(0), ambientOn(1.0), diffuseOn(1.0), specularOn(1.0)

{
}

/*************************************************************************/


Solution::~Solution()
{

}

/******************************************************************************/


// initializing the opengl functions and windows
int Solution::initOpenGL()
{
	//initialize OpenGL
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 400);
	glutCreateWindow("Drawing Basic Objects");
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glutDisplayFunc(Solution::renderCB);
	glutReshapeFunc(Solution::winResizeCB);
	glutKeyboardFunc(Solution::keyboardCB);
	glutSpecialFunc(Solution::specialKeyboardCB);
	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);

	glewInit();


	return 0;
}

/************************************************************/

// render callback function.  This is a static funcion


void Solution::renderCB()
{

	sol->render();
	
}


/************************************************************/

// keyboard callback function.  This is a static funcion


void Solution::keyboardCB(unsigned char key, int x, int y)
{
	sol->keyboard(key, x, y);
}


/************************************************************/

// special keyboard callback function.  This is a static funcion



void Solution::specialKeyboardCB(int key, int x, int y)
{
	sol->specialKeyboard(key, x, y);
}


/************************************************************/

// window resize callback function.  This is a static funcion



void Solution::winResizeCB(int width, int height)
{
	sol->winResize(width, height);
}

/************************************************************/

// timer  callback function.  This is a static funcion


void Solution::timerCB(int operation)
{

	glutTimerFunc(FRAME_TIME, Solution::timerCB, UPDATE_RENDERRED_OBJECTS);	
	sol->timer(operation);

}


/************************************************************/

// timrt  function.  


int Solution::timer(int operation)
{
	numFrames++;
	switch (operation) {
	case UPDATE_RENDERRED_OBJECTS:
		updateObjects(numFrames);
		break;
	default:
		break;
	}
	return(0);
}




/******************************************************************************/
// initialization of the solution
int Solution::initSolution()
{
	//initialize the camera.
	Vector3f viewerPosition = Vector3f(0, 1, 5);
	//Vector3f viewerPosition = Vector3f(0, 0, 5);
	Vector3f lookAtPoint = Vector3f(0, 0, 0);
	//Vector3f lookAtPoint = Vector3f(0, 0, 0);
	Vector3f upVector = Vector3f(0, 1, 0);

	camera.setCamera(viewerPosition, lookAtPoint, upVector);
	
	int rc;
	Vertices vtx;
	Indices ind;

	//fancy object
	
	Texture texture, fireTexture;
	Material material;
	Campfire campfire;

	// create the shader object
	rc = shader.createShaderProgram("phong.vert", "phong.frag");
	if (rc != 0) {
		fprintf(stderr, "Error in generating shader (solution)\n");
		rc = -1; 
		goto err;
	}

	rc = phongShader.createShaderProgram("phong.vert", "phong.frag");
	if (rc != 0) {
		fprintf(stderr, "Error in generating shader (solution)\n");
		rc = -1;
		goto err;
	}

	texture.loadTextures("tree_bark_long.jpg", GL_TEXTURE_2D, GL_TEXTURE1);
	fireTexture.loadTextures("fire_temp.jpg", GL_TEXTURE_2D, GL_TEXTURE2);

	campfire.setupCampfire(&phongShader, &texture, &shader, &fireTexture);
	campfire.setInitialPosition(0, 0, 0);
	campfire.setInitialRotations(0, 0, 0);
	campfire.setScale(1, 1, 1);
	world.addObject(&campfire);

	err:
	return 0;
}


/**********************************************************************/

void Solution::setSolution(Solution * _sol)
{
	Solution::sol = _sol;
}



/************************************************************/

// render function.  


void Solution::render()
{

	Vector4f lightPos;
	Vector4f lightColour = Vector4f(1.0, 1.0, 1.0, 1.0);
	Matrix4f viewMat, projMat;	

	// use the created shader
	shader.useProgram(1);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	// set the camera matrix
	viewMat = Matrix4f::cameraMatrix(Vector3f(200, 200, 200), Vector3f(100, 10, 100), Vector3f(0, 1, 0));
	// move matrix to shader
	//shader.copyMatrixToShader(viewMat, "view");
	
	lightPos = camera.getViewMatrix() * Vector4f(0, 0, 0, 1);

	// set the projection matrix
	projMat = Matrix4f::symmetricPerspectiveProjectionMatrix(30, 2, .1, 1000);
	// move matrix to shader
	shader.useProgram(1);
	shader.copyMatrixToShader(camera.getViewMatrix(), "view");
	shader.copyMatrixToShader(projMat, "projection");

	shader.copyFloatToShader(ambientOn, "ambientOn");
	shader.copyFloatToShader(diffuseOn, "diffuseOn");
	shader.copyFloatToShader(specularOn, "specularOn");

	shader.copyVectorToShader(lightPos, "light_position");
	shader.copyVectorToShader(lightColour, "light_colour");
	
	//phong shader

	phongShader.useProgram(1);
	phongShader.copyMatrixToShader(camera.getViewMatrix(), "view");
	phongShader.copyMatrixToShader(projMat, "projection");

	phongShader.copyFloatToShader(ambientOn, "ambientOn");
	phongShader.copyFloatToShader(diffuseOn, "diffuseOn");
	phongShader.copyFloatToShader(specularOn, "specularOn");

	phongShader.copyVectorToShader(lightPos, "light_position");
	phongShader.copyVectorToShader(lightColour, "light_colour");
	// render the objects
	world.render();
	glutSwapBuffers();
}


/************************************************************/

// keyboard handling function. 


void Solution::keyboard(unsigned char key, int x, int y)
{

	switch (key){
	case 27:
		exit(1);
		break;
	case 'w':
		camera.moveForward(0.2);
		break;
	case 's':
		camera.moveBack(0.2);
		break;
	case 'a':
		camera.moveLeft(0.2); 
		break;
	case 'd':
		camera.moveRight(0.2);
		break;
	case 'q':
		camera.roll(-1);
		break;
	case 'e':
		camera.roll(1);
		break;
	case '+':
		world.getObject("ball")->getMaterial()->increaseShine(2);
		break;
	case '-':
		world.getObject("ball")->getMaterial()->reduceShine(2);
		break;
	case 'M':
		ambientOn = 0.0;
		break;
	case 'm':
		ambientOn = 1.0;
		break;
	case 'N':
		diffuseOn = 0.0;
		break;
	case 'n':
		diffuseOn = 1.0;
		break;
	case 'B':
		specularOn = 0.0;
		break;
	case 'b':
		specularOn = 1.0;
		break;
	case'i':
		world.getObject("ball")->incrementScale(0.5, 0, 0);
		break;
	case'j':
		world.getObject("ball")->incrementScale(-0.5, 0, 0);
		break;
	case'k':
		world.getObject("ball")->incrementScale(0, 0.5, 0);
		break;
	case'l':
		world.getObject("ball")->incrementScale(0, -0.5, 0);
		break;
	case'r': //resetting our scale back to our initial scale
		world.getObject("ball")->setScale(1, 1, 1);
		break;
	default:
		return;
	}
}


/************************************************************/

// special keyboard handling  function.  



void Solution::specialKeyboard(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_UP:
		camera.pitch(1);
		break;
	case GLUT_KEY_DOWN:
		camera.pitch(-1);
		break;
	case GLUT_KEY_LEFT:
		camera.yaw(1);
		break;
	case GLUT_KEY_RIGHT:
		camera.yaw(-1);
		break;
	}
}


/************************************************************/

// window resize handling function.  



void Solution::winResize(int width, int height)
{
}

/***********************************************************/
// update the state of the objects

int Solution::updateObjects(int numFrames)
{
	// recall that this will be carried out in the model space
	Sphere* spherePtr = (Sphere*) world.getObject("ball1");

	glutPostRedisplay();
	return 0;
}
