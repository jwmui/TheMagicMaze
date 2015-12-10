#pragma once
#include "GLee.h"
#include "Shader.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include "Matrix4.h"

#include "Vector4.h"
#include "Light.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Shadow
{
protected:

	glm::mat4 bias;

public:

	Shadow();
	~Shadow();
	void makeShadow(Light source);
	Camera shadowCam;
	glm::mat4 depthMVP;
	glm::mat4 biasDepth;

};