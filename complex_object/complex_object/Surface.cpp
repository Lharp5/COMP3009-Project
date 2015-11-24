#include "Surface.h"
using namespace std;


Surface::Surface()
{
}


Surface::~Surface()
{
}


/**************************************************************************************/
/* this function creates a surface.  The sureface is genreated using two arrays.  The vertex data array which
contains the vertex data (geometry) and an index array which contains the topology of the triangles.  The trainagles
are stored in the index array as a triangle list.

Input
numCols - number of columns.  For example if numLong == 10 than the surface will have 10 columns

numRows - number rows.

height - the height of the surface.  Can beachieved by scaling the surface.

width - the width of the surface.  Can beachieved by scaling the surface.

Ouptut:

*/
int Surface::createSurface(int numLong, int numLat, float height, float width, Vertices &vtx, Indices &ind)

{
	int i, j, k;
	int numRows;
	int numCols;
	int numVtx;
	int numTriangles;
	Vector3f pos;
	Vector4f col;
	float dTexX, dTexY;	// delta for setting up the texture coordinates
	int texFactor = 1;
	Vector2f texCoord;
	float dh = 0.0;	// angle of latitude starting from the "south pole" at angle -90
	float dw = 0.0;   // angle of longtitude in the rage of 0-360
	float deltaHeight;	// the increment of the surface along the rows
	float deltaWidth;	// the increment of the surface along the columns


	numRows = numLat * 2;  // number of horizonal slabs
	numCols = numLong;	// number of vertical slabs

	numVtx = (numRows + 1) * (numCols + 1);
	vtx.resize(numVtx);
	cout << "   the vector's size is: " << vtx.size() << endl;
	cout << "   the vector's capacity is: " << vtx.capacity() << endl;
	cout << "   the vector's maximum size is: " << vtx.max_size() << endl;


	numTriangles = numRows * numCols * 2;
	ind.resize(numTriangles * 3);

	// Fill the vertex buffer with positions
	k = 0;
	dw = dh = 0.0;
	dTexX = 1.0f / numCols;
	dTexY = 1.0f / numRows;
	deltaHeight = height / numRows; // increment of height
	deltaWidth = width / numCols; // increment of width



	for (i = 0, dh = -height/2; i <= numRows; i++, dh += deltaHeight) {
		for (j = 0, dw = -width/2; j <= numCols; j++, dw += deltaWidth) {
			pos.x = dw;
			pos.y = 0;
			pos.z = dh;
			// pos.w = 1.0;  DN 26/10/2015
			texCoord.x = j*dTexX*texFactor;
			texCoord.y = i*dTexY*texFactor;
			vtx[k] = Vertex(pos, Vector4f(Vector3f::normalize(pos), 1.0), Vector3f(0,-1,0),texCoord);  //DN 26/10/2015
			k++;


		}
	}




	// fill the index buffer

	k = 0;
	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numCols; j++) {
			// fill indices for the quad
			// change by making a quad function
			ind[k++] = i * (numCols + 1) + j;
			ind[k++] = i * (numCols + 1) + j + 1;
			ind[k++] = (i + 1) * (numCols + 1) + j + 1;

			ind[k++] = i * (numCols + 1) + j;
			ind[k++] = (i + 1) * (numCols + 1) + j + 1;
			ind[k++] = (i + 1) * (numCols + 1) + j;
		}
	}


	return(0);

}


