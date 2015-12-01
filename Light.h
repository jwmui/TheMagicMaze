#ifndef CSE167_Light_h
#define CSE167_Light_h

#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"
#include <vector>
#include "Vector3.h"
#include "Drawable.h"
class Light : public Drawable
{
    
protected:
    
    int bindID = -1;
    
public:
    
    Vector4 position;
	float spotCutoff;
	float *spotDirection;
	float exponent;
    float *ambientColor;
    float *diffuseColor;
    float *specularColor;
    
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    
public:
    
    Light();
    virtual ~Light(void);
    
    void bind(int);
    void unbind(void);
	void draw(DrawData&);
};

#endif
