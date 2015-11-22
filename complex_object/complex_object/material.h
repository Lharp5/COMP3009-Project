#ifndef MATERIAL_H
#define MATERIAL_H

#include "nuss_vector.h"
#include "Shader.h"

class Material{
public:
	Material();
	Material(Vector4f amb, Vector4f diff, Vector4f spec, float shineComponent);
	void setComponents(Vector4f amb, Vector4f diff, Vector4f spec, float shineComponent);
	void setAmbient(const Vector4f amb);
	void setDiffuse(const Vector4f diff);
	void setSpecular(const Vector4f spec);
	void setShine(const float shineComponent);

	void increaseShine(const float diff);
	void reduceShine(const float diff);

	Vector4f getAmbient() const;
	float getShine() const;
	Vector4f getDiffuse() const;
	Vector4f getSpecular() const;
	void render(Shader shader);

private:
	Vector4f ambient;
	Vector4f diffuse;
	Vector4f specular;
	float shine;



};

#endif