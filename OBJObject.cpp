#include "OBJObject.h"
#include "limits.h"
#include <cmath>
#include <iostream>
//#include <windows.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <cmath>

Vector3 amb, dif, spec;
float shine;


#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)


OBJObject::OBJObject(std::string filename) : Drawable()
{
	float center = 1.0;
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
	this->name = filename;
	//this->colors = new std::vector<Vector3*>();
	if (filename == ("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/BunnyF14/bunny.obj")){
		center = 8.49859596231;
		
		amb.set(0.24725, 0.1995, 0.0745);
		dif.set(0.75164,	0.60648,	0.22648);
		spec.set(0.628281,	0.555802,	0.366065);
		shine = 0.4;
	}
		
	else if (filename == ("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/BearF14/bear.obj")){
		center = 1.15;
		amb.set(0.0,	0.0,	0.0);
		dif.set(0.5,	0.5,	0.0);
		spec.set(0.60,	0.60,	0.50);
		shine = 0.25;
	}
		
	else if (filename == ("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/DragonF14/dragon.obj")){
		center = 10.6463389637;
		amb.set(0.0215,	0.1745,	0.0215);
		dif.set(0.07568,	0.61424,	0.07568);
		spec.set(0.633,	0.727811,	0.633);
		shine = 0.6;
	}
		
	else
		center = 1.0;
    parse(filename, center);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    
    deleteVector(Vector3*, vertices);
    deleteVector(Vector3*, normals);
    deleteVector(Face*, faces);
}

void OBJObject::draw(DrawData& data)
{

	if (name == ("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/BunnyF14/bunny.obj")){
		amb.set(0.135,	0.2225,	0.1575);
		dif.set(0.54,	0.89,	0.63);
		spec.set(0.316228,	0.316228,	0.316228);
		shine = 0.5;
	}

	else if (name == ("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/BearF14/bear.obj")){
		amb.set(0.0, 0.0, 0.0);
		dif.set(0.5, 0.5, 0.0);
		spec.set(0.60, 0.60, 0.50);
		shine = 0.1;
	}

	else if (name == ("C:/Users/Jonathan/Desktop/CSE167-Spring-2015-Starter-Code-master/DragonF14/dragon.obj")){
		amb.set(0.25,	0.25,	0.25);
		dif.set(0.4,	0.4,	0.4);
		spec.set(0.774597,	0.774597,	0.774597);
		shine = 1.0;
	}
	material.apply(amb, dif, spec, shine);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
    
    //      glNorm(normals->at(face.normalIndices[0]))
    //      glVert(vertices->at(face.vertexIndices[0]))
    //      Etc.
    //
	for (auto iterator = faces->begin(); iterator != faces->end(); iterator++){
		

		Vector3 *v1 = vertices->at((*iterator)->vertexIndices[0] - 1);
		Vector3 *v2 = vertices->at((*iterator)->vertexIndices[1] - 1);
		Vector3 *v3 = vertices->at((*iterator)->vertexIndices[2] - 1);

		Vector3 *n1 = normals->at((*iterator)->normalIndices[0] - 1);
		Vector3 *n2 = normals->at((*iterator)->normalIndices[1] - 1);
		Vector3 *n3 = normals->at((*iterator)->normalIndices[2] - 1);

		/*if (!colors->empty()){
			Vector3 *c1 = colors->at((*iterator)->vertexIndices[0] - 1);
			Vector3 *c2 = colors->at((*iterator)->vertexIndices[1] - 1);
			Vector3 *c3 = colors->at((*iterator)->vertexIndices[2] - 1);


			glColor3f((*c1)[0], (*c1)[1], (*c1)[2]);
			glColor3f((*c2)[0], (*c2)[1], (*c2)[2]);
			glColor3f((*c3)[0], (*c3)[1], (*c3)[2]);
		}*/
		
		glNormal3f((*n1)[0], (*n1)[1], (*n1)[2]);
		glNormal3f((*n2)[0], (*n2)[1], (*n2)[2]);
		glNormal3f((*n3)[0], (*n3)[1], (*n3)[2]);

		glVertex3f((*v1)[0], (*v1)[1], (*v1)[2]);
		glVertex3f((*v2)[0], (*v2)[1], (*v2)[2]);
		glVertex3f((*v3)[0], (*v3)[1], (*v3)[2]);
		
	}
    
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data)
{
    //
}

std::vector<Vector3*>* OBJObject::getVertices(){
	return vertices;
}

