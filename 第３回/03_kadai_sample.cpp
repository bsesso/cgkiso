#include <cstdlib>
#include <stdio.h>
#include <GLUT/glut.h>
#include <cmath>

// �F�̏����i�[���鋤�p��
union color {
	struct { float r, g, b, a; };
	float colors[4];
};

// �X�̃e�B�[�|�b�g�̐F��A�X���p�x�Ɋւ������ێ����邽�߂̍\����
struct TeapotData {
	color ambient, diffuse, specular;
	float shininess, angle;
};

// �O���[�o���ϐ��i�v���O�������̂ǂ�����ł��A�N�Z�X�ł���ϐ��j�ɂ� g_ ��t���Ă���
const int g_NumTeapots = 8;
TeapotData g_Teapots[g_NumTeapots];

// float�^�̒l�́A�����̌���f��t����B�����̃[���͏ȗ��ł���
const float g_TeapotSize = 1.f;
const float g_InnerRadius = 6.f;
const float g_OuterRadius = 7.5f;
const float g_HeightAmplitude = 0.8f;
const float g_HeightOffset = 0.2f;

const float g_EyeCenterY = 9.f;
const float g_EyeCenterZ = 30.f;
const float g_EyeRadius = 8.f;
float g_EyeX = 0, g_EyeY = 0, g_EyeZ = 30;

// My
float fovy = 30;
float eyecx = 0, eyecy = 0, eyecz = -1;
float deltaMove = 0;
float deltaAngle = 0;
float angle = 0;
float xOrigin = -1;

const int g_AnimationIntervalMsec = 10;

float g_RotationDegree = 0.f;
const float g_DeltaRotationDegree = 0.3;

int g_WindowWidth = 512;
int g_WindowHeight = 512;

// �~����`��c�����͉~�̔��a�A�����A�~�̕�����
// glut�ɂ͉~����`�悷�邽�߂̊֐��������̂ŁA�Ǝ��ɏ���
void displayCylinder(float radius, float height, int nSlices) {
	// �V����
	const float deltaTheta = 2 * M_PI / (float)nSlices;

	glNormal3f(0, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, height, 0);
	for (int i = 0; i <= nSlices; i++) {
		const float theta = deltaTheta * i;
		glVertex3f(radius * cosf(theta), height, radius * sinf(theta));
	}
	glEnd();

	// ���
	glNormal3f(0, -1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= nSlices; i++) {
		const float theta = deltaTheta * i;
		glVertex3f(radius * cosf(theta), 0, radius * sinf(theta));
	}
	glEnd();

	// ����
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= nSlices; i++) {
		const float theta = deltaTheta * i;
		const float cosTheta = cosf(theta);
		const float sinTheta = sinf(theta);
		glNormal3f(cosTheta, 0, sinTheta);
		glVertex3f(radius * cosTheta, height, radius * sinTheta);
		glVertex3f(radius * cosTheta, 0, radius * sinTheta);
	}
	glEnd();
}

