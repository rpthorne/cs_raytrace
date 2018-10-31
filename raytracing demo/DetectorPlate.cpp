//detector recieves a list of arrays and determines which points hit
#include <forward_list>
#include "DetectorPlate.h"
#include "XRay.h"
#include "TrianglePlane.h"
#include "RectPlane.h"

//assuming arbitrary 3d points begin and end form a rectangle


//fro now assuming that plate is square
DetectorPlate::DetectorPlate(const Pointf &begin_, const Pointf &end_, const Pointf &direction, int width_, int height_)
{
	int i, j;
	begin = begin_;
	end = end_;
	width = width_;
	height = height_;
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
	y_vector = x_vector - normnorm.get_normal().scale_mul((x_vector - begin).magnitude_precise());
	x_vector = x_vector + normnorm.get_normal().scale_mul((x_vector - begin).magnitude_precise());
	detector_plane = RectPlane(begin, begin + x_vector, begin + y_vector);
	x_vector = x_vector.scale_div(width);
	y_vector = y_vector.scale_div(height);
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
		{
			Pointf temp = begin + x_vector.scale_mul(i) + y_vector.scale_mul(j);
			b_coords[i][j] = RectPlane(temp, temp + x_vector, temp + y_vector);
		}
}

//helper function to manage parallel, this should be the only write section
int DetectorPlate::add_to_bucket(const XRay &p, int x, int y)
{
	buckets[x][y].push_front(p);
	return 0;// false on success
}

//tests if ray intersects the detector then places it in the appropriate bucket should be to run in parrallel with a semaphore for each bucket
int DetectorPlate::test_ray(XRay &p)
{
	//first ask if ray collides with detector
	if (detector_plane.ray_plane_collision(p) >= 0)
		//determine if ray collision has alternate method with more infor
	{
		int i = 0, j = 0;
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

int DetectorPlate::collect_rays(std::forward_list<XRay>**) const
{
	return 0;//on success return false
}

