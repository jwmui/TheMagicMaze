#include "Wall.h"


Wall::Wall(int valid, float x, float y, float z, int face)
{
    this->valid = valid; // if not valid, don't draw
    
    this->x = x;  // center of the cube??? subtract off halfsize, add halfsize to get its edge
    this->y = y;
    this->z = z;
    
    this->face = face;
    
    this->halfSize = 10;
    this->thickness = 1.0;
    this->halfSize1 = 10 + thickness;
}

void Wall::draw(){

    if(!valid) { return; }
    
    // glTranslatef() is already called from Maze::draw()
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    // Draw front (top) face:
    if (this->face == FRONT){
        glNormal3f(0.0, 0.0, 1.0);//front
        glVertex3f(-halfSize, halfSize, halfSize);
        glVertex3f(halfSize, halfSize, halfSize);
        glVertex3f(halfSize, -halfSize, halfSize);
        glVertex3f(-halfSize, -halfSize, halfSize);
        
        glNormal3f(0.0, 0.0, -1.0);//back
        glVertex3f(-halfSize, halfSize, halfSize1);
        glVertex3f(halfSize, halfSize, halfSize1);
        glVertex3f(halfSize, -halfSize, halfSize1);
        glVertex3f(-halfSize, -halfSize, halfSize1);
        
        glNormal3f(-1.0, 0.0, 0.0);//left
        glVertex3f(-halfSize, halfSize, halfSize);
        glVertex3f(-halfSize, halfSize, halfSize1);
        glVertex3f(-halfSize, -halfSize, halfSize1);
        glVertex3f(-halfSize, -halfSize, halfSize);
        
        glNormal3f(1.0, 0.0, 0.0);//right
        glVertex3f(halfSize, halfSize, halfSize);
        glVertex3f(halfSize, halfSize, halfSize1);
        glVertex3f(halfSize, -halfSize, halfSize1);
        glVertex3f(halfSize, -halfSize, halfSize);
        
        glNormal3f(0.0, 1.0, 0.0);//top
        glVertex3f(-halfSize, halfSize, halfSize);
        glVertex3f(-halfSize, halfSize, halfSize1);
        glVertex3f(halfSize, halfSize, halfSize1);
        glVertex3f(halfSize, halfSize, halfSize);
    }
    
    // Draw left side:
    else if (this->face == LEFT){
        glNormal3f(-1.0, 0.0, 0.0);//left
        glVertex3f(-halfSize, halfSize, halfSize);
        glVertex3f(-halfSize, halfSize, -halfSize);
        glVertex3f(-halfSize, -halfSize, -halfSize);
        glVertex3f(-halfSize, -halfSize, halfSize);
        
        glNormal3f(1.0, 0.0, 0.0);//right
        glVertex3f(-halfSize1, halfSize, halfSize);
        glVertex3f(-halfSize1, halfSize, -halfSize);
        glVertex3f(-halfSize1, -halfSize, -halfSize);
        glVertex3f(-halfSize1, -halfSize, halfSize);
        
        glNormal3f(0.0, 0.0, 1.0);//front
        glVertex3f(-halfSize, halfSize, halfSize);
        glVertex3f(-halfSize1, halfSize, halfSize);
        glVertex3f(-halfSize1, -halfSize, halfSize);
        glVertex3f(-halfSize, -halfSize, halfSize);
        
        glNormal3f(0.0, 0.0, -1.0);//back
        glVertex3f(-halfSize, halfSize, -halfSize);
        glVertex3f(-halfSize1, halfSize, -halfSize);
        glVertex3f(-halfSize1, -halfSize, -halfSize);
        glVertex3f(-halfSize, -halfSize, -halfSize);
        
        glNormal3f(0.0, 1.0, 0.0);//top
        glVertex3f(-halfSize, halfSize, halfSize);
        glVertex3f(-halfSize1, halfSize, halfSize);
        glVertex3f(-halfSize1, halfSize, -halfSize);
        glVertex3f(-halfSize, halfSize, -halfSize);
        
        
    }
    
    // Draw right side:
    else if (this->face == RIGHT){
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(halfSize, halfSize, halfSize);
        glVertex3f(halfSize, halfSize, -halfSize);
        glVertex3f(halfSize, -halfSize, -halfSize);
        glVertex3f(halfSize, -halfSize, halfSize);
        
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(halfSize1, halfSize, halfSize);
        glVertex3f(halfSize1, halfSize, -halfSize);
        glVertex3f(halfSize1, -halfSize, -halfSize);
        glVertex3f(halfSize1, -halfSize, halfSize);
        
        glNormal3f(0.0, 0.0, 1.0);//front
        glVertex3f(halfSize, halfSize, halfSize);
        glVertex3f(halfSize1, halfSize, halfSize);
        glVertex3f(halfSize1, -halfSize, halfSize);
        glVertex3f(halfSize, -halfSize, halfSize);
        
        glNormal3f(0.0, 0.0, -1.0);//back
        glVertex3f(halfSize, halfSize, -halfSize);
        glVertex3f(halfSize1, halfSize, -halfSize);
        glVertex3f(halfSize1, -halfSize, -halfSize);
        glVertex3f(halfSize, -halfSize, -halfSize);
        
        glNormal3f(0.0, 1.0, 0.0);//top
        glVertex3f(halfSize, halfSize, halfSize);
        glVertex3f(halfSize1, halfSize, halfSize);
        glVertex3f(halfSize1, halfSize, -halfSize);
        glVertex3f(halfSize, halfSize, -halfSize);
    }
    
    // Draw back (bottom) face:
    else if (this->face == BACK){
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-halfSize, halfSize, -halfSize);
        glVertex3f(halfSize, halfSize, -halfSize);
        glVertex3f(halfSize, -halfSize, -halfSize);
        glVertex3f(-halfSize, -halfSize, -halfSize);
        
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-halfSize, halfSize, -halfSize1);
        glVertex3f(halfSize, halfSize, -halfSize1);
        glVertex3f(halfSize, -halfSize, -halfSize1);
        glVertex3f(-halfSize, -halfSize, -halfSize1);
        
        glNormal3f(-1.0, 0.0, 0.0);//left
        glVertex3f(-halfSize, halfSize, -halfSize);
        glVertex3f(-halfSize, halfSize, -halfSize1);
        glVertex3f(-halfSize, -halfSize, -halfSize1);
        glVertex3f(-halfSize, -halfSize, -halfSize);
        
        glNormal3f(1.0, 0.0, 0.0);//right
        glVertex3f(halfSize, halfSize, -halfSize);
        glVertex3f(halfSize, halfSize, -halfSize1);
        glVertex3f(halfSize, -halfSize, -halfSize1);
        glVertex3f(halfSize, -halfSize, -halfSize);
        
        glNormal3f(0.0, 1.0, 0.0);//top
        glVertex3f(-halfSize, halfSize, -halfSize);
        glVertex3f(-halfSize, halfSize, -halfSize1);
        glVertex3f(halfSize, halfSize, -halfSize1);
        glVertex3f(halfSize, halfSize, -halfSize);
    }
    
    glEnd();
}

Wall::~Wall()
{
}