void updateCameraPos() {
	g_EyeX += deltaMove * eyecx;
	g_EyeZ += deltaMove * eyecz;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������e�ϊ��̐ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, g_WindowWidth/(double)g_WindowHeight, 1, 100.0);

	// ���f�����W�̑���փ��[�h�؂�ւ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (deltaMove)
		updateCameraPos();
	gluLookAt(g_EyeX, g_EyeY, g_EyeZ, 
			  g_EyeX + eyecx, 0, g_EyeZ + eyecz, 
			  0.0, 1.0, 0.0);

	float ambientColor[] = { 0.4f, 0.2f, 0.2f, 1.0f };
	float diffuseColor[] = { 1.f, 0.8f, 0.8f, 1.0f };
	float specularColor[] = { 0.4f, 0.3f, 0.3f, 1.0f };
	float shininess = 5.f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	// ����
	glPushMatrix();
	glTranslatef(0, g_HeightAmplitude + g_HeightOffset + 3.f, 0);
	glRotated(g_RotationDegree, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(g_OuterRadius, 2.f, 32, 32);
	glPopMatrix();

	// ���S�̒�
	glPushMatrix();
	glTranslatef(0, -1.f, 0);
	glRotated(g_RotationDegree, 0, 1, 0);
	displayCylinder(0.5f, g_HeightAmplitude + g_HeightOffset + 6.5f, 32);
	glPopMatrix();

	// �y��
	glPushMatrix();
	glTranslatef(0, -2.f, 0);
	glRotated(g_RotationDegree, 0, 1, 0);
	glRotated(g_RotationDegree, 0, 1, 0);
	displayCylinder(g_OuterRadius, 0.7f, 64);
	glPopMatrix();

	// �����̏�̃e�B�[�|�b�g
	glPushMatrix();
	glTranslatef(0, g_HeightAmplitude + g_HeightOffset + 5.5f, 0);
	glRotatef(g_RotationDegree, 0, 1, 0); // ��]�����Ă���
	glutSolidTeapot(g_TeapotSize);
	glPopMatrix();

	const float deltaTheta = 360 / (float)g_NumTeapots;

	// �e�B�[�|�b�g�ƒ���1���`�悷��
	// �����L�̃R�[�h�ł́A��ɓ����ʒu�ɕ`�悳���̂ŁA�S�̂���]����悤�ɕύX����
	glRotated(g_RotationDegree, 0, 1, 0);
	for (int i = 0; i < g_NumTeapots; i++) {
		const float thetaDegree = deltaTheta * i; // �e�B�[�|�b�g�̈ʒu�����߂邽�߂̊p�x

		const float thetaRad = thetaDegree * M_PI / 180.f;
		const float xPos = g_InnerRadius * sinf(thetaRad);
		const float zPos = g_InnerRadius * cosf(thetaRad);

		// �e�B�[�|�b�g�̍��������̒l
		const float yPos = g_HeightOffset; // �����̒l���������ω������邱�ƂŃe�B�[�|�b�g���㉺�Ɉړ�����
		const float maxHeight = 0.5;

		// �e�B�[�|�b�g�̐F�̎w��
		glMaterialfv(GL_FRONT, GL_AMBIENT  , g_Teapots[i].ambient.colors);
		glMaterialfv(GL_FRONT, GL_DIFFUSE  , g_Teapots[i].diffuse.colors);
		glMaterialfv(GL_FRONT, GL_SPECULAR , g_Teapots[i].specular.colors);
		glMaterialfv(GL_FRONT, GL_SHININESS, &g_Teapots[i].shininess);


		// �e�B�[�|�b�g�̕`��
		glPushMatrix();
		glTranslatef(xPos, yPos + (((i % 2) - 0.5) * 2) * maxHeight * sin(0.5 * g_RotationDegree) + 1, zPos);
		glRotatef(thetaDegree, 0, 1, 0);
		glRotatef(g_Teapots[i].angle, 0, 0, 1);
		glutSolidTeapot(1.2f * g_TeapotSize);
		glPopMatrix();

		// �e�B�[�|�b�g���x���钌�̐F�̎w�� 
		glMaterialfv(GL_FRONT, GL_AMBIENT,   ambientColor);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuseColor);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  specularColor);
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		// �e�B�[�|�b�g���x���钌�̕`��
		glPushMatrix();
		glTranslatef(xPos, -1.f, zPos);
		displayCylinder(0.3f, yPos + (((i % 2) - 0.5) * 2) * maxHeight * sin(0.5 * g_RotationDegree) + 1 + 1.f, 32);
		glPopMatrix();
	}


	glutSwapBuffers();
}

float frand() { return rand() / (float)RAND_MAX; }

