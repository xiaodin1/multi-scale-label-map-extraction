/*
------------------------------------------------------------------------------ -
MIT License

Copyright(c) 2016 Yale University

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

This is based on the source for the paper

"Multi-scale label-map extraction for texture synthesis"
in the ACM Transactions on Graphics(TOG) - Proceedings of ACM SIGGRAPH 2016,
Volume 35 Issue 4, July 2016
by
Lockerman, Y.D., Sauvage, B., Allegre,
R., Dischler, J.M., Dorsey, J.and Rushmeier, H.

http://graphics.cs.yale.edu/site/publications/multi-scale-label-map-extraction-texture-synthesis

If you find it useful, please consider giving us credit or citing our paper.
------------------------------------------------------------------------------ -

@author : Yitzchak David Lockerman

This is a simple program to demonstrate loading of HSLIC data. Given a label-map file and a scale 
it will output a ppm file with each superpixel given a random color.

Usage: 
      HSLIC_demo input_file.mat output_file.ppm scale
Where:
      input_file.mat is a label-map file
      output_file.ppm is the location to store the resulting image
      scale is the scale in pixels of the superpixels.

*/

#include "HSLIC.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "example_utils.h"

using namespace std;


int main(int argc, char* argv[])
{
	//Print somthing of a useful message if we get an exception
	try 
	{
		//If we don't have enough args, give the usage infomation 
		if (argc < 3)
		{
			cout << "Usage: " << argv[0] << " input_file.mat output_file.ppm scale" << endl
				<< "Will output a ppm file which indicates the superpixels at a given scale." << endl
				<< "The color will be chosen to make the image a little easier to read. However," << endl
				<< "note that the colors are arbitrary and useful for visualization only. " << endl;
			return 1;
		}

		//Load the values from the arguments
		string filename_in = argv[1];
		string filename_out = argv[2];
		float scale = stof(argv[3]);

		//Load the HSLIC file
		//Create a map to a blank image
		HierarchicalRegionMap<color> hslic = load_HLIC<color>(filename_in);

		output_PPM(filename_out, hslic.get_single_scale_map(scale));

	}
	catch (exception e)
	{
		cerr << "Error encounted: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "Error encounted!";
	}

}