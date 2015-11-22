#include "material.h"

Material::Material():
ambient(Vector4f(0.2, 0.2, 0.2, 1)), diffuse(Vector4f(0.75, 0.75, 0.75, 1)), specular(Vector4f(0.8, 0.8, 0.8, 1)), shine(5)
{
}

Material::Material(Vector4f amb, Vector4f diff, Vector4f spec, float shineComponent) :
ambient(amb), diffuse(diff), specular(spec), shine(shineComponent)
{

}
void Material::setComponents(Vector4f amb, Vector4f diff, Vector4f spec, float shineComponent)
{
	ambient = amb;
	diffuse = diff;
	specular = spec;
	shine = shineComponent;
}
void Material::setAmbient(const Vector4f amb)
{
	ambient = amb;
}
void Material::setDiffuse(const Vector4f diff)
{
	diffuse = diff;
}
void Material::setSpecular(const Vector4f spec)
{
	specular = spec;
}
void Material::setShine(const float shineComponent)
{
	shine = shineComponent;
}

Vector4f Material::getAmbient() const
{
	return ambient;
}
float Material::getShine() const
{
	return shine;
}
Vector4f Material::getDiffuse() const
{
	return diffuse;
}
Vector4f Material::getSpecular() const
{
	return specular;
}

void Material::increaseShine(const float diff){
	shine += diff;
	//incase a negative was passed
	shine = max(shine, 0);
}
void Material::reduceShine(const float diff)
{
	shine -= diff;
	//ensuring it does not go below 0
	shine = max(shine, 0);
}

void Material::render(Shader shader)
{
	shader.useProgram(1);
	shader.copyVectorToShader(ambient, "ambient");
	shader.copyVectorToShader(diffuse, "diffuse");
	shader.copyVectorToShader(specular, "specular");
	shader.copyFloatToShader(shine, "shine");

}