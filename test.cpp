#include <iostream>
#include <GLUT/glut.h>
#include <math.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>

using namespace std;

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    
    for (int i = 0; i < 360; i++) {
        double x = cos(i * 3.14159 / 180.0);
        double y = sin(i * 3.14159 / 180.0);
        glVertex2d(x * 0.6, y * 0.6);
    }
    glEnd();
    
    glBegin(GL_LINES);
    
    for (int i = 0; i < 12; i++) {
        double x = cos(i * 30 * 3.14159 / 180.0);
        double y = sin(i * 30 * 3.14159 / 180.0);
        glVertex2d(x * 0.55, y * 0.55);
        glVertex2d(x * 0.45, y * 0.45);
    }
    glEnd();
    
	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMainLoop();	
	€‹›
	return 0;
}
