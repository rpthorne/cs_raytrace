//basic glut information to start building raytraces
//ryan thorne
//it is worth mentioning that this IS spaghetti code b/c not sure if it will be used


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // (or others, depending on the system in use)
#include <iostream>
#include <fstream>
#include "Pointf.h"


//from "Quake III Arena"
//https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c#L552
//(lines 552 - 572) taken from wikepedia article, unmodified:
//https://en.wikipedia.org/wiki/Fast_inverse_square_root#cite_note-quakesrc-6
//finds the approximate inverse square root in a short, time efficient manner.
float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck? 
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
										   // y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed

	return y;
}


//math constants precomputed
float R2I = Q_rsqrt(2); //    1/sqrt(2)

//lol wtf even is good formating



//"environment" variables
GLsizei win_width = 600, win_height = 600;
Pointf wrot;
Pointf trans;
float xdiff;
float ydiff;
int width, height;
Pointf src;

//array holding each source point of ray
Pointf** p_ray_src;

//array holding the initial direction of the rays
Pointf** d_ray_src;

//determines the maximum/minimum diffusion of a ray in degrees
GLfloat max_diffusion_coefficient;
GLfloat min_diffusion_coefficient;

//holds the ray gun definitions

//determines the rectangle of the view screen
Pointf gunbox_view1;
Pointf gunbox_view2;
//the rectangle of the origin
Pointf gunbox_orig1;
Pointf gunbox_orig2;

int poly_count;
Pointf** poly_list;

//rotation of the plane in the scene
Pointf planerot;
bool mouseDown;

//part 2 look controls
Pointf m_offset;




//return value is t parameter along the direction vector from the origin point to the point on the plane (triangle) that the ray passes through
//if it is less than 0, there is no collision for the ray to the plane in question

//only collision upon the triangle defining the plane, not the whole plane itself :)
GLfloat ray_plane_collision(Pointf* const r_origin, Pointf* const r_direction, Pointf* const p_1, Pointf* const p_2, Pointf* const p_3)
{
	//you can actually just solve this by hand and plug in the values from there, but this is less time consuming for me and it is a prototype so w/e
	GLfloat matrix[3][4];
	int i;
	//set up matrix
	Pointf* temp;
	matrix[0][0] = p_2->x - p_1->x;
	matrix[0][1] = p_3->x - p_1->x;
	matrix[0][2] = -1 * r_direction->x;
	matrix[0][3] = r_origin->x - p_1->x;
	matrix[1][0] = p_2->y - p_1->y;
	matrix[1][1] = p_3->y - p_1->y;
	matrix[1][2] = -1 * r_direction->y;
	matrix[1][3] = r_origin->y - p_1->y;
	matrix[2][0] = p_2->z - p_1->z;
	matrix[2][1] = p_3->z - p_1->z;
	matrix[2][2] = -1 * r_direction->z;
	matrix[2][3] = r_origin->z - p_1->z;
	//ensure [0][0] is not 0;
	if (abs(matrix[0][0]) <= 0.0001)//add one of row1 to force non-zero
	{
		matrix[0][0] += matrix[1][0];
		matrix[0][1] += matrix[1][1];
		matrix[0][2] += matrix[1][2];
		matrix[0][3] += matrix[1][3];
	}
	if (abs(matrix[0][0]) <= 0.0001)//add one of row2 to force non-zero
	{
		matrix[0][0] += matrix[2][0];
		matrix[0][1] += matrix[2][1];
		matrix[0][2] += matrix[2][2];
		matrix[0][3] += matrix[2][3];
	}
	if (abs(matrix[0][0]) <= 0.0001)//fails, return
	{
		return -1;
	}

	//divide row 0 by col0
	for (i = 1; i < 4; i++)
	{
		matrix[0][i] = matrix[0][i] / matrix[0][0];
		matrix[1][i] = matrix[1][i] - (matrix[1][0] * matrix[0][i]);
		matrix[2][i] = matrix[2][i] - (matrix[2][0] * matrix[0][i]);
	}
	//now the first collumn is [[1][0][0]] but i wont change that in memory
	//from here we are interested in returning t, so solve for that first

	if (abs(matrix[2][2] - matrix[1][2] * matrix[2][1] / matrix[1][1]) <= .001f)
		return -1.0f;
	//t exists, t is greater than 0;
	//now solve fo rthe other two values;

	if (abs(matrix[1][1]) <= .0001) // add one of row2 to force non-zero
	{
		matrix[1][1] += matrix[2][1];
		matrix[1][2] += matrix[2][2];
		matrix[1][3] += matrix[2][3];
	}
	if (abs(matrix[1][1]) <= .0001) // fails, non-unique solution
		return -1.0f;

	//solve beta
	matrix[1][0] = (matrix[1][3] - matrix[1][2] * (matrix[2][3] - matrix[1][3] * matrix[2][1] / matrix[1][1]) / (matrix[2][2] - matrix[1][2] * matrix[2][1] / matrix[1][1])) / matrix[1][1];
	
	//soln for t
	matrix[2][0] = (matrix[2][3] - matrix[1][3] * matrix[2][1] / matrix[1][1]) / (matrix[2][2] - matrix[1][2] * matrix[2][1] / matrix[1][1]);

	//soln for alpha
	matrix[0][0] = matrix[0][3] - matrix[0][1] * matrix[1][0] - matrix[0][2] * matrix[2][0];

	if (matrix[1][0] < 0 || matrix[0][0] < 0 || matrix[0][0] + matrix[1][0] > 1) // fail, item outside of triangle
		return -1.0f;

	return matrix[2][0];
}


