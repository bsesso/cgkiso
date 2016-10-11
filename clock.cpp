#include <iostream>
#include <GLUT/glut.h>
#include <math.h>
#include <ctime>

using namespace std;
int second = 0;
int minute = 0;
int hour = 0;


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
    

    // 秒針
    glPushMatrix();
    glColor3d(1.0, 0.0, 0.0);
    glRotated(-(second * 6), 0, 0, 1);

    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(0, 0.45);
    glEnd();

    glPopMatrix();

    // 分針
    glPushMatrix();
    glColor3d(1.0, 0.0, 1.0);
    glRotated(-(minute * 6 + second * 0.1), 0, 0, 1);

    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(0, 0.45);
    glEnd();
    
    glPopMatrix();

    // 時針
    glPushMatrix();
    glColor3d(0.0, 0.70, 0.30);
    glRotated(-(hour * 30 + minute * 0.5 + second * 0.08333333333), 0, 0, 1);

    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(0, 0.3);
    glEnd();
    
    glPopMatrix();
    
	glFlush();
}

void timer(int arg) {
    if (++second == 60) {
        if (++minute == 60) {
            if (++hour == 12)
                hour = 0;
            minute = 0;
        }
        second = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    hour = ltm->tm_hour;
    minute = ltm->tm_min;
    second = ltm-> tm_sec;

	glutMainLoop();	
	
	return 0;
}
