#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

using namespace std;

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.9, -0.8);
    glVertex2d( 0.9, -0.8);
    glVertex2d( 0.0,  0.8);
    glEnd();
    
	glFlush();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMainLoop();	
	
	return 0;
}
