#ifdef _WIN32
#include <windows.h>
#include "Rasterizer.h"
#include "Globals.h"
#endif

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static float* zBuffer = new float[window_width * window_height];

using namespace std;


Matrix4 P;
Matrix4 D;
Drawable *toDraw;
//Camera *rCamera = &Globals::camera;
Vector4 imSp;
Vector4 toRasterize;
Vector3 coords1;
Vector3 a, b, c, an, bn, cn;
Vector3 vertex;

float z;
int scene = 1;
int debug;

Rasterizer::Rasterizer(Drawable *object, int debug1){
	toDraw = object;
	debug = debug1;
}
Rasterizer::~Rasterizer(){

}

struct Color1    // generic color
{
	float r, g, b;
};

void loadData()
{
	// put code to load data model here
}

// Clear frame buffer
void clearBuffer()
{
	Color1 clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
		zBuffer[i] = 1.0;
	}
}

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{
	int offset = y*window_width * 3 + x * 3;
	pixels[offset] = r;
	pixels[offset + 1] = g;
	pixels[offset + 2] = b;
}

void Rasterizer::rasterizeTriangle(Vector3 a, Vector3 b, Vector3 c, Vector3 a1, Vector3 b1, Vector3 c1, bool zBuf)
{
	float red, green, blue;
	float alpha, beta, gamma;
	float Aa, Ab, Ac, A;
	int minX, minY, maxX, maxY;
	Vector3 p;
	Vector3 Va, Vb, Vc, V;
	
	minX = min(a[0], b[0]);
	minX = min(minX, c[0]);
	minX = max(minX, 0);

	minY = min(a[1], b[1]);
	minY = min(minY, c[1]);
	minY = max(minY, 0);

	maxX = max(a[0], b[0]);
	maxX = max(maxX, c[0]);
	maxX = min(maxX, window_width-1);

	maxY = max(a[1], b[1]);
	maxY = max(maxY, c[1]);
	maxY = min(maxY, window_height-1);
	
	for (int x = minX; x <= maxX; x++){
		for (int y = minY; y <= maxY; y++){
			if (debug){
				if (y == minY || y == maxY || x == minX || x == maxX)
					drawPoint(x, y, 1.0, 1.0, 1.0);
			}
			p.set(x, y, 0);
			Va = (b - p).cross(c - p);
			Aa = (Va.magnitude()) / 2.0;
			Vb = (c - p).cross(a - p);
			Ab = (Vb.magnitude()) / 2.0;
			Vc = (a - p).cross(b - p);
			Ac = (Vc.magnitude()) / 2.0;
			V = (c - b).cross(a - b);
			A = (V.magnitude()) / 2.0;
			
			srand(a[0] * b[0] * c[0]);

			alpha = (Aa / A) * ((Va.dot(V)) / (Va.magnitude() * V.magnitude()));
			beta = (Ab / A) * ((Vb.dot(V)) / (Vb.magnitude() * V.magnitude()));
			gamma = (Ac / A) * ((Vc.dot(V)) / (Vc.magnitude() * V.magnitude()));
			red = 1.0;
			green = 1.0;
			blue = 1.0;
			if (scene != 4){
				red = (float)rand() / (float)RAND_MAX;
				green = (float)rand() / (float)RAND_MAX;
				blue = (float)rand() / (float)RAND_MAX;
			}

				if (alpha >= 0 && alpha <= 1){
					if (beta >= 0 && beta <= 1){
						if (gamma >= 0 && gamma <= 1){
							z = 0.01;
							if (zBuf)
								z = a[2] * alpha + b[2] * beta + c[2] * gamma;
							if (zBuffer[y*window_height + x] > z && z > 0){
								if (zBuf)
									zBuffer[y*window_height + x] = z;
								if (scene == 4){															
											red = alpha*a1[0] + beta*b1[0] + gamma*c1[0];
											green = alpha*a1[1] + beta*b1[1] + gamma*c1[1];
											blue = alpha*a1[2] + beta*b1[2] + gamma*c1[2];
											//printf("red: %f, green: %f, blue: %f\n", red, green, blue);
								}
								drawPoint(x, y, red, green, blue);
							}

							
						}
					}
				}
			}

		}
}


