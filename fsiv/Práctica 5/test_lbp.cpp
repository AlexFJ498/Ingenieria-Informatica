//! \file test_lbp.cpp
//! \author FSIV-UCO

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "lbp.h"

using namespace std;

const cv::String keys =
    "{help h usage ? |      | print this message.}"
//    "{u uniform      |      | use uLBP.}"
    "{c colunms      |      | Build descriptor using a grid with c colums.}"
    "{r rows         |      | Build descriptor using a grid with r rows.}"
    "{@image1        |<none>| path to input image.}"
    "{@image2        |      | path to second image, for comparison.}"
    ;

int main(int argc, char * argv[])
{
   cv::CommandLineParser parser(argc, argv, keys);
   parser.about("Test LBP implementation.");
   if (parser.has("help"))
   {
      parser.printMessage();
      return 0;
   }

   //Load the image1
    cv::Mat image1 = cv::imread(parser.get<cv::String>(0),0	);

   //Load the image2 (if it is set).
	cv::String nombre2 = parser.get<cv::String>(1);
    cv::Mat image2;

	if(!nombre2.empty()){
		image2 = cv::imread(nombre2,0);
	}
	//if image2 is not set, image2 = mirror(image1) (x axe). see cv::flip()	
	else{
		cv::flip(image1,image2,0);
	}

	float dist = 0.0;
	if(parser.has("c") && parser.has("r")){
		cv::Mat lbp_desc1 = image1.clone();
		cv::Mat lbp_desc2 = image2.clone();
		int ncells[2] = {0, 0}; 

		ncells[0] = parser.get<int>("c");
		ncells[1] = parser.get<int>("r");

		//Se realiza sobre la imagen1
		fsiv_lbp_desc(image1, lbp_desc1, ncells);
		fsiv_lbp_desc(image2, lbp_desc2, ncells);

		dist = fsiv_chisquared_dist(lbp_desc1,lbp_desc2);
	}
	else{
	   //Compute LBP matrixs
		cv::Mat lbp1 = image1.clone();
		cv::Mat lbp2 = image2.clone();

		fsiv_lbp(image1, lbp1);
		fsiv_lbp(image2, lbp2);

  	 	//Display LBP images
		fsiv_lbp_disp(lbp1, "lbp1");
   		fsiv_lbp_disp(lbp2, "lbp2");

	   //Compute the LBP histograms.
	    cv::Mat lbp_h1, lbp_h2;
		fsiv_lbp_hist(lbp1, lbp_h1);
		fsiv_lbp_hist(lbp2, lbp_h2);
	
	   //Compute the Chi^2 distance between the input image1 and image2, if it is set,
	   //or else between image1 and its mirror.
	
		dist = fsiv_chisquared_dist(lbp_h1, lbp_h2);
	}

   std::cerr << "Distance between image1, image2 = " << dist << std::endl;   
	std::cout << "End! " <<std::endl;
   
   return 0;
}