// �����ݒ���s���֐�
void init() {
	glClearColor(1, 1, 1, 1);
	glClearDepth(100.f);

	float lightAmbientColor0[] = { 0.2f, 0.2f, 0.2f, 0.0f };
	float lightDiffuseColor0[] = { 0.4f, 0.4f, 0.4f, 0.0f };
	float lightSpecularColor0[] = { 0.8f, 0.8f, 0.8f, 0.0f };
	float lightPosition0[] = { 5.0f, 5.0f, 8.0f, 0.0f };

	float lightAmbientColor1[] = { 0.2f, 0.2f, 0.2f, 0.0f };
	float lightDiffuseColor1[] = { 0.4f, 0.4f, 0.4f, 0.0f };
	float lightSpecularColor1[] = { 0.8f, 0.8f, 0.8f, 0.0f };
	float lightPosition1[] = { -5.0f, 2.0f, 3.0f, 0.0f };

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbientColor0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseColor0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecularColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbientColor1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuseColor1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecularColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

	srand(0);

	// �X�̃e�B�[�|�b�g�̐F��ݒ肷�鏈�� �����Ō��߂Ă���
	for (int i = 0; i < g_NumTeapots; i++) {
		g_Teapots[i].ambient.r = 0.2f * frand();
		g_Teapots[i].ambient.g = 0.2f * frand();
		g_Teapots[i].ambient.b = 0.2f * frand();
		g_Teapots[i].ambient.a = 1.f;

		g_Teapots[i].diffuse.r = 0.2f * frand() + 0.8f;
		g_Teapots[i].diffuse.g = 0.2f * frand() + 0.8f;
		g_Teapots[i].diffuse.b = 0.2f * frand() + 0.8f;
		g_Teapots[i].diffuse.a = 1.f;

		g_Teapots[i].specular.r = 0.3f * frand() + 0.2f;
		g_Teapots[i].specular.g = 0.3f * frand() + 0.2f;
		g_Teapots[i].specular.b = 0.3f * frand() + 0.2f;
		g_Teapots[i].specular.a = 1.f;

		g_Teapots[i].shininess = 2.f + 30 * frand();

		g_Teapots[i].angle = 15 * (2.f * frand() - 1.f);
	}

	glEnable(GL_DEPTH_TEST);
}

// ��莞�Ԃ��ƂɎ��s�����֐�
void timer(int val) {
	// ��]�p�x�̍X�V
	g_RotationDegree += g_DeltaRotationDegree;

	const float rotationRad = 2.f * g_RotationDegree * M_PI / 180.f;
	
	// �� ���̃R�[�h�ł͎��_���Œ肾����
	// ������  g_EyeY �� g_EyeZ �̒l��ς��邱�ƂŎ��_�ʒu��ω������邱�Ƃ��ł���
	// g_EyeY = g_EyeCenterY;
	// g_EyeZ = g_EyeCenterZ;

	glutPostRedisplay();

	glutTimerFunc(g_AnimationIntervalMsec, timer, val);
}

// �E�B���h�E�T�C�Y���ύX���ꂽ�Ƃ��̏���
void reshape(int w, int h) {
	if (h < 1) return;

	// �r���[�|�[�g���E�B���h�E�T�C�Y�ɕύX
	glViewport(0, 0, w, h);
	g_WindowWidth = w;
	g_WindowHeight = h;
}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			eyecy += 1;
		break;	
		case GLUT_KEY_DOWN:
			eyecy -= 1;
		break;
		case GLUT_KEY_LEFT:
			eyecx -= 1;
		break;
		case GLUT_KEY_RIGHT:
			eyecx += 1;
		break;
	}

	glutPostRedisplay();
}

void pressKey(unsigned char key, int x, int y) {
	switch(key) {
		case 'w':
			deltaMove = 0.5;
		break;
		case 's':
			deltaMove = -0.5;
		break;
		case 'a':
		break;
		case 'd':
		break;
	}

	glutPostRedisplay();
}

void upKey(unsigned char key, int x, int y) {
	switch(key) {
		case 'w':
			deltaMove = 0;
		break;
		case 's':
			deltaMove = 0;
		break;
		case 'a':
		break;
		case 'd':
		break;
	}

	glutPostRedisplay();
}

void mouseMove(int x, int y) { 	
// this will only be true when the left button is down
// if (xOrigin >= 0) {
// update deltaAngle
		deltaAngle = -(x - xOrigin) * 0.001f;
// update camera's direction
		eyecx = sin(angle + deltaAngle);
		eyecz = -cos(angle + deltaAngle);
	// }
}
void mouseButton(int button, int state, int x, int y) {
// only start motion if the left button is pressed
if (button == GLUT_LEFT_BUTTON) {
// when the button is released
if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
		}
else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(g_WindowWidth, g_WindowHeight);

	// �E�B���h�E�^�C�g���ɕ\�����镶������w�肷��ꍇ
	glutCreateWindow("Teapot Merry-Go-Round");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape); // �E�B���h�E�T�C�Y���ύX���ꂽ�Ƃ��Ɏ��s�����֐����w��
	glutTimerFunc(g_AnimationIntervalMsec, timer, 0);

	glutSpecialFunc(SpecialInput);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(upKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


	// �����ݒ���s��
	init();

	glutMainLoop();

	return 0;
}