// Called whenever the window size changes
void Rasterizer::reshape(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];

	delete[] zBuffer;
	zBuffer = new float[window_width * window_height];

	P = P.makePerspectiveProjection((M_PI/3), (float)window_width, (float)window_height, 1.0, 1000.0);
	D = D.makeViewport(0, window_width, 0, window_height);
}

void Rasterizer::draw(int state)
{
	if (state == 0)
	{
			toDraw->draw(Globals::drawData);
	}
	else
	{
		clearBuffer();

		float vertices[] = {
			-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
			-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
			4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
			4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
			4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
			-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

			-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
			-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
			4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
			-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
			4, 4, -4, -4, 4, -4, 0, 8, -4 };

		int indices[] = {
			0, 2, 3, 0, 1, 2,      // front face
			4, 6, 7, 4, 5, 6,      // left face
			8, 10, 11, 8, 9, 10,     // back face
			12, 14, 15, 12, 13, 14,   // right face
			16, 18, 19, 16, 17, 18,   // top face
			20, 22, 23, 20, 21, 22,   // bottom face

			24, 26, 27, 24, 25, 26,   // grass
			28, 29, 30,             // front attic wall
			31, 33, 34, 31, 32, 33,   // left slope
			35, 37, 38, 35, 36, 37,   // right slope
			39, 40, 41 };

		float verticesC[] = {
			5.0, 5.0, 5.0,//+++ 0
			5.0, 5.0, -5.0,//++- 1
			5.0, -5.0, 5.0, //+-+ 2
			5.0, -5.0, -5.0, // +-- 3
			-5.0, 5.0, 5.0, // -++ 4
			-5.0, 5.0, -5.0, // -+- 5
			-5.0, -5.0, 5.0, // --+ 6
			-5.0, -5.0, -5.0 // --- 7
		};
		int indicesC[] = {
			4, 0, 6,//front
			2, 6, 0,//front
			1, 3, 2,//right
			0, 1, 2,//right
			1, 3, 7,//back
			5, 1, 7,//back
			5, 7, 6,//left
			4, 5, 6,//left
			5, 0, 4,//top
			5, 1, 0,//top
			7, 6, 2,//bottom
			7, 2, 3 };//bottom
		float normalsC[] = {
			0.0, 0.0, 1.0,//front
			0.0, 0.0, 1.0,
			1.0, 0.0, 0.0,//right
			1.0, 0.0, 0.0,
			0.0, 0.0, -1.0,//back
			0.0, 0.0, -1.0,
			-1.0, 0.0, 0.0,//left
			-1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,//top
			0.0, 1.0, 0.0,
			0.0, -1.0, 0.0,//bottom
			0.0, -1.0, 0.0

		};

		if (scene == 1){
			if (typeid(*toDraw) == typeid(OBJObject)){
				OBJObject *o = (OBJObject*)toDraw;
				std::vector<Vector3*>* vertices = o->getVertices();
				for (auto iterator = vertices->begin(); iterator != vertices->end(); iterator++){
					toRasterize.set((*(*iterator))[0], (*(*iterator))[1], (*(*iterator))[2], 1);
					vertex = rasterizeVertex(toRasterize);
					if (vertex[0] <= window_width - 1 && vertex[1] <= window_height - 1){
						if (vertex[0] >= 0 && vertex[1] >= 0){
							drawPoint(vertex[0], vertex[1], 1.0, 1.0, 1.0);
						}
					}
				}
				glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
			}
			else if (typeid(*toDraw) == typeid(House)){
				for (int i = 0; i < 126; i = i + 3){
					toRasterize.set(vertices[i], vertices[i + 1], vertices[i + 2], 1);
					vertex = rasterizeVertex(toRasterize);
					if (vertex[0] <= window_width - 1 && vertex[1] <= window_height - 1){
						if (vertex[0] >= 0 && vertex[1] >= 0){
							drawPoint(vertex[0], vertex[1], 1.0, 1.0, 1.0);
						}
					}
				}
				glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
			}
			else if (typeid(*toDraw) == typeid(Cube)){
				for (int i = 0; i < 24; i = i + 3){
					toRasterize.set(verticesC[i], verticesC[i + 1], verticesC[i + 2], 1);
					vertex = rasterizeVertex(toRasterize);
					if (vertex[0] <= window_width - 1 && vertex[1] <= window_height - 1){
						if (vertex[0] >= 0 && vertex[1] >= 0){
							drawPoint(vertex[0], vertex[1], 1.0, 1.0, 1.0);
						}
					}
				}
				glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
			}
		}
		if (scene == 2 || scene == 3 || scene == 4){
			bool zBuf = false;
			if (scene == 3 || scene == 4)
				zBuf = true;



			if (typeid(*toDraw) == typeid(OBJObject)){
				OBJObject *o = (OBJObject*)toDraw;
				std::vector<Vector3*>* vertices = o->getVertices();
				std::vector<Face*>* faces = o->getFaces();
				std::vector<Vector3*>* normals = o->getNormals();
				for (auto iterator = faces->begin(); iterator != faces->end(); iterator++){
					Vector3 *v1 = vertices->at((*iterator)->vertexIndices[0] - 1);
					Vector3 *v2 = vertices->at((*iterator)->vertexIndices[1] - 1);
					Vector3 *v3 = vertices->at((*iterator)->vertexIndices[2] - 1);
					
					Vector3 *n1 = normals->at((*iterator)->normalIndices[0] - 1);
					Vector3 *n2 = normals->at((*iterator)->normalIndices[1] - 1);
					Vector3 *n3 = normals->at((*iterator)->normalIndices[2] - 1);
					
					toRasterize.set((*v1)[0], (*v1)[1], (*v1)[2], 1);
					a = rasterizeVertex(toRasterize);
					toRasterize.set((*v2)[0], (*v2)[1], (*v2)[2], 1);
					b = rasterizeVertex(toRasterize);
					toRasterize.set((*v3)[0], (*v3)[1], (*v3)[2], 1);
					c = rasterizeVertex(toRasterize);
					
					
					toRasterize.set((*n1)[0], (*n1)[1], (*n1)[2], 1);
					an = toRasterize.toVector3();
					an = an.normalize();
					an.set(an[0] / 2.0 + 0.5, an[1] / 2.0 + 0.5, an[2] / 2.0 + 0.5);
					//an.print("\n");
					toRasterize.set((*n2)[0], (*n2)[1], (*n2)[2], 1);
					bn = toRasterize.toVector3();
					bn = bn.normalize();
					bn.set(bn[0] / 2.0 + 0.5, bn[1] / 2.0 + 0.5, bn[2] / 2.0 + 0.5);
					//bn.print("\n");
					toRasterize.set((*n3)[0], (*n3)[1], (*n3)[2], 1);
					cn = toRasterize.toVector3();
					cn = cn.normalize();
					cn.set(cn[0] / 2.0 + 0.5, cn[1] / 2.0 + 0.5, cn[2] / 2.0 + 0.5);
					//cn.print("\n");
					rasterizeTriangle(a, b, c, an, bn, cn, zBuf);
				}
				glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
			}

			else if (typeid(*toDraw) == typeid(House)){
				for (int i = 0; i < 60; i=i+3){
					toRasterize.set(vertices[indices[i] * 3], vertices[indices[i] * 3 + 1], vertices[indices[i] * 3 + 2], 1);
					a = rasterizeVertex(toRasterize);
					toRasterize.set(vertices[indices[i+1] * 3], vertices[indices[i+1] * 3 + 1], vertices[indices[i+1] * 3 + 2], 1);
					b = rasterizeVertex(toRasterize);
					toRasterize.set(vertices[indices[i + 2] * 3], vertices[indices[i + 2] * 3 + 1], vertices[indices[i + 2] * 3 + 2], 1);
					c = rasterizeVertex(toRasterize);

					
					an = a.normalize();
					an.set(an[0] / 2.0 + 0.5, an[1] / 2.0 + 0.5, an[2] / 2.0 + 0.5);
					bn = b.normalize();
					bn.set(bn[0] / 2.0 + 0.5, bn[1] / 2.0 + 0.5, bn[2] / 2.0 + 0.5);
					cn = c.normalize();
					cn.set(cn[0] / 2.0 + 0.5, cn[1] / 2.0 + 0.5, cn[2] / 2.0 + 0.5);

					rasterizeTriangle(a, b, c, an, bn, cn, zBuf);

				}
				glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
			}

			else if (typeid(*toDraw) == typeid(Cube)){
				
				for (int i = 0; i < 36; i = i + 3){
					toRasterize.set(verticesC[indicesC[i] * 3], verticesC[indicesC[i] * 3 + 1], verticesC[indicesC[i] * 3 + 2], 1);
					a = rasterizeVertex(toRasterize);
					toRasterize.set(verticesC[indicesC[i + 1] * 3], verticesC[indicesC[i + 1] * 3 + 1], verticesC[indicesC[i + 1] * 3 + 2], 1);
					b = rasterizeVertex(toRasterize);
					toRasterize.set(verticesC[indicesC[i + 2] * 3], verticesC[indicesC[i + 2] * 3 + 1], verticesC[indicesC[i + 2] * 3 + 2], 1);
					c = rasterizeVertex(toRasterize);

					toRasterize.set(normalsC[indicesC[i] * 3], normalsC[indicesC[i] * 3 + 1], normalsC[indicesC[i] * 3 + 2], 1);
					an = toRasterize.toVector3();
					an = an.normalize();
					an.set(an[0] / 2.0 + 0.5, an[1] / 2.0 + 0.5, an[2] / 2.0 + 0.5);

					toRasterize.set(normalsC[indicesC[i + 1] * 3], normalsC[indicesC[i + 1] * 3 + 1], normalsC[indicesC[i + 1] * 3 + 2], 1);
					bn = toRasterize.toVector3();
					bn = bn.normalize();
					bn.set(bn[0] / 2.0 + 0.5, bn[1] / 2.0 + 0.5, bn[2] / 2.0 + 0.5);
					
					toRasterize.set(normalsC[indicesC[i + 2] * 3], normalsC[indicesC[i + 2] * 3 + 1], normalsC[indicesC[i + 2] * 3 + 2], 1);
					cn = toRasterize.toVector3();
					cn = cn.normalize();
					cn.set(cn[0] / 2.0 + 0.5, cn[1] / 2.0 + 0.5, cn[2] / 2.0 + 0.5);
					
					rasterizeTriangle(a, b, c, an, bn , cn, zBuf);
					
				}
				glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);
			}

		}

	}
}

Vector3 Rasterizer::rasterizeVertex(Vector4 toRasterize){
	imSp = toDraw->toWorld * toRasterize;
	//imSp = rCamera->getInverseMatrix() * imSp;
	imSp = P * imSp;
	imSp = D * imSp;
	imSp = imSp.dehomogenize();
	//if (imSp[0] <= window_width - 1 && imSp[1] <= window_height - 1){
	//	if (imSp[0] >= 0 && imSp[1] >= 0){
			//drawPoint(imSp[0], imSp[1], 1.0, 1.0, 1.0);
	coords1.set(imSp[0], imSp[1], imSp[2]);
	return coords1;
		//}
	//}
	
}

void Rasterizer::setToDraw(Drawable *object){
	toDraw = object;
}

void Rasterizer::setDebug(int debug1){
	debug = debug1;
}

void Rasterizer::setScene(int scene1){
	scene = scene1;
}