void draw_plane()
{
	//translate to plane position
	glPointSize(4);
	int i;
	for (i = 0; i < poly_count; i++)
	{

		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		glVertex3f(poly_list[i][0].x, poly_list[i][0].y, poly_list[i][0].z);
		glVertex3f(poly_list[i][1].x, poly_list[i][1].y, poly_list[i][1].z);
		glVertex3f(poly_list[i][2].x, poly_list[i][2].y, poly_list[i][2].z);
		glEnd();

		glColor3f(0.0, 1.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
		Pointf norm = surf_norm(*(poly_list[i]), *(poly_list[i] + 1), *(poly_list[i] + 2));
		glNormal3f(norm.x, norm.y, norm.z);
		glBegin(GL_POLYGON);
		glVertex3f(poly_list[i][0].x, poly_list[i][0].y, poly_list[i][0].z);
		glVertex3f(poly_list[i][1].x, poly_list[i][1].y, poly_list[i][1].z);
		glVertex3f(poly_list[i][2].x, poly_list[i][2].y, poly_list[i][2].z);
		glEnd();
	}


}

//draws a line from source to dest and two lines from the dest out at a 30 degree angles from the x and y axis
void draw_ray(Pointf* const origin, Pointf* const dest)
{
	//fitted to the origin for easy computation
	Pointf tenth;
	tenth.x = (origin->x - dest->x) / 10.0f;
	tenth.y = (origin->y - dest->y) / 10.0f;
	tenth.z = (origin->z - dest->z) / 10.0f;

	glBegin(GL_LINES);
	glVertex3f(dest->x, dest->y, dest->z);
	glVertex3f(origin->x, origin->y, origin->z);
	//glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(dest->x, dest->y, dest->z);
	glVertex3f(tenth.x + dest->x, tenth.y * R2I - tenth.z * .5f + dest->y, tenth.y * .5f + tenth.z * R2I + dest->z);
	glVertex3f(dest->x, dest->y, dest->z);
	glVertex3f(tenth.z * .5f + tenth.x * R2I + dest->x, tenth.y + dest->y, tenth.z * R2I - tenth.x * .5f + dest->z);
	glEnd();
	glBegin(GL_POINTS);
	glVertex3f(origin->x, origin->y, origin->z);
	glVertex3f(dest->x, dest->y, dest->z);
	glEnd();
}


void draw_raygun()
{
	Pointf or = { 0,0,0 };
	int i;
	int j;
	int k;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
		glVertex3f(gunbox_orig1.x, gunbox_orig1.y, gunbox_orig1.z);
		glVertex3f(gunbox_orig2.x, gunbox_orig2.y, gunbox_orig2.z);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(gunbox_view1.x, gunbox_view1.y, gunbox_view1.z);
		glVertex3f(gunbox_view2.x, gunbox_view2.y, gunbox_view2.z);
	glEnd();
	Pointf norm;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			
			//now if ray collides with objects in scene, draw those points
			GLfloat t;
			for (k = 0; k < poly_count; k++)

				if (0 < (t = ray_plane_collision(&p_ray_src[i][j], &d_ray_src[i][j], poly_list[k], poly_list[k] + 1, poly_list[k] + 2)))
				{
					//collision, draw point;
					Pointf loc = { p_ray_src[i][j].x + t * d_ray_src[i][j].x, p_ray_src[i][j].y + t * d_ray_src[i][j].y, p_ray_src[i][j].z + t * d_ray_src[i][j].z };
					norm = surf_norm(*(poly_list[k]), *(poly_list[k] + 1), *(poly_list[k] + 2));
					Pointf reflect = loc.scale_mul(2) - (p_ray_src[i][j]).reflect_across(norm);
					norm = loc - norm;
					//draw the rays to plane
					glColor3f(1.0f, 0.0f, 0.0f);
					draw_ray(&p_ray_src[i][j], &loc);
					//normal
					glColor3f(1.0f, 0.0f, 1.0f);
					draw_ray(&loc, &norm);
					//reflect line
					glColor3f(0.0f, 0.0f, 0.0f);
					draw_ray(&loc, &reflect);
				}
		}
	}
	
}
//TODO: initialize raybox as a feild of rays based on the two gunbox's
//assuming the gunbox and gunview maintain a 1:1 aspect ratio. create a frustrum
void define_raybox()
{
	int i, j;
	Pointf go0, go1;
	Pointf gv0, gv1;
	go0 = (gunbox_orig2 + gunbox_orig1).scale_mul(.5f);//center of gunbox
	gv0 = (gunbox_view2 + gunbox_view1).scale_mul(.5f);//center of view
	glBegin(GL_POINTS);
	glVertex3f(go0.x, go0.y, go0.z);
	glVertex3f(gv0.x, gv0.y, gv0.z);
	glEnd();
	Pointf norm = surf_norm(gunbox_orig1, gunbox_orig2, gunbox_view1); //finds some point orthagonal to the view trapezoid
	draw_ray(&go0, &gv0);
	go1 = norm + go0;
	draw_ray(&go0, &go1);
	go1 = norm.scale_mul((gunbox_orig1 - go0).magnitude_precise()) + go0;//gunbox point 3
	gv1 = norm.scale_mul((gunbox_view1 - gv0).magnitude_precise()) + gv0;//gunview point 3
	go0 = (go1 - gunbox_orig1).scale_mul(.5f).scale_div(width);//width value
	go1 = (go1 - gunbox_orig2).scale_mul(-.5f).scale_div(height);//height value
	gv0 = (gv1 - gunbox_view1).scale_mul(.5f).scale_div(width);//width value)
	gv1 = (gv1 - gunbox_view2).scale_mul(-.5f).scale_div(height);//height value
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
		{
			p_ray_src[i][j] = gunbox_orig1 + go0.scale_mul(2 * i + 1) + go1.scale_mul(2 * j + 1);
			d_ray_src[i][j] = gunbox_view1 + gv0.scale_mul(2 * i + 1) + gv1.scale_mul(2 * j + 1) - p_ray_src[i][j];
		}
	/*for (i = 0; i < width; i++)
	for (j = 0; j < height; j++)
	{
	p_ray_src[i][j].x = src.x;
	p_ray_src[i][j].y = src.y;
	p_ray_src[i][j].z = src.z;
	d_ray_src[i][j].x = -src.x;
	d_ray_src[i][j].y = -src.y;
	d_ray_src[i][j].z = -src.z;
	}*/
}

