//detector recieves a list of arrays and determines which points hit
#include <forward_list>
#include "XRay.h"
#include "AbstractPlane.h"
#include "TrianglePlane.cpp"

std::forward_list<XRay>** buckets;
Pointf** b_coords;
Pointf x_vector;
Pointf y_vector;
Pointf begin;
Pointf end;

//assuming arbitrary 3d points begin and end form a rectangle

//only collision upon the triangle defining the plane, not the whole plane itself :)
float ray_plane_collision(Pointf& const r_origin, Pointf& const r_direction, Pointf& const p_1, Pointf& const p_2, Pointf& const p_3)
{
	//you can actually just solve this by hand and plug in the values from there, but this is less time consuming for me and it is a prototype so w/e
	float matrix[3][4];
	int i;
	//set up matrix
	Pointf* temp;
	matrix[0][0] = p_2.getX() - p_1.getX();
	matrix[0][1] = p_3.getX() - p_1.getX();
	matrix[0][2] = -1 * r_direction.getX();
	matrix[0][3] = r_origin.getX() - p_1.getX();
	matrix[1][0] = p_2.getY() - p_1.getY();
	matrix[1][1] = p_3.getY() - p_1.getY();
	matrix[1][2] = -1 * r_direction.getY();
	matrix[1][3] = r_origin.getY() - p_1.getY();
	matrix[2][0] = p_2.getZ() - p_1.getZ();
	matrix[2][1] = p_3.getZ() - p_1.getZ();
	matrix[2][2] = -1 * r_direction.getZ();
	matrix[2][3] = r_origin.getZ() - p_1.getZ();
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

	//soln for t
	matrix[2][0] = (matrix[2][3] - matrix[1][3] * matrix[2][1] / matrix[1][1]) / (matrix[2][2] - matrix[1][2] * matrix[2][1] / matrix[1][1]);



	//solve beta
	matrix[1][0] = (matrix[1][3] - matrix[1][2] * (matrix[2][3] - matrix[1][3] * matrix[2][1] / matrix[1][1]) / (matrix[2][2] - matrix[1][2] * matrix[2][1] / matrix[1][1])) / matrix[1][1];


	//soln for alpha
	matrix[0][0] = matrix[0][3] - matrix[0][1] * matrix[1][0] - matrix[0][2] * matrix[2][0];

	if (matrix[1][0] < 0 || matrix[0][0] < 0 || matrix[0][0] + matrix[1][0] > 1) // fail, item outside of triangle
		return -1.0f;

	return matrix[2][0];
}


//fro now assuming that plate is square
int init_detector(int width, int height,Pointf &begin1, Pointf &end1, Pointf norm)
{
	int i;
	begin = begin1;
	end = end1;
	buckets = (std::forward_list<XRay>**)malloc(width * sizeof(std::forward_list<XRay> *));
	b_coords = (Pointf**)malloc(width * sizeof(Pointf *));
	for (i = 0; i < width; i++)
	{
		buckets[i] = (std::forward_list<XRay>*)malloc(height * sizeof(std::forward_list<XRay>));
		b_coords[i] = (Pointf*)malloc(height * sizeof(Pointf));
	}
	//compute normal and begin and ends normal.
	TrianglePlane normnorm = TrianglePlane(begin1, end1, norm);
	Pointf temp = normnorm.one();
	//normnorm = TrianglePlane(begin1, end1, );
	return 0;
}

//tests if ray intersects the detector then places it in the appropriate bucket should be to run in parrallel with a semaphore for each bucket
int test_ray(XRay &p)
{
	//test if p E detector
	
}



//helper function to manage parallel
int add_to_bucket(XRay &p, int x, int y)
{
	buckets[x][y].push_front(p);
}


int collect_rays(std::forward_list<XRay>)
{

}

