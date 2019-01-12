/*
 * data outputer
 * @author Ryan Thorne
 * @date 1/11
 * @description
 * the DataOutputer is a system to handle th I/) operation of writing data recieved from the simulation to an output file.
 * it directly handles deplentry's and formats the data in them as to be useable by some other program
*/

//default filename unles otherwise specified in the constructor is output.txt
#ifndef DEFAULT_FILE_NAME
#define DEFAULT_FILE_NAME "output.txt"
#endif

#pragma once
#include "DetectorPlate.h"
#include <fstream>
#include <iostream>

class DataOutputer
{
	char* filename;
public:
	DataOutputer()
	{
		filename = DEFAULT_FILE_NAME;
	}

	DataOutputer(char* file) {
		filename = file;
	}

	int output_results(deplentry** out, int width, int height)
	{
		std::ofstream ofs(filename, std::ofstream::out);

		//make sure file is properly opened
		if (!ofs.is_open())
		{
			std::cout << "could not open file";
			return -1;
		}

		int i = 0, j = 0;
		for (i = 0; i < width; i++)
		{
			//indicate row beginning
			ofs << "[\n";
			for (j = 0; j < height; j++)
			{
				//print a deplentry
				//this is an example until intensity and phase are properly implemented
				ofs << (*out)[i * height + j].complex_intensity << ",";
				ofs << (*out)[i * height + j].simple_intensity << ",";
				ofs << (*out)[i * height + j].num_hits << "";
				//indicate next entry
				ofs << std::endl;
			}
			//terminate row
			ofs << "]\n";
		}
		ofs.close();
		return 0;
	}

	char* get_file_name()
	{
		return filename;
	}

	~DataOutputer() {}

	
};