void disp(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	//glMaterialfv(GL_FRONT, GL_EMISSION, white);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 3.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	//put light in here
	glLightf(GL_LIGHT0, GL_DIFFUSE, (.5, .5, .5, 1));

	//glMaterialfv(GL_FRONT, GL_EMISSION, white);
	glTranslatef(0, 0, 6);
	glutSolidSphere(0.1, 10, 8);
	glTranslatef(0, 0, -6);
	//glMaterialfv(GL_FRONT, GL_EMISSION, black);
	//translation applied here
	GLfloat* tmp = trans.asArray();
	glTranslatef(tmp[0], tmp[1], tmp[2]);
	tmp = wrot.asArray();
	//camera rotation applied here
	glRotatef(tmp[0], 1.0f, 0.0f, 0.0f);
	glRotatef(tmp[1], 0.0f, 1.0f, 0.0f);
	glRotatef(0.0, 0.0f, 0.0f, 1.0f);

	//draw plane
	draw_plane();
	//draw raygun
	//define_raybox();
	draw_raygun();
	//draw rays
	

	glFlush();

}










void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		xdiff = x - wrot.y;
		ydiff = -y + wrot.x;
	}
	else mouseDown = false;
}

void mouseMotion(int x, int y)
{
	if (mouseDown)
	{
		wrot.y = x - xdiff;
		wrot.x = y + ydiff;
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[])
{
	//note that this is for more rays per item

	//controls
	printf("basic demonstration of raytracing");
	//gather informations from user
	printf("\nNumber of rays vertically:");
	scanf_s("%d", &width);
	printf("\nNumber of rays horizontally): ");
	scanf_s("%d", &height);

	//initialize global points
	m_offset.x = 0.0;
	m_offset.y = 0.0;
	m_offset.z = 0.0;

	trans.x = 0.0f;
	trans.y = 0.0f;
	trans.z = 0.0f;
	wrot.x = -45.0f;
	wrot.y = 0.0f;
	wrot.z = 0.0f;

	src.x = -0.5;
	src.y = -0.5;
	src.z = 1;
	gunbox_orig1 = { .5f, .5f, 2 };
	gunbox_orig2 = {-.5f, -.5f, 2};
	gunbox_view1 = { .75f, .75f, 1 };
	gunbox_view2 = { -.75f, -.75f, 1 };

	int i;
	int j;
	p_ray_src = (Pointf **)malloc(width * sizeof(Pointf *));
	d_ray_src = (Pointf **)malloc(width * sizeof(Pointf *));
	for (i = 0; i < width; i++)
	{
		p_ray_src[i] = (Pointf *)malloc(height * sizeof(Pointf));
		d_ray_src[i] = (Pointf *)malloc(height * sizeof(Pointf));
	}

	//define poly's in room
	poly_count = 2;
	poly_list = (Pointf **)malloc(poly_count * sizeof(Pointf *));
	for (i = 0; i < poly_count; i++)
		poly_list[i] = (Pointf *)malloc(3 * sizeof(Pointf));
	poly_list[0][0] = { 1,1,0 };
	poly_list[0][1] = { 1,-1,0 };
	poly_list[0][2] = { -1,-1,0 };
	poly_list[1][0] = { -1,1,-1 };
	poly_list[1][1] = { 1.0f,1,0 };
	poly_list[1][2] = { -1,-1.0f,0 };

	define_raybox();

	//build glut window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(win_height, win_width);
	glutCreateWindow("raytrace");

	glMatrixMode(GL_PROJECTION);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);

	//end init

	glutDisplayFunc(disp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	//glutKeyboardFunc(keyboard);


	//run the glut main loop.
	glutMainLoop();
}

