#include "Globals.h"

Camera* Globals::playerCamera = new Camera();
Camera* Globals::overheadCamera = new Camera();

Sphere Globals::sphere(5, 100, 100);

Light Globals::dir;
//Light Globals::spot;
//Light Globals::point;

SkyBox* Globals::skyBox = new SkyBox(1000.0);

DrawData Globals::drawData;
UpdateData Globals::updateData;

