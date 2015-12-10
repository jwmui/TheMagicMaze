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
Plant::Plant(float x, float y, float z, int n,
             float lengthF, float plusAngle, float minusAngle,
             float andAngle, float caratAngle,
             float backslashAngle, float forwardslashAngle)
{
    /*this->x = x;
    this->y = y;
    this->z = z;*/
    this->currPosition.set(x,y,z);
    this->currDirection.set(0.1,1.0,0.1);
    
    this->n = n;
    
    this->lengthF = lengthF;
    this->plusAngle = plusAngle;
    this->minusAngle = minusAngle;
    this->andAngle = andAngle;
    this->caratAngle = caratAngle;
    this->backslashAngle = backslashAngle;
    this->forwardslashAngle = forwardslashAngle;
    
    Matrix4 rotateX, rotateY, rotateZ;
    
    s = "X";
    for(int i = 0; i < n; i++) {
        std::string tempS = "";
        tempS.swap(s);
        //s.erase();
        for(int j = 0; j < tempS.length(); j++) {
            if(tempS[j] == 'X') {
                int randnum = rand()%6;
                //std::cout << randnum << "\n";
                switch(randnum) {
                    case 0: s.append("F-[[X]+X]+F[+FX]-X"); break;
                    case 1: s.append("F^[[X]&X]&F[&FX]^X"); break;
                    case 2: s.append("F/[[X]\\X]\\F[\\FX]/X"); break;
                    case 3: s.append("F+[[X]-X]-F[-FX]+X"); break;
                    case 4: s.append("F&[[X]^X]^F[^FX]&X"); break;
                    case 5: s.append("F\\[[X]/X]/F[/FX]\\X"); break;
                }
                //s.append("F−[[X]&X]+F[^FX]−X");
            }
            else if(tempS[j] == 'F') {
                
                int randnum = rand()%2;
                //std::cout << randnum << "\n";
                switch(randnum) {
                    case 0: s.append("F"); break;
                    case 1: s.append("FF"); break;
                }
                // s.append("FF");
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
                currPosition = currPosition +currDirection.scale(lengthF);
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
                rotateZ.makeRotateZ(-minusAngle * M_PI / 180);  // radians
                currDirection = rotateZ.multiply(currDirection);
                //std::cout <<"-";
                break;
            case '+':
                rotateZ.makeRotateZ(plusAngle * M_PI / 180); // radians
                currDirection = rotateZ.multiply(currDirection);
                //std::cout <<"+";
                break;
            case '&':
                rotateY.makeRotateY(-andAngle * M_PI / 180);  // radians
                currDirection = rotateX.multiply(currDirection);
                break;
            case '^':
                rotateY.makeRotateY(caratAngle * M_PI / 180); // radians
                currDirection = rotateX.multiply(currDirection);
                break;
            case '\\':
                rotateX.makeRotateX(-backslashAngle * M_PI / 180);  // radians
                currDirection = rotateX.multiply(currDirection);
                break;
            case '/':
                rotateX.makeRotateX(forwardslashAngle * M_PI / 180); // radians
                currDirection = rotateX.multiply(currDirection);
                break;

        }
    }
}

void Plant::draw(){
    glLineWidth(1.5);
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