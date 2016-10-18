#include <iostream>
#include <GLUT/glut.h>
#include <math.h>

using namespace std;
int second = 60;


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
    
    
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    if (--second == 0)
        second = 60;
    
    
    double x = cos(second * 6 * 3.14159 / 180.0);
    double y = sin(second * 6 * 3.14159 / 180.0);
    glVertex2d(0, 0);
    glVertex2d(x * 0.45, y * 0.45);
    glEnd();
    
	glFlush();
}

void timer(int arg) {
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
	glutMainLoop();	
	
	return 0;
}
