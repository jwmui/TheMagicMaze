#ifndef CSE167_Window_h
#define CSE167_Window_h
#include "Vector3.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    static int time, frame, timebase;
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void keyboardCallback(unsigned char, int, int);
	static void specialCallback(int, int, int);
	static void mouseCallback(int,int,int,int);
	static void motionCallback(int, int);
	static Vector3 mapping(int, int);
	static void mouseWheelCallback(int,int,int,int);
    
};

#endif

