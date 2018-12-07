////////////////////////////////////////////////////////
// Lab Exercise 07.cpp
// Uses glutTimerFunc() to smoothly start and stop animation
//
///////////////////////////////////////////////////////


#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "simulation.cpp"
#define PI 3.1415

static GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };
static GLdouble cpos[] = { 0.0, 5.0, 5.0 };
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat grey[] = { 0.5, 0.5, 0.5, 1.0 };
static GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };

static GLfloat low[] = { 0.0, 1.0, 0.0, 1.0 };
static GLfloat low_mid[] = { 0.5, 1.0, 0.0, 1.0 };
static GLfloat mid[] = { 1.0, 1.0, 0.0, 1.0 };
static GLfloat mid_high[] = { 1.0, 0.5, 0.0, 1.0 };
static GLfloat high[] = { 1.0, 0.0, 0.0, 1.0 };

//dynamic dimensions
static GLfloat detector_distance, raygun_distance;
static GLfloat detector_width, detector_height;
static int width_pixels, height_pixels;
const GLfloat detectorNormal[3] = { 0.0, 0.0, 1.0 };

/* camera location in longitude and latitude */
static float alpha = 0.0;
static float beta = PI / 6.0;

int view = 1;

void writemessage()
{
	printf("\n\tVisual representation of X-Ray tracing simulation\n");
	printf("\t\t> Use \'w\' to toggle wire mesh. Useful to see detector pixels\n");
	printf("\t\t> Use arrow keys to position camera in scene view\n");
	printf("\t\t> Use \'v\' to toggle between screen view and scene view\n");
	printf("");
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (view == 3)
		gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
	else
		gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 2.0, 50.0);
}

void drawDetector() {
	detector_width = 5.0;
	detector_height = 5.0;
	width_pixels = 100;
	height_pixels = 100;
	float pixelWidth = detector_width / (float)width_pixels;
	float pixelHeight = detector_height / (float)height_pixels;
	int i, j;
	glNormal3fv(detectorNormal);

	for (i = 0; i < width_pixels; i++) {
		for (j = 0; j < height_pixels; j++) {
			if (sqrt(abs(i - 50)*abs(i - 50) + abs(j - 50)*abs(j - 50)) > 55)
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
			else if (sqrt(abs(i - 50)*abs(i - 50) + abs(j - 50)*abs(j - 50)) > 45)
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low);
			else if (sqrt(abs(i - 50)*abs(i - 50) + abs(j - 50)*abs(j - 50)) > 35)
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low_mid);
			else if (sqrt(abs(i - 50)*abs(i - 50) + abs(j - 50)*abs(j - 50)) > 25)
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid);
			else if (sqrt(abs(i - 50)*abs(i - 50) + abs(j - 50)*abs(j - 50)) > 15)
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid_high);
			else
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, high);

			glBegin(GL_POLYGON);
			glVertex3f(-(detector_width / 2.0) + j * pixelWidth, detector_height / 2.0 - i * pixelHeight, 0.0);
			glVertex3f(-(detector_width / 2.0) + j * pixelWidth, detector_height / 2.0 - (i + 1)*pixelHeight, 0.0);
			glVertex3f(-(detector_width / 2.0) + (j + 1)*pixelWidth, detector_height / 2.0 - (i + 1)*pixelHeight, 0.0);
			glVertex3f(-(detector_width / 2.0) + (j + 1)*pixelWidth, detector_height / 2.0 - i * pixelHeight, 0.0);
			glEnd();
		}
	}
}

void drawRaygun() {
	//draw rays here?
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grey);

	glNormal3f(0.0, -1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.0, 1.0, 2.0);
	glVertex3f(-1.0, 1.0, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, -1.0, 2.0);
	glVertex3f(1.0, -1.0, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.0, -1.0, 2.0);
	glVertex3f(1.0, 1.0, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0, 1.0, 2.0);
	glVertex3f(-1.0, -1.0, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* update camera position */
	cpos[0] = 7.0 * cos(beta) * sin(alpha);
	cpos[1] = 7.0 * sin(beta);
	cpos[2] = 7.0 * cos(beta) * cos(alpha);
	if (view == 3)
		gluLookAt(cpos[0], cpos[1], cpos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else
		gluLookAt(1.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	static GLfloat lpos[] = { 1.0, 2.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glMaterialfv(GL_FRONT, GL_EMISSION, white);
	//glPushMatrix();
	//glTranslatef(lpos[0], lpos[1], lpos[2]);
	//glutSolidSphere(0.1, 10, 8);
	//glPopMatrix();

	/* remaining objects do not look as if they emit light */
	glMaterialfv(GL_FRONT, GL_EMISSION, black);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grey);
	glutSolidSphere(1.0, 30, 20);

	//draw detector plate
	detector_distance = 2.0;
	glPushMatrix();
	glTranslatef(-(detector_distance), 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	drawDetector();
	glPopMatrix();

	//draw raygun
	raygun_distance = 5.0;
	glPushMatrix();
	glTranslatef(raygun_distance, 0.0, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	drawRaygun();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void specialkey(GLint key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (view == 3) {
			alpha = alpha + PI / 180;
			if (alpha > 2 * PI) alpha = alpha - 2 * PI;
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_LEFT:
		if (view == 3) {
			alpha = alpha - PI / 180;
			if (alpha < 0) alpha = alpha + 2 * PI;
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_UP:
		if (view == 3) {
			if (beta < 0.45*PI) beta = beta + PI / 180;
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_DOWN:
		if (view == 3) {
			if (beta > 0.05*PI) beta = beta - PI / 180;
			glutPostRedisplay();
		}
		break;

	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	static int polygonmode[2];

	switch (key) {
	case 27:
		exit(0);
		break;

	case 'w':
		glGetIntegerv(GL_POLYGON_MODE, polygonmode);
		if (polygonmode[0] == GL_FILL)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;

	case 'v':
		if (view == 1)
			view = 3;
		else
			view = 1;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);
	writemessage();
	glutMainLoop();
	return 0;
}