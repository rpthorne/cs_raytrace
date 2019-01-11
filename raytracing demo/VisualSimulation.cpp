/****************************************************************
 *	VisualSimulation
 *
 *	A visual adaptation using OpenGL as a representation of a 
 * single simulation. Contains the main method of the entire 
 * project
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "simulation.h"
#include <time.h>
#include <queue>
#define PI 3.1415
#define DEGREES ((1.0 / 180.0)*PI)

static GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };
static GLdouble cpos[] = { 0.0, 5.0, 5.0 };
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat grey[] = { 0.5, 0.5, 0.5, 1.0 };
static GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
static GLfloat reflect[] = { 1.0, 1.0, 0.0, 1.0 };

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

//simulation bits for changing views & items rendered.
int view = 1, sampleRay = 0, detectorMock = 0, drawSample = 1, drawRays = 0, pixelate = 0;

//detector plate result displays
deplentry **results = new deplentry*;
int detectorNumHits = 0, detectorSimpleIntensity = 0, detectorComplexIntensity = 0, simulationRan = 0;
#ifndef INTENSITY_SCALE
#define INTENSITY_SCALE 5.0
#endif // INTENSITYSCALE

//inherit and update simulation

struct ray
{
	Point src;
	Point dest;
};
class VisualSimulation : public simulation
{
	const int cull_factor = 1;
	int cull_count;
	std::queue<ray> d_ray;
public:
	VisualSimulation() : simulation() { cull_count = 0; };
	int draw_ray(XRay &x) override {
		if (++cull_count < cull_factor)
			return 0;
		cull_count = 0;
		ray s = { x.get_src(), x.get_src() + x.get_dir().traverse(x.get_length()) };
		d_ray.emplace(s);
		return 1;
	}
	std::queue<ray> get_d_ray()
	{
		return d_ray;
	}
};


VisualSimulation vs;



void writemessage()
{
	printf("\n\tVisual representation of X-Ray tracing simulation\n");
	printf("\t\t> Use \'w\' to toggle wire mesh\n");
	printf("\t\t> Use arrow keys to position camera in scene view\n");
	printf("\t\t> Use \'v\' to toggle between detector view and scene view\n");
	printf("\t\t> Use \'0\' to display mocked detector results\n");
	printf("\t\t> Use \'1\' to display actual detector num_hits results\n");
	printf("\t\t> Use \'2\' to display actual detector simple_intensity results\n");
	printf("\t\t> Use \'3\' to display actual detector complex_intensity results\n");
	printf("\t\t> Use \'r\' to display a single mocked XRay\n");
	printf("\t\t> Use \'R\' to display actual XRays fired\n");
	printf("\t\t> Use \'p\' to toggle pixel outline on detector plate\n");
	printf("\t\t> Use \'s\' to toggle rendering the sample sphere\n");
	printf("");
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
}

void drawDetector() {
	detector_width = DETECTOR_PLATE_SIZE;
	detector_height = DETECTOR_PLATE_SIZE;
	width_pixels = DETECTOR_PLATE_WIDTH;
	height_pixels = DETECTOR_PLATE_HEIGHT;
	float pixelWidth = detector_width / (float)width_pixels;
	float pixelHeight = detector_height / (float)height_pixels;
	int i, j;
	glNormal3fv(detectorNormal);

	

	for (i = 0; i < width_pixels; i++) {
		for (j = 0; j < height_pixels; j++) {
			//mocked detector plate results from before real results were available
			if (detectorMock) {
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
			}
			else if (detectorNumHits && simulationRan)
			{
				if ((*results)[i * height_pixels + j].num_hits < 1)
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
				else if((*results)[i * height_pixels + j].num_hits < 2)
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low);
				else if ((*results)[i * height_pixels + j].num_hits < 3)
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low_mid);
				else if ((*results)[i * height_pixels + j].num_hits < 4)
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid);
				else if ((*results)[i * height_pixels + j].num_hits < 5)
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid_high);
				else
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, high);
			}
			else if (detectorSimpleIntensity && simulationRan)
			{
				if ((*results)[i * height_pixels + j].simple_intensity <= 0.0)
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
				else if ((*results)[i * height_pixels + j].simple_intensity < (0.2 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low);
				else if ((*results)[i * height_pixels + j].simple_intensity < (0.4 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low_mid);
				else if ((*results)[i * height_pixels + j].simple_intensity < (0.6 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid);
				else if ((*results)[i * height_pixels + j].simple_intensity < (0.8 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid_high);
				else
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, high);
			}
			else if (detectorComplexIntensity && simulationRan)
			{
				if ((*results)[i * height_pixels + j].complex_intensity <= 0.0)
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
				else if ((*results)[i * height_pixels + j].complex_intensity < (0.2 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low);
				else if ((*results)[i * height_pixels + j].complex_intensity < (0.4 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low_mid);
				else if ((*results)[i * height_pixels + j].complex_intensity < (0.6 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid);
				else if ((*results)[i * height_pixels + j].complex_intensity < (0.8 * INTENSITY_SCALE))
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mid_high);
				else 
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, high);
			}
			else glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
			//colors the pixel hit by the mocked XRay
			if (j == 80 && i == 50 && sampleRay) glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, low);
			glBegin(GL_POLYGON);
			glVertex3f(-(detector_width / 2.0) + j * pixelWidth, detector_height / 2.0 - i * pixelHeight, 0.0);
			glVertex3f(-(detector_width / 2.0) + j * pixelWidth, detector_height / 2.0 - (i + 1)*pixelHeight, 0.0);
			glVertex3f(-(detector_width / 2.0) + (j + 1)*pixelWidth, detector_height / 2.0 - (i + 1)*pixelHeight, 0.0);
			glVertex3f(-(detector_width / 2.0) + (j + 1)*pixelWidth, detector_height / 2.0 - i * pixelHeight, 0.0);
			glEnd();

			//draws lines around every pixel
			if (pixelate) {
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
				glBegin(GL_LINE_LOOP);
				glVertex3f(-(detector_width / 2.0) + j * pixelWidth, detector_height / 2.0 - i * pixelHeight, 0.001);
				glVertex3f(-(detector_width / 2.0) + j * pixelWidth, detector_height / 2.0 - (i + 1)*pixelHeight, 0.001);
				glVertex3f(-(detector_width / 2.0) + (j + 1)*pixelWidth, detector_height / 2.0 - (i + 1)*pixelHeight, 0.001);
				glVertex3f(-(detector_width / 2.0) + (j + 1)*pixelWidth, detector_height / 2.0 - i * pixelHeight, 0.001);
				glEnd();
			}
		}
	}
}

void draw_ray(ray s)
{
	Point origin = s.src;
	Point dest = s.dest;
	Point tenth = Point((origin - dest).getX() * .1f, (origin - dest).getY() * .1f, (origin - dest).getY() * .1f);
	float R2I = 1.0 / sqrtf(2.0);

	glBegin(GL_LINES);
	glVertex3f(dest.getX(), dest.getY(), dest.getZ());
	glVertex3f(origin.getX(), origin.getY(), origin.getZ());/*
	glVertex3f(dest.getX(), dest.getY(), dest.getZ());
	glVertex3f(tenth.getX() + dest.getX(), tenth.getY() * R2I - tenth.getZ() * .5f + dest.getY(), tenth.getY() * .5f + tenth.getZ() * R2I + dest.getZ());
	glVertex3f(dest.getX(), dest.getY(), dest.getZ());
	glVertex3f(tenth.getZ() * .5f + tenth.getX() * R2I + dest.getX(), tenth.getY() + dest.getY(), tenth.getZ() * R2I - tenth.getX() * .5f + dest.getZ());*/
	glEnd();
	glBegin(GL_POINTS);
	glVertex3f(origin.getX(), origin.getY(), origin.getZ());
	glVertex3f(dest.getX(), dest.getY(), dest.getZ());
	glEnd();
}

