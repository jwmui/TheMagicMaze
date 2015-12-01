#include "Material.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Material::Material()
{
    //Material setup goes hurr
    ambientColor = Color::ambientMaterialDefault();
    diffuseColor = Color::diffuseMaterialDefault();
    specularColor = Color::specularMaterialDefault();
    emissionColor = Color::emissionMaterialDefault();
    shininess = 10.0;
    
   
}

Material::~Material()
{
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(Vector3 amb, Vector3 dif, Vector3 spec, float shine)
{
    //Set the material properties for ambient, diffuse, specular, emission, and shininess
    //Hint: Lookup how glMaterialfv works
	
	float mat[4];
	mat[0] = amb[0];
	mat[1] = amb[1];
	mat[2] = amb[2];
	mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	mat[0] = dif[0];
	mat[1] = dif[1];
	mat[2] = dif[2];
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = spec[0];
	mat[1] =spec[1];
	mat[2] = spec[2];
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128);
}



   
