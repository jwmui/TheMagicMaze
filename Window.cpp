#include <iostream>
#include "Flag.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Light.h"
#include "Rasterizer.h"
#include <math.h>
#include <vector>
#include "SkyBox.h"
#include "BezierCurve.h"
#include "Maze.h"
#include <time.h>
#include "Player.h"

#define PI_OVER_2 1.57079

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
int spinDirection = 1;
//Drawable *current = &Globals::sphere;
float angle = 0;
float oldX, oldY, oldZ;
int debugSet = 0;
Vector3 coords;
Vector3 e, d, up;
//Rasterizer object(current, debugSet);
int renderMode = 0;
int part = 1;
int Window::time, Window::frame=0, Window::timebase=0;
float fps;
int lastX;
int lastY;
bool leftB;
bool rightB;
bool spotB, dirB, poiB;
Vector3 lastPoint, curPoint, v, direction, rotAxis;
//Drawable *curLight = current;
Vector3 origin(0.0, 0.0, 0.0);
Vector4 toChange;
BezierCurve *curve1, *curve2, *curve3, *curve4, *curveV, *curveH;
std::vector<Vector3> cPts;
std::vector<BezierCurve*> curvesV;
std::vector<BezierCurve*> curvesH;
Maze maze(time(NULL));
Player *player = new Player();
Vector3 oldE, oldD;
bool overhead = false;

void Window::initialize(void)
{	
	//Setup the directional light
	Vector4 lightPos(-5.0, 5.0, 10.0, 0.0);
	Globals::dir.position = lightPos;
	Globals::dir.spotCutoff = 180.0;
	Globals::dir.spotDirection = new float[3]{0.0, 0.0, -1.0};
	Globals::dir.exponent = 0.0;
	Globals::dir.quadraticAttenuation = 0.02;
	//Setup the point light
	Vector4 lightPos1(5.0, 5.0, 10.0, 1.0);
	Globals::point.position = lightPos1;
	Globals::point.spotCutoff = 180.0;
	Globals::point.spotDirection = new float[3]{0.0, 0.0, -1.0};
	Globals::point.exponent = 0.0;
	Globals::point.quadraticAttenuation = 0.02;
	//Setup the spot light
	Vector4 lightPos2(0.0, -5.0, 10.0, 1.0);
	Vector3 direction;
	Vector3 source;
	source.set(0.0, -5.0, 10.0);
	direction = origin - source;
	float mag = direction.magnitude();
	Globals::spot.position = lightPos2;
	Globals::spot.spotCutoff = 30.0;
	Globals::spot.spotDirection = new float[3]{direction[0], direction[1], direction[2]};
	Globals::spot.exponent = 2.0;
	Globals::spot.quadraticAttenuation = 0.02;
	coords.set(0, 0, 30);
	player->move(coords);
	oldE = Globals::camera->e;
	oldD = Globals::camera->d;
	//(*current).toWorld.identity();

}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
		//Globals::cube.spin(0.0005 * spinDirection);
    

	//(*current).update(Globals::updateData);

	//fps
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		printf("FPS:%4.2f\n",
			frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
    //Call the display routine to draw the cube
    displayCallback();

}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
		width = w;                                                       //Set the window width
		height = h;                                                      //Set the window height
		glViewport(0, 0, w, h);                                          //Set new viewport size
		glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
		glLoadIdentity();                                                //Clear the projection matrix by loading the identity
		gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
		//object.reshape(w, h);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera->getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::dir.bind(0);
	Globals::point.bind(1);
	Globals::spot.bind(2);

	//object.draw(renderMode);
	Globals::dir.draw(Globals::drawData);
	Globals::point.draw(Globals::drawData);
	Globals::spot.draw(Globals::drawData);
    
	//(*current).draw(Globals::drawData);


	/*glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-50, -10, -50);
	glVertex3f(50, -10, -50);
	glVertex3f(50, -10, 50);
	glVertex3f(-50, -10, 50);
	glEnd();*/
	//glDisable(GL_LIGHTING);
    maze.draw();
    player->draw();
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


