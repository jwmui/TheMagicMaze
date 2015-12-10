#include "Plant.h"
#include "Matrix4.h"
#include <math.h>

/*  At least 4 language variables (X, F, +, -), and parameters (length of F, theta of + and -).
 *  To make it 3D you can also add another axis for rotation(typical variables are & and ^).
 *  At least 3 trees that demonstrate different rules.
 *  Pseudorandom execution will make your trees look more varied and pretty.
 */

/* Example: Fractal plant
 * variables: X F
 * constants: + - []
 * start: X
 * rules: (X → F−[[X]+X]+F[+FX]−X), (F → FF)
 *        (X → F−[[X]&X]+F[^FX]−X), (F → FF)
 * angle: 25 degrees
 
 * try rotating about x with & and ^
 */
Plant::Plant(float x, float y, float z, int n)
{
    /*this->x = x;
    this->y = y;
    this->z = z;*/
    this->currPosition.set(x,y,z);
    this->currDirection.set(0.1,1.0,0.1);
    
    this->n = n;
    ROTATION = 25; // degrees
    
    this->branchLength = 0.2;
    Matrix4 rotateZ, rotateX;
    
    s = "X";
    for(int i = 0; i < n; i++) {
        std::string tempS = "";
        tempS.swap(s);
        //s.erase();
        for(int j = 0; j < tempS.length(); j++) {
            if(tempS[j] == 'X') {
                s.append("F-[[X]+X]+F[+FX]-X");
                //s.append("F−[[X]&X]+F[^FX]−X");
            }
            else if(tempS[j] == 'F') {
                s.append("FF");
            }
            else {
                s.push_back(tempS[j]);
            }
        }
        //std::cout << s << "\n\n\n";  // tested
    }
    
    
    // try with hardcoding a string first
    // store them in drawVector
    // this might be a different one?
    for(int i = 0; i < s.length(); i++) {
        switch(s.at(i)) {
            case 'X':
                break;
            case 'F':
                drawVector.push_back(currPosition);
                currPosition = currPosition +currDirection.scale(branchLength);
                drawVector.push_back(currPosition);
                //std::cout <<"F";
                break;
            case '[':
                prevStack.push(std::make_pair(currDirection, currPosition));
                //std::cout <<"[";
                break;
            case ']':
                currDirection = prevStack.top().first;
                currPosition = prevStack.top().second;
                prevStack.pop();
                //std::cout <<"]";
                break;
            case '-':
                rotateZ.makeRotateZ(-ROTATION * M_PI / 180);  // radians
                currDirection = rotateZ.multiply(currDirection);
                //std::cout <<"-";
                break;
            case '+':
                rotateZ.makeRotateZ(ROTATION * M_PI / 180); // radians
                currDirection = rotateZ.multiply(currDirection);
                //std::cout <<"+";
                break;
            /*case '&':
                rotateX.makeRotateY(-ROTATION/2 * M_PI / 180);  // radians
                currDirection = rotateX.multiply(currDirection);
                //std::cout <<"-";
                break;
            case '^':
                rotateX.makeRotateY(ROTATION/2 * M_PI / 180); // radians
                currDirection = rotateX.multiply(currDirection);
                //std::cout <<"+";
                break;*/

        }
    }
}

void Plant::draw(){
    glBegin(GL_LINES);
    glColor3f(0.15, 0.51, 0.0);
    for(std::vector<Vector3>::iterator it = drawVector.begin(); it != drawVector.end(); ++it) {
        /* std::cout << *it; ... */
        Vector3 v = *it;
        glVertex3f(v[0], v[1], v[2]);
        //v.print("");
    }
    
    glEnd();
}

Plant::~Plant()
{
}