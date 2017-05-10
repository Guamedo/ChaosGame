#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include <GL/gl.h>
#include <array>
#include <sstream>
#include "GL/freeglut.h"


#include "Point.h"

using namespace std;

static const int window_width = 600;
static const int window_height = 600;


bool paint = false;
const unsigned int interval = 1000/60;
vector<Point> puntuak;
vector<Point> hasieraPuntuak;
Point lastPoint;
int iter = 0;

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = (GLfloat)(2.0f * 4*atan(1));

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
                (GLfloat)(x + (radius * cos(i *  twicePi / triangleAmount))),
                (GLfloat)(y + (radius * sin(i * twicePi / triangleAmount)))
        );
    }
    glEnd();
}

void print(int x, int y,int z, string s)
{
//set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x,y);
//get the length of the string to display
    int len = s.size();

//loop to display character by character
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
    }
};

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    for(unsigned int i = 0; i < puntuak.size(); i++){
        glColor3f(puntuak.at(i).col[0],puntuak.at(i).col[1],puntuak.at(i).col[2]);
        drawFilledCircle(puntuak.at(i).posX,puntuak.at(i).posY,2);
    }
    ostringstream oss;
    oss << "Iteracion: " << iter;
    glColor3f(1.0,1.0,1.0);
    print(5, window_height-17, 0, oss.str());
    glutSwapBuffers();
}

void enable2D(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int random_range(int min, int max){
    return min + (rand() % (max - min + 1));
}

void addPoint(){
    unsigned int r = (unsigned int)random_range(0,hasieraPuntuak.size()-1);
    switch (r){
        case 0:
            lastPoint = Point(abs(lastPoint.posX+hasieraPuntuak.at(r).posX)/2, abs(lastPoint.posY+hasieraPuntuak.at(r).posY)/2, {1.0,0.0,0.0});
            break;
        case 1:
            lastPoint = Point(abs(lastPoint.posX+hasieraPuntuak.at(r).posX)/2, abs(lastPoint.posY+hasieraPuntuak.at(r).posY)/2, {0.0,1.0,0.0});
            break;
        case 2:
            lastPoint = Point(abs(lastPoint.posX+hasieraPuntuak.at(r).posX)/2, abs(lastPoint.posY+hasieraPuntuak.at(r).posY)/2, {0.0,0.0,1.0});
            break;
        default:
            break;
    }
    puntuak.push_back(lastPoint);
}

void update(int value) {
    if(paint){
        addPoint();
        iter++;
    }
    glutTimerFunc(interval, update, 0);
    glutPostRedisplay();
}

void puntuakHasieratu(){
    hasieraPuntuak.push_back(Point(10,10,{1.0,1.0,1.0}));
    hasieraPuntuak.push_back(Point(590, 10,{1.0,1.0,1.0}));
    hasieraPuntuak.push_back(Point(290, 590,{1.0,1.0,1.0}));

    puntuak = hasieraPuntuak;
}

void kayboard(unsigned char key, int x, int y){
    switch (key){
        case 13:
            if(puntuak.size() >= 4) {
                paint = true;
            }
            break;
        case 27:
            exit(0);
        default:
            break;
    }
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(!paint){
            if(puntuak.size() == 4){
                puntuak.pop_back();
            }
            lastPoint = Point(x, window_height-y, {1.0,1.0,1.0});
            puntuak.push_back(lastPoint);
        }
    }
}

int main(int argc, char **argv) {

    srand((unsigned int)time(NULL));
    puntuakHasieratu();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Chaos Game");

    glutDisplayFunc(draw);
    glutKeyboardFunc(kayboard);
    glutMouseFunc(mouse);
    glutTimerFunc(interval, update, 0);
    enable2D(window_width, window_height);

    glutMainLoop();
    return 0;
}