void Window::keyboardCallback(unsigned char key, int x, int y)
{
	Matrix4 transform;
	Matrix4 temp;
	int x1, y1;
	Vector3 down;
	down.set(0, -1, 0);
	switch (key) {
		case 'w':
			direction = Globals::camera->d - Globals::camera->e;
			direction.set(direction[0], 0, direction[2]);
			//direction.normalize();
			Globals::camera->e = Globals::camera->e + (direction * .01).normalize();
			Globals::camera->d = Globals::camera->d + (direction * .01).normalize();
			Globals::camera->update();
			if (!overhead){
                maze.doCollisionDetection(Globals::camera->e, player);
				player->move(Globals::camera->e);  // TODO check collision detection, also don't move camera?
				oldE = Globals::camera->e;
				oldD = Globals::camera->d;
			}
			break;

		case 'a':
			direction = Globals::camera->d - Globals::camera->e;
			direction.set(direction[0], 0, direction[2]);
			direction = direction.cross(down);
			//direction.normalize();
			Globals::camera->e = Globals::camera->e + (direction * .01).normalize();
			Globals::camera->d = Globals::camera->d + (direction * .01).normalize();
			Globals::camera->update();
			if (!overhead){
                maze.doCollisionDetection(Globals::camera->e, player);
				player->move(Globals::camera->e);  // TODO check collision detection
				oldE = Globals::camera->e;
				oldD = Globals::camera->d;
			}
			break;

		case 's':
			direction = Globals::camera->d - Globals::camera->e;
			direction.set(direction[0], 0, direction[2]);
			//direction.normalize();
			Globals::camera->e = Globals::camera->e + (direction * -.01).normalize();
			Globals::camera->d = Globals::camera->d + (direction * -.01).normalize();
			Globals::camera->update();
			if (!overhead){
                maze.doCollisionDetection(Globals::camera->e, player);
				player->move(Globals::camera->e);  // TODO check collision detection
				oldE = Globals::camera->e;
				oldD = Globals::camera->d;
			}
			break;
		
		case 'd':
			direction = Globals::camera->d - Globals::camera->e;
			direction.set(direction[0], 0, direction[2]);
			direction = down.cross(direction);
			//direction.normalize();
			Globals::camera->e = Globals::camera->e + (direction * .01).normalize();
			Globals::camera->d = Globals::camera->d + (direction * .01).normalize();
			Globals::camera->update();
			if (!overhead){
                maze.doCollisionDetection(Globals::camera->e, player);
				player->move(Globals::camera->e);  // TODO check collision detection
				oldE = Globals::camera->e;
				oldD = Globals::camera->d;
			}
			break;

		case 'b':
			player->togDebug();
            maze.togDebug();
			break;

		case 'r':
			initialize();
			break;

		case'1':
			 //curLight = &Globals::dir;
			 dirB = true;
			 spotB = false;
			 poiB = false;
			break;
		case'2':
			// curLight = &Globals::point;
			 dirB = false;
			 spotB = false;
			 poiB = true;
			break;
		case'3':
			// curLight = &Globals::spot;
			 dirB = false;
			 spotB = true;
			 poiB = false;
			break;
		case'0':
			//curLight = current;
			dirB = false;
			spotB = false;
			poiB = false;
			break;
	}
	//coords.print("Coordinates");

}

void Window::specialCallback(int key, int x, int y){
	switch (key){
		case GLUT_KEY_F1:
			//cube
			//current = &Globals::sphere;
			//object.setToDraw(current);
			e.set(oldE[0], oldE[1], oldE[2]);
			d.set(oldD[0], oldD[1], oldD[2]);
			up.set(0.0, 1.0, 0.0);
			Globals::camera->set(e, d, up);
			//glEnable(GL_LIGHTING);
			overhead = false;
			break;
		case GLUT_KEY_F2:
			//e = 0, 24.14, 24.14 d = 0,0,0 up = 0, 1, 0
			//current = &Globals::house;
			//object.setToDraw(current);
			//glDisable(GL_LIGHTING);
			e.set(50, 200, -50);
			d.set(50, 0, -50);
			up.set(0, 1.0, 0);
			Globals::camera->set(e,d,up);
			overhead = true;
			break;
		case GLUT_KEY_F3:
			//e = -28.33, 11.66, 23.33 d = -5, 0, 0 up = 0, 1, 0.5
			//current = &Globals::house;
			//object.setToDraw(current);
			//glDisable(GL_LIGHTING);
			e.set(-28.33, 11.66, 23.33);
			d.set(-5, 0, 0);
			up.set(0, 1, 0.5);
			Globals::camera->set(e, d, up);
			
			break;
		case GLUT_KEY_F4:
			//bunny
			e.set(3.0, 0.0, 20.0);
			d.set(0.0, 0.0, 0.0);
			up.set(0.0, 1.0, 0.0);
			Globals::camera->set(e, d, up);
			//current = &Globals::bunny;
			//object.setToDraw(current);
			//glEnable(GL_LIGHTING);

			break;
		case GLUT_KEY_F5:
			//bear
			e.set(3.0, 0.0, 20.0);
			d.set(0.0, 0.0, 0.0);
			up.set(0.0, 1.0, 0.0);
			Globals::camera->set(e, d, up);
			//current = &Globals::bear;
			//object.setToDraw(current);
			//glEnable(GL_LIGHTING);

			break;
		case GLUT_KEY_F6:
			//dragon
			e.set(3.0, 0.0, 20.0);
			d.set(0.0, 0.0, 0.0);
			up.set(0.0, 1.0, 0.0);
			Globals::camera->set(e, d, up);
			//current = &Globals::dragon;
			//object.setToDraw(current);
			//
			
			//glEnable(GL_LIGHTING);

			break;

	}
}

