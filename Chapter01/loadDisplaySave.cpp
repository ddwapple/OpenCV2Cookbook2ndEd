/*------------------------------------------------------------------------------------------*\
   This file contains material supporting chapter 1 of the cookbook:  
   Computer Vision Programming using the OpenCV Library 
   Second Edition 
   by Robert Laganiere, Packt Publishing, 2013.

   This program is free software; permission is hereby granted to use, copy, modify, 
   and distribute this source code, or portions thereof, for any purpose, without fee, 
   subject to the restriction that the copyright notice may not be removed 
   or altered from any source or altered source distribution. 
   The software is released on an as-is basis and without any warranties of any kind. 
   In particular, the software is not guaranteed to be fault-tolerant or free from failure. 
   The author disclaims all warranties with regard to this software, any use, 
   and any consequent failure, is purely the responsibility of the user.
 
   Copyright (C) 2013 Robert Laganiere, www.laganiere.name
\*------------------------------------------------------------------------------------------*/

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void onMouse( int event, int x, int y, int flags, void* param)	{
	
	cv::Mat *im= reinterpret_cast<cv::Mat*>(param);

    switch (event) {	// dispatch the event

		case CV_EVENT_LBUTTONDOWN: // mouse button down event

			// display pixel value at (x,y)
			std::cout << "at (" << x << "," << y << ") value is: " 
				      << static_cast<int>(im->at<uchar>(cv::Point(x,y))) << std::endl;
			break;
	}
}

void main() {

	cv::Mat image; // create an empty image
	std::cout << "This image is " << image.rows << " x " 
              << image.cols << std::endl;

	// read the input image as a gray-scale image
	image=  cv::imread("puppy.bmp", CV_LOAD_IMAGE_GRAYSCALE); 

	if (!image.data) {  // error handling
		// no image has been created�
		// possibly display an error message
		// and quit the application 
		std::cout << "Error reading image..." << std::endl;
		return;
	}

	std::cout << "This image is " << image.rows << " x " 
			  << image.cols << std::endl;
	std::cout << "This image has " 
              << image.channels() << " channel(s)" << std::endl; 

	// create image window named "My Image"
	cv::namedWindow("Original Image"); // define the window
	cv::imshow("Original Image", image); // show the image

	// set the mouse callback for this image
	cv::setMouseCallback("Original Image", onMouse, reinterpret_cast<void*>(&image));

	cv::Mat result; // we create another empty image
	cv::flip(image,result,1); // positive for horizontal
                          // 0 for vertical,                     
                          // negative for both

	cv::namedWindow("Output Image"); // the output window
	cv::imshow("Output Image", result);

	cv::waitKey(0); // 0 to indefinitely wait for a key pressed
                // specifying a positive value will wait for
                // the given amount of msec

	cv::imwrite("output.bmp", result); // save result

	return;
}
