// Example : videoInput library alternative video example
// usage: prog 

// For use only on MS Windows with the videoInput Library
// Download http://muonics.net/school/spring05/videoInput/ 

// N.B. !!!!! TO USE THIS CODE !!!!!!!!!
//
// In Visual Studio in 
//
// 1. Copy videoInput.h from videoInput download to your project 
//    (use the correct version for your version of Visual Studio etc.)
//
// 2. Copy videoInput.lib to somewhere sensible (... /OpenCV/lib/ directory for example)
//    (use the correct version for your version of Visual Studio etc.)
//
// 3. Project Settings -> Linker ->Input 
//    3a. add videoInput.lib to "Additional dependencies:"  
//    3b. set "Ignore Specific Library:" to atlthunk.lib;LIBC.lib
//	(on some systems this may need to be chaned to  atlthunk.lib;LIBCMT.lib)
//
// 4. If the program does not run correctly from the Visual Studio play button 
//    (i.e. the green run button "|>") then try running it from the DOS command line.
//
// 5. To change/edit anything else about the camera capture - 
//    see the videoInput.h header file for further details

// Author : Toby Breckon, toby.breckon@cranfield.ac.uk
// (heavily based on code by Marcin Eichner, 2007/08)

// Copyright (c) 2010 School of Engineering, Cranfield University
// License : LGPL - http://www.gnu.org/licenses/lgpl.html

/******************************************************************************/
//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "videoInput.h" // video input library include file

//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
#include <vector>


//#include "cv.h"       // opencv general include file
//#include "highgui.h"  // opencv GUI include file

//#include "videoInput.h" // video input library include file

/******************************************************************************/

int main(int argc, char ** argv)
{
	videoInput::listDevices();		// get list of devices
	videoInput * vi = new videoInput();   	//required class to manage all the cameras
	vi->setupDevice(0);			// choose first device (device 0)

	static char * windowName = "videoInput Library Video Example"; // window name
	
	// if all is OK with device 0
	
 	if(vi->isDeviceSetup(0))
	{
		// create a window and an OpenCV image (assuming 8 bit, 3 channel image)
		
		cvNamedWindow(windowName, 1);
		IplImage* img = cvCreateImage(cvSize(vi->getWidth(0),vi->getHeight(0)),8, 3);

		// loop forever (or until we press "x" to break the loop)
		
		while(1)
		{
			// if we have a new frame on the camera buffer
			
			if(vi->isFrameNew(0))
			{
				// get the pixels from the image to the "imageData" of the OpenCV
				// image (here we assign it's an 8-bit 3 channel image
				
				// BGR order, flipped (=> do not requrie flipping or origin fixes)

				// N.B. This is a data "copy", see getPixels() doc. for info.

				vi->getPixels(0,(unsigned char*)img->imageData,false,true); 


				// !!! DO ALL OpenCV IMAGE PROCESSING HERE USING img AS INPUT
				// !!!
				// !!!
				
				// display the image in an OpenCV window
				
				cvShowImage(windowName,img);
				char key = cvWaitKey(1); // wait only for 1ms because we will 
							  // only refresh when we have a new frame

				// if the user presses "x" then break the loop and exit

				if(key == 'x')
				{
					break;
				}
			}
		}

		// release the allocated image (N.B. it is not deallocated by the video device)
		
		cvReleaseImage( &img );
	}

	// stop the video device
	
	vi->stopDevice(0);

	return 0;

}

/******************************************************************************/