//TODO: Mouse callbacks!
void Window::mouseCallback(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		leftB = true;
		lastPoint = mapping(x, y);
		glMatrixMode(GL_MODELVIEW);
		printf("press L\n");
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		rightB = true;
		lastPoint = mapping(x, y);
		glMatrixMode(GL_MODELVIEW);
		printf("press L\n");
	}
	if (state == GLUT_UP){
		leftB = false;
		rightB = false;
	}
	
}
//TODO: Mouse Motion callbacks!
void Window::motionCallback(int x, int y){
	Matrix4 transform;
	float pixel_diff;
	float rot_angle, zoom_factor;
	
	if(leftB){
		curPoint = mapping(x, y);
		direction = curPoint - lastPoint;
		Vector4 lookAt = Globals::camera->d.toVector4(1) - Globals::camera->e.toVector4(1);
		float velocity = direction.magnitude();
		if (velocity > 0.0001){


			if (!dirB && !poiB && !spotB){
				rotAxis = lastPoint.cross(curPoint);
				rot_angle = lastPoint.angle(curPoint);
				//rotAxis = rotAxis.normalize();
				transform.makeRotateArbitrary(rotAxis, rot_angle);
				lookAt = transform * lookAt;
				Globals::camera->d = lookAt.toVector3() + Globals::camera->e;
				Globals::camera->update();
			}
			if (dirB){
				rotAxis = lastPoint.cross(curPoint);
				rot_angle = lastPoint.angle(curPoint);
				transform.makeRotateArbitrary(rotAxis, rot_angle);
				//transform.makeTranslate(direction * 2);
				Globals::dir.toWorld = transform * Globals::dir.toWorld;
				Vector4 lightPos(Globals::dir.toWorld.get(3, 0), Globals::dir.toWorld.get(3, 1), Globals::dir.toWorld.get(3, 2), 0.0);
				Globals::dir.position = lightPos;
			}
			if (poiB){
				rotAxis = lastPoint.cross(curPoint);
				rot_angle = lastPoint.angle(curPoint);
				transform.makeRotateArbitrary(rotAxis, rot_angle);
				//transform.makeTranslate(direction * 2);
				Globals::point.toWorld = transform * Globals::point.toWorld;
				Vector4 lightPos(Globals::point.toWorld.get(3, 0), Globals::point.toWorld.get(3, 1), Globals::point.toWorld.get(3, 2), 1.0);
				Globals::point.position = lightPos;
			}
			if (spotB){
				rotAxis = lastPoint.cross(curPoint);
				rot_angle = lastPoint.angle(curPoint);
				transform.makeRotateArbitrary(rotAxis, rot_angle);
				//transform.makeTranslate(direction * 2);
				Globals::spot.toWorld = transform * Globals::spot.toWorld;
				Vector4 lightPos(Globals::spot.toWorld.get(3, 0), Globals::spot.toWorld.get(3, 1), Globals::spot.toWorld.get(3, 2), 1.0);
				Globals::spot.position = lightPos;
				Vector3 direction = origin- lightPos.toVector3();
				Globals::spot.spotDirection = new float[3]{direction[0], direction[1], direction[2]};

			}

		}
		lastPoint = curPoint;
	}
	if (rightB){
		if (!dirB && !poiB && !spotB){
			curPoint = mapping(x, y);
			direction = curPoint - lastPoint;
			direction[2] = 0;
			transform.makeTranslate(direction * 2);
			toChange = transform * Globals::camera->e.toVector4(1);
			Globals::camera->e = toChange.toVector3();
			toChange = transform * Globals::camera->d.toVector4(1);
			Globals::camera->d = toChange.toVector3();
			Globals::camera->update();
			//(*current).toWorld = transform * (*current).toWorld;
			//coords.set((*current).toWorld.get(3, 0), (*current).toWorld.get(3, 1), (*current).toWorld.get(3, 2));
			//coords.print("Coordinates");
			lastPoint = curPoint;
		}
		if (spotB){
			curPoint = mapping(x, y);
			direction = curPoint - lastPoint;
			if (direction[0] > 0 && abs(direction[1])  == 0){
				Globals::spot.exponent = Globals::spot.exponent + .5;
			}
			else if (direction[0] < 0 && abs(direction[1]) == 0){
				if (Globals::spot.exponent > 0)
				Globals::spot.exponent = Globals::spot.exponent - .5;
			}
			if (direction[1] > 0 && abs(direction[0]) == 0){
				if (Globals::spot.spotCutoff < 90 )
					Globals::spot.spotCutoff++;
			}
			else if (direction[1] < 0 && abs(direction[0]) == 0){
				if (Globals::spot.spotCutoff > 0 )
					Globals::spot.spotCutoff--;
			}
			lastPoint = curPoint;
		}
	}
	
}

