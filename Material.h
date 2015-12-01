#ifndef CSE167_Material_h
#define CSE167_Material_h

#include <iostream>
#include "Color.h"
#include "Vector3.h"

class Material
{
    
public:
    
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    Color emissionColor;
    
    float shininess;
    
 
    
public:
    
    Material(void);
    ~Material(void);
    
	virtual void apply(Vector3, Vector3, Vector3, float);
    
};

#endif
