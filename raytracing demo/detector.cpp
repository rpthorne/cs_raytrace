//detector recieves a list of arrays and determines which points hit
#include <forward_list>
#include "XRay.h"
#include "TrianglePlane.h"
#include "RectPlane.h"

std::forward_list<XRay>** buckets;
RectPlane** b_coords;
RectPlane detector_plane;
Pointf x_vector;
Pointf y_vector;
Pointf begin;
Pointf end;
int width, height;


//assuming arbitrary 3d points begin and end form a rectangle


//fro now assuming that plate is square
int init_detector(int width1, int height1,Pointf &begin1, Pointf &end1, Pointf direction)
{
	int i, j;
	begin = begin1;
	end = end1;
	width = width1;
	height = height1;
	buckets = (std::forward_list<XRay>**)malloc(width * sizeof(std::forward_list<XRay> *));
	b_coords = (RectPlane**)malloc(width * sizeof(RectPlane *));
	for (i = 0; i < width; i++)
	{
		buckets[i] = (std::forward_list<XRay>*)malloc(height * sizeof(std::forward_list<XRay>));
		b_coords[i] = (RectPlane*)malloc(height * sizeof(RectPlane));
	}
	//compute normal and begin and ends normal.
	RectPlane normnorm = RectPlane(begin, end, direction);
	x_vector = (begin + end).scale_mul(.5f);
	y_vector = x_vector - normnorm.get_normal().scale_mul((x_vector - begin1).magnitude_precise());
	x_vector = x_vector + normnorm.get_normal().scale_mul((x_vector - begin1).magnitude_precise());
	detector_plane = RectPlane(begin, begin + x_vector, begin + y_vector);
	x_vector = x_vector.scale_div(width);
	y_vector = y_vector.scale_div(height);
	//change to squarePlane
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
		{
			Pointf temp = begin + x_vector.scale_mul(i) + y_vector.scale_mul(j);
			b_coords[i][j] = RectPlane(temp, temp + x_vector, temp + y_vector);
		}

	//normnorm = TrianglePlane(begin1, end1, );
	return 0;
}

//tests if ray intersects the detector then places it in the appropriate bucket should be to run in parrallel with a semaphore for each bucket
int test_ray(XRay &p)
{
	//first ask if ray collides with detector
	if (detector_plane.ray_plane_collision(p) >= 0)
		//determine if ray collision has alternate method with more infor
	{
		int i, j;
		float res = -1;
		for (int i = 0; i < width; i++)
		{
			for (j = 0; j < height; j++)
			{
				if ((res = b_coords[i][j].ray_plane_collision(p)) >= 0)
					break;
			}
			if (res >= 0) break;
		}
		add_to_bucket(p, i, j);
		return 0;
	}
	return -1; 
}



//helper function to manage parallel, this should be the only write section
int add_to_bucket(XRay &p, int x, int y)
{
	buckets[x][y].push_front(p);
	return 0;// false on success
}


int collect_rays(std::forward_list<XRay>)
{
	return 0;//on success return false
}

