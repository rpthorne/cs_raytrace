/****************************************************************
 *	DetectorPlate
 *
 *	 a detector plate is designed to capture XRays that collide
 * with it. any XRay that collides with a detector plate should be
 * captured by the detector plate, and cannot pass through, or
 * reflect/refract.
 *
 *	 the detector plate has a resolution describing the discrete
 * "pixels" that an XRay can hit on the detector. each pixel must
 * be capable of computing information based on all XRays that
 * intersect that particular pixel, produceable as a deplentry
 *
 *	 Additionally, detector plates should be able to support an add
 * operation that allows the combining of two separate detector
 * plates that have the same definitions (specifically, height and
 * width, but also expectedly the same size and position). this
 * feature is for parallelization of a single scene
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

//detector recieves a list of arrays and determines which points hit
#pragma once
#include "DetectorPlate.h"
#include <math.h>

//assuming fixed 2d points on a XYplane begin and end form a rectangle at depth begin.z

DetectorPlate::DetectorPlate() : DetectorPlate(Point(0, 0, 0), Point(0, 0, 0), 1, 1) {}

//for now assuming that plate is alligned to x-y plane along x and y
DetectorPlate::DetectorPlate(const Point &begin_, const Point &end_, int width_, int height_)
{
	int i, j;
	begin = begin_;
	end = end_;
	width = width_;
	height = height_;
	//no malloc calls :(
	buckets = new std::forward_list<XRay>[width * height];//(std::forward_list<XRay>**)malloc(width * sizeof(std::forward_list<XRay> *));
	bucket_coords = new RectPlane[width * height];// (RectPlane**)malloc(width * sizeof(RectPlane *) + width);
	
	detector_plane = RectPlane(begin, Point(end.getX(), begin.getY(), begin.getZ()), Point(begin.getX() ,end.getY(), begin.getZ()));
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
		{
			Point temp = begin + Vector(1,0,0).traverse(x_vector * i) + Vector(0,1,0).traverse(y_vector * j);
			bucket_coords[i * height + j] = RectPlane(temp, temp + Vector(1, 0, 0).traverse(x_vector * i), temp + Vector(1, 0, 0).traverse(x_vector * i));
		}
}

//helper function to manage parallel, this should be the only write section
int DetectorPlate::add_to_bucket(const XRay &p, int x, int y)
{
	buckets[x * height + y].push_front(p);
	return 0;// false on success
}

//tests if ray intersects the detector then places it in the appropriate bucket should be to run in parrallel with a semaphore for each bucket
int DetectorPlate::test_ray(XRay &p)
{
	//first ask if ray collides with detector
	float len;
	if ((len = detector_plane.ray_plane_collision(p)) >= 0)
		//determine if ray collision has alternate method with more infor
	{
		p.set_length(len);
		Point p_dest = p.get_src() + p.get_dir().traverse(len);
		add_to_bucket(p, (int)((begin.getX() - p_dest.getX()) * width / (begin.getX() - end.getX())), (int)((begin.getY() - p_dest.getY()) * height / (begin.getY() - end.getY())));
		return 0;
	}
	return -1; 
}

int DetectorPlate::collect_rays(deplentry** arr) const
{
	//create data table to hold information
	//deplentry*** arr;
	*arr = new deplentry[width * height];// = (deplentry**)malloc(width * (sizeof(deplentry)) + width);
	int i, j;
	//no enumerate each cell and data-ize it to the deplentry
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
		{
			(*arr)[i * height + j].num_hits = 0;
			(*arr)[i * height + j].simple_intensity = 0.0f;
			(*arr)[i * height + j].complex_intensity = 0.0f;
			(*arr)[i * height + j].intensity_dir = Vector(0, 0, 0);
			for (auto k = buckets[i * height + j].begin(); k != buckets[i * height + j].end(); k++)
			{
				Point temp = (*arr)[i * height + j].intensity_dir.traverse((*arr)[i * height + j].complex_intensity) + k->get_dir().traverse(k->get_intensity());
				(*arr)[i * height + j].complex_intensity = temp.get_magnitude();
				(*arr)[i * height + j].intensity_dir = Vector(temp);
				(*arr)[i * height + j].simple_intensity += k->get_intensity();
				(*arr)[i * height + j].num_hits++;
			}
		}
	return 0;//on success return false
}