void drawRaygun() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grey);

	glNormal3f(0.0, -1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.75, 0.75, 2.0);
	glVertex3f(-0.75, 0.75, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.75, -0.75, 2.0);
	glVertex3f(0.75, -0.75, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.75, -0.75, 2.0);
	glVertex3f(0.75, 0.75, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.75, 0.75, 2.0);
	glVertex3f(-0.75, -0.75, 2.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	//draw the mocked sample XRay
	if (sampleRay && view != 1) {
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cyan);
		ray r1 = { Point(0.0, 0.0, 0.0), Point(0.0, sin(30 * DEGREES), 5.0 - cos(30 * DEGREES)) };
		draw_ray(r1);
		ray r2 = { Point(0.0, sin(30 * DEGREES), 5.0 - cos(30 * DEGREES)), Point(0.0, sin(120*DEGREES), 5.0 - cos(120*DEGREES)) };
		draw_ray(r2);
		ray r3 = { Point(0.0, sin(120 * DEGREES), 5 - cos(120 * DEGREES)), Point(0.0, 1.5, 7.0) };
		draw_ray(r3);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, reflect);
		ray r4 = { Point(0.0, sin(30 * DEGREES), 5.0 - cos(30 * DEGREES)), Point(0.0, sin(30 * DEGREES) + 0.5, 4.8 - cos(30 * DEGREES)) };
		draw_ray(r4);
		ray r5 = { Point(0.0, sin(120 * DEGREES), 5 - cos(120 * DEGREES)), Point(0.0, sin(120 * DEGREES)-0.7, 4.9 - cos(120 * DEGREES)) };
		draw_ray(r5);
	}
	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//update camera position 
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

	//remaining objects will not look as if they emit light 
	glMaterialfv(GL_FRONT, GL_EMISSION, black);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grey);
	if (view == 3 && drawSample) glutSolidSphere(SPHERE_RADIUS, 30, 20);

	//draw detector plate
	detector_distance = DETECTOR_PLATE_DEPTH;
	glPushMatrix();	//saving initial matrix position (0.0, 0.0, 0.0)
	glTranslatef(-(detector_distance), 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	//align axis'
	glRotatef(90, 0.0, 0.0, 1.0);
	drawDetector();
	glPopMatrix(); //restore original matrix position

	//draw raygun
	raygun_distance = CAMERA_SOURCE_DEPTH;
	glPushMatrix(); //save initial matrix position
	glTranslatef(raygun_distance, 0.0, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	drawRaygun();
	glPopMatrix(); //restore original matrix position

	//draw rays
	glPushMatrix(); //save initial matrix position
	glRotatef(90, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cyan);
	if (drawRays) {
		std::queue<ray> dr = vs.get_d_ray();
		while (!dr.empty())
		{
			draw_ray(dr.front());
			dr.pop();
		}
	}
	glPopMatrix(); //restore original matrix position

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

	case 'r':
		if (sampleRay)
			sampleRay = 0;
		else
			sampleRay = 1;
		glutPostRedisplay();
		break;
	case 'R':
		if (drawRays)
			drawRays = 0;
		else
			drawRays = 1;
		glutPostRedisplay();
		break;

	case '0':
		if (detectorMock) 
			detectorMock = 0;
		else {
			detectorMock = 1;
			detectorNumHits = 0;
			detectorSimpleIntensity = 0;
			detectorComplexIntensity = 0;
		}
		glutPostRedisplay();
		break;

	case '1':
		if (detectorNumHits)
			detectorNumHits = 0;
		else {
			detectorMock = 0;
			detectorNumHits = 1;
			detectorSimpleIntensity = 0;
			detectorComplexIntensity = 0;
		}
		glutPostRedisplay();
		break;

	case '2':
		if (detectorSimpleIntensity)
			detectorSimpleIntensity = 0;
		else {
			detectorMock = 0;
			detectorNumHits = 0;
			detectorSimpleIntensity = 1;
			detectorComplexIntensity = 0;
		}
		glutPostRedisplay();
		break;

	case '3':
		if (detectorComplexIntensity)
			detectorComplexIntensity = 0;
		else {
			detectorMock = 0;
			detectorNumHits = 0;
			detectorSimpleIntensity = 0;
			detectorComplexIntensity = 1;
		}
		glutPostRedisplay();
		break;

	case 's':
		if (drawSample)
			drawSample = 0;
		else
			drawSample = 1;
		glutPostRedisplay();
		break;

	case 'p':
		if (pixelate)
			pixelate = 0;
		else
			pixelate = 1;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	clock_t t;
	t = clock();
		vs = VisualSimulation();
	t = clock() - t;
	printf("number of seconds to initialize simulation: (%f)\n", ((float)t) / CLOCKS_PER_SEC);
	
	t = clock();
	int failure = vs.run_scene();
	t = clock() - t;
	printf("number of seconds to compute simulation: (%f)\n", ((float)t) / CLOCKS_PER_SEC);

	
	if (failure) printf("simulation failed to run correctly!\n");
	else failure = vs.clean_scene(results);
	if (failure) printf("failed to collect simulation results!\n");
	else simulationRan = 1;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
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