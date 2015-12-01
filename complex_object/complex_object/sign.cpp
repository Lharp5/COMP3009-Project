#include "sign.h"

Sign::Sign()
{

}
Sign::~Sign()
{

}

void Sign::setupSign(Shader* woodShader, Texture* woodTexture, Shader* signShader, Texture* signTexture)
{
	Vertices vtx;
	Indices ind;

	Cylinder *leg1, *leg2;
	leg1 = new Cylinder();
	leg2 = new Cylinder();
	Sphere *cap1, *cap2;
	cap1 = new Sphere();
	cap2 = new Sphere();
	Surface * sign1, *sign2;
	sign1 = new Surface();
	sign2 = new Surface();
	//our campfire does not have any base geometry itself so we have no indices
	numIndices = 0;
	Material surfaceMat, legsMat;
	surfaceMat.setShine(10);
	surfaceMat.setSpecular(Vector4f(0.2, 0.2, 0.2, 1));

	//creating the logs

	Cylinder::createCylinder(200, vtx, ind);
	leg1->setId("leg1");
	leg1->setMaterial(legsMat);
	leg1->setTexture(*woodTexture);
	leg1->createVAO(*woodShader, vtx, ind);
	leg1->setInitialPosition(-0.5, 0, 0);
	leg1->setInitialRotations(0, 90, 0);
	leg1->setScale(0.1, 0.1, 1);
	addChild(leg1);

	Sphere::createSphere(600, 300, vtx, ind);
	cap1->setId("cap1");
	cap1->setMaterial(legsMat);
	cap1->setTexture(*woodTexture);
	cap1->createVAO(*woodShader, vtx, ind);
	cap1->setInitialPosition(0, 0, -0.70);
	cap1->setInitialRotations(0, 0, 0);
	cap1->setScale(1, 1, 0.1);
	leg1->addChild(cap1);

	Cylinder::createCylinder(200, vtx, ind);
	leg2->setId("leg2");
	leg2->setMaterial(legsMat);
	leg2->setTexture(*woodTexture);
	leg2->createVAO(*woodShader, vtx, ind);
	leg2->setInitialPosition(0.5, 0, 0);
	leg2->setInitialRotations(0, 90, 0);
	leg2->setScale(0.1, 0.1, 1);
	addChild(leg2);

	Sphere::createSphere(600, 300, vtx, ind);
	cap2->setId("cap2");
	cap2->setMaterial(legsMat);
	cap2->setTexture(*woodTexture);
	cap2->createVAO(*woodShader, vtx, ind);
	cap2->setInitialPosition(0, 0, -0.70);
	cap2->setInitialRotations(0, 0, 0);
	cap2->setScale(1, 1, 0.1);
	leg2->addChild(cap2);

	Surface::createSurface(6, 3, 1, 1, vtx, ind);
	sign1->createVAO(*signShader, vtx, ind);
	sign1->setId("sign1");
	sign1->setTexture(*signTexture);
	sign1->setMaterial(surfaceMat);
	sign1->setInitialPosition(0, 0.15, 0);
	sign1->setInitialRotations(180, -90, 0);
	sign1->setScale(1, 1, 1);
	addChild(sign1);

	Surface::createSurface(6, 3, 1, 1, vtx, ind);
	sign2->createVAO(*signShader, vtx, ind);
	sign2->setId("sign2");
	sign2->setTexture(*signTexture);
	sign2->setMaterial(surfaceMat);
	sign2->setInitialPosition(0, 0.15, 0);
	sign2->setInitialRotations(0, 90, 0);
	sign2->setScale(1, 1, 1);
	addChild(sign2);

}

void Sign::update()
{
}