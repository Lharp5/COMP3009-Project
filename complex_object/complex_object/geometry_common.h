#ifndef GEOMETRY_COMMON
#define GEOMETRY_COMMON 1


#include <vector>

#include "nuss_vector.h"


struct Vertex {
	Vertex(){}
	Vertex(const Vector4f& _pos);
	Vertex(const Vector4f _pos, const Vector4f _col, const Vector4f _norm){
		memcpy(pos, (void *)&_pos, sizeof(pos));
		memcpy(col, (void *)&_col, sizeof(col));
		memcpy(norm, (void *)&_norm, sizeof(norm));
	}

	float pos[4];
	float col[4];
	float norm[4];
};

typedef struct Vertex Vertex;



typedef std::vector<Vertex> Vertices;
typedef std::vector<unsigned int>	Indices;

#endif