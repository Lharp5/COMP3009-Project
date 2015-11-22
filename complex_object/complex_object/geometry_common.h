
/* FILE IS geometry_common.h 

This file contains the strucure of a vertex.



REVISIONS:
1. Created: 2012  Doron Nussbaum
2. October 26, 2015 Doron Nussbaum - Changed the vertex geometry from 4 dimensions to 3 dimensions. 



*/


#ifndef GEOMETRY_COMMON
#define GEOMETRY_COMMON 1


/*******************************************************************/
// INCLUDE FILES
#include <vector>
#include "nuss_vector.h"
#include "nuss_matrix.h"

/*******************************************************************/

// DEFGINES

#define VERTEX_DIMENSIONS 3

/*******************************************************************/

// STRUCTURES

struct Vertex {
	Vertex(){}
	Vertex(const Vector3f& pos);
	Vertex(const Vector3f _pos, const Vector4f _col, const Vector3f _norm){
		memcpy(pos, (void *)&_pos, sizeof(pos));
		memcpy(col, (void *)&_col, sizeof(col));
		memcpy(norm, (void *)&_norm, sizeof(norm));
	}
	Vertex(const Vector3f _pos, const Vector4f _col, const Vector3f _norm, Vector2f _texCoord){
		memcpy(pos, (void *)&_pos, sizeof(pos));
		memcpy(col, (void *)&_col, sizeof(col));
		memcpy(norm, (void *)&_norm, sizeof(norm));
		memcpy(texCoord, (void *)&_texCoord, sizeof(texCoord));
	}

	float pos[VERTEX_DIMENSIONS];
	float texCoord[2];
	float col[4];
	float norm[VERTEX_DIMENSIONS];
};

typedef struct Vertex Vertex;



typedef std::vector<Vertex> Vertices;
typedef std::vector<unsigned int>	Indices;

#endif