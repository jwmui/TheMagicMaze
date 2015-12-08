#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "House.h"
#include "Sphere.h"
#include "OBJObject.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "SkyBox.h"

class Globals
{
    
public:
    
    static Camera *playerCamera;   // player's view -- key callbacks, no mouse controls
    static Camera *overheadCamera; // static overhead view -- mouse controls, no key callbacks

	static Sphere sphere;
    static Light dir;
	static Light spot;
	static Light point;
    static DrawData drawData;
    static UpdateData updateData;
	static SkyBox *skyBox;
    //Feel free to add more member variables as needed
    
};

#endif
