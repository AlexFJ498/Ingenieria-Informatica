#include <iostream>
#include <exception>
#include <assert.h>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{path           |.     | path to file         }"
    "{fps            | -1.0 | fps for output video }"
    "{N count        |100   | count of objects     }"
    "{ts timestamp   |      | use time stamp       }"
	"{f              |0     | tipe of filter       }"
	"{g              |1.0   | ganancia             }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    "{@repeat        |1     | number               }"
    ;

cv::Mat_<float> create_sharp_filter(int tipo, float g){
	cv::Mat_<float> kernel(3,3);
	if(tipo == 0){ //Laplaciano 5 puntos
		kernel << 0, -1, 0, -1, g+4, -1, 0, -1, 0;
	} 

	if(tipo == 1){ //Laplaciano 9 puntos
		kernel << -1, -1, -1, -1, g+9, -1, -1, -1, -1;
	}	
	return kernel;
}

void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0){
	assert(
		in.type() == CV_32FC1 && filter.type() == CV_32FC1
	);

	cv::filter2D(in, out, -1, filter,cv::Point(-1,-1),border_type);
	cv::addWeighted(in,1.0,out,1.0,0.0,out);
}

int main (int argc, char* const* argv){
  int retCode=EXIT_SUCCESS;
  
  try {    

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      int N = parser.get<int>("N");
      double fps = parser.get<double>("fps");
      cv::String path = parser.get<cv::String>("path");
      bool use_time_stamp = parser.has("timestamp");
      cv::String img1 = parser.get<cv::String>(0);
      cv::String img2 = parser.get<cv::String>(1);
      int repeat = parser.get<int>(2);
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }
	int tipo = parser.get<int>("f");
	int g = parser.get<float>("g");

    cv::Mat entrada = imread(img1);
	cv::Mat salida;
	cv::Mat_<float> kernel = create_sharp_filter(tipo,g);

	cv::imshow("Image", entrada);
	//cv::imshow("Laplace",kernel);
	cv::Mat entrada2;
	cvtColor(entrada, entrada, CV_BGR2GRAY,1);
	entrada.convertTo(entrada2,CV_32F);
	convolve(entrada2,kernel,salida);
	cvtColor(salida,salida,CV_GRAY2BGR);
	cv::imshow("convolve", salida);
	//Create window


	//Wait for any key press
	cv::waitKey(0);

	//Destroy the window
	cv::destroyWindow("Image");

    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