Vector3 Window::mapping(int x, int y){
	float d;
	v.set(((2.0*x - width) / width), ((height - 2.0*y) / height), 0.0);
	d = v.magnitude();
	d = (d < 1.0) ? d : 1.0;
	v[2] = sqrtf(1.001 - d*d);
	v = v.normalize();
	return v;
}

void Window::mouseWheelCallback(int wheel, int direction, int x, int y){
	Matrix4 transform;
	Matrix4 temp;
	if (!dirB && !poiB && !spotB){
		if (direction == -1){
			Vector3 direction;
			direction = Globals::camera->d - Globals::camera->e;
			direction.normalize();
			//transform.makeTranslate(0, 0, -0.1);

			//toChange = transform * Globals::camera->e.toVector4(1);
			Globals::camera->e = Globals::camera->e + (direction * .1);
			//toChange = transform * Globals::camera->d.toVector4(1);
			Globals::camera->d = Globals::camera->d + (direction * .1);
			Globals::camera->update();

		}
		if (direction == 1){

			Vector3 direction;
			direction = Globals::camera->d - Globals::camera->e;
			direction.normalize();
			//transform.makeTranslate(0, 0, -0.1);

			//toChange = transform * Globals::camera->e.toVector4(1);
			Globals::camera->e = Globals::camera->e - (direction * .1);
			toChange = transform * Globals::camera->d.toVector4(1);
			Globals::camera->d = Globals::camera->d - (direction * .1);
			Globals::camera->update();
		}
	}
	if (poiB){
		if (direction == -1){
			transform.makeTranslate(0, 0, -0.1);
			Globals::point.toWorld = transform * Globals::point.toWorld;
			Vector4 lightPos(Globals::point.toWorld.get(3, 0), Globals::point.toWorld.get(3, 1), Globals::point.toWorld.get(3, 2), 1.0);
			Globals::point.position = lightPos;
		}
		if (direction == 1){
			transform.makeTranslate(0, 0, 0.1);
			Globals::point.toWorld = transform * Globals::point.toWorld;
			Vector4 lightPos(Globals::point.toWorld.get(3, 0), Globals::point.toWorld.get(3, 1), Globals::point.toWorld.get(3, 2), 1.0);
			Globals::point.position = lightPos;
		}
	}
	if (spotB){
		if (direction == -1){
			transform.makeTranslate(0, 0, -1.0);
			Globals::spot.toWorld = transform * Globals::spot.toWorld;
			Vector4 lightPos(Globals::spot.toWorld.get(3, 0), Globals::spot.toWorld.get(3, 1), Globals::spot.toWorld.get(3, 2), 1.0);
			Globals::spot.position = lightPos;
		}
		if (direction == 1){
			transform.makeTranslate(0, 0, 1.0);
			Globals::spot.toWorld = transform * Globals::spot.toWorld;
			Vector4 lightPos(Globals::spot.toWorld.get(3, 0), Globals::spot.toWorld.get(3, 1), Globals::spot.toWorld.get(3, 2), 1.0);
			Globals::spot.position = lightPos;
		}

	}

}