std::vector<Vector3*>* OBJObject::getNormals(){
	return normals;
}

std::vector<Face*>* OBJObject::getFaces(){
	return faces;
}

void OBJObject::parse(std::string& filename, float scale)
{
	
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> tokens;
	std::vector<std::string> tokens1;
	std::string token;

	int lineNum = 0;
	this->maxX = INT_MIN+0.0;
	this->maxY = INT_MIN+0.0;
	this->maxZ = INT_MIN+0.0;
	this->minX = INT_MAX+0.0;
	this->minY = INT_MAX+0.0;
	this->minZ = INT_MAX+0.0;

	std::cout << "Starting parse..." << std::endl;

	//While all your lines are belong to us
	while (std::getline(infile, line))
	{
		//Progress
		if (++lineNum % 10000 == 0)
			std::cout << "At line " << lineNum << std::endl;

		//Split a line into tokens by delimiting it on spaces
		//"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
		tokens.clear();
		tokens = split(line, ' ', tokens);
		//If first token is a v then it gots to be a vertex
		if (!tokens.empty()){
			if (tokens.at(0).compare("v") == 0)
			{
				//Parse the vertex line
				if (tokens.size() == 4){
					float x = std::stof(tokens.at(1));
					float y = std::stof(tokens.at(2));
					float z = std::stof(tokens.at(3));

                    this->maxX = std::max(x, this->maxX);
                    this->maxY = std::max(y, this->maxY);
                    this->maxZ = std::max(z, this->maxZ);

                    this->minX = std::min(x, this->minX);
                    this->minY = std::min(y, this->minY);
                    this->minZ = std::min(z, this->minZ);

					vertices->push_back(new Vector3(x, y, z));
				}
				else if (tokens.size() == 7){
					float x = std::stof(tokens.at(1));
					float y = std::stof(tokens.at(2));
					float z = std::stof(tokens.at(3));
					float r = std::stof(tokens.at(4));
					float g = std::stof(tokens.at(5));
					float b = std::stof(tokens.at(6));
					//colors->push_back(new Vector3(r, g, b));
					vertices->push_back(new Vector3(x, y, z));
				}
			}
			


			else if (tokens.at(0).compare("vn") == 0)
			{
				//Parse the normal line
					float x = std::stof(tokens.at(1));
					float y = std::stof(tokens.at(2));
					float z = std::stof(tokens.at(3));

					normals->push_back(new Vector3(x, y, z));
				
			}
			else if (tokens.at(0).compare("f") == 0)
			{
					Face *face = new Face;
					//Parse the face line
					tokens1.clear();
					tokens1 = split((tokens.at(1)), '/', tokens1);
					face->vertexIndices[0] = std::stoi(tokens1.at(0));
					face->normalIndices[0] = std::stoi(tokens1.at(2));

					tokens1.clear();
					tokens1 = split((tokens.at(2)), '/', tokens1);
					face->vertexIndices[1] = std::stoi(tokens1.at(0));
					face->normalIndices[1] = std::stoi(tokens1.at(2));

					tokens1.clear();
					tokens1 = split((tokens.at(3)), '/', tokens1);
					face->vertexIndices[2] = std::stoi(tokens1.at(0));
					face->normalIndices[2] = std::stoi(tokens1.at(2));

					faces->push_back(face);
				
			}
			else if (tokens.at(0).compare("How does I are C++?!?!!") == 0)
			{
				//Parse as appropriate
				//There are more line types than just the above listed
				//See the Wavefront Object format specification for details

			}
			
		}
		
	}
	center(std::abs(scale));
	std::cout << "Done parsing." << std::endl;
}
    


//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}



std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void OBJObject::center(float scale){
	float halfX = (this->minX + this->maxX) / 2.0;
	float halfY = (this->minY + this->maxY) / 2.0;
	float halfZ = (this->minZ + this->maxZ) / 2.0;
	//printf("half Y %\n", halfY);
	for (auto iterator = vertices->begin(); iterator != vertices->end(); iterator++){
		Vector3 *v = (*iterator);
		(*v)[0] -= halfX;
		(*v)[1] -= halfY;
		(*v)[2] -= halfZ;
		(*v)[0] = (*v)[0] * (scale);
		(*v)[1] = (*v)[1] * (scale);
		(*v)[2] = (*v)[2] * (scale);

	}
	halfX = 0;
	halfY = 0;
	halfZ = 0;
}
