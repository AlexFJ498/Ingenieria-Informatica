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

cv::Mat create_sharp_filter(int tipo, float g){
	cv::Mat kernel(3,3,CV_32FC1);
	if(tipo == 0){ //Laplaciano 5 puntos
		kernel.at<float>(0,0) = 0;
		kernel.at<float>(0,1) = -1;
		kernel.at<float>(0,2) = 0;
		kernel.at<float>(1,0) = -1;
		kernel.at<float>(1,1) = g+4;
		kernel.at<float>(1,2) = -1;
		kernel.at<float>(2,0) = 0;
		kernel.at<float>(2,1) = -1;
		kernel.at<float>(2,2) = 0;
	} 

	if(tipo == 1){ //Laplaciano 9 puntos
		kernel.at<float>(0,0) = -1;
		kernel.at<float>(0,1) = -1;
		kernel.at<float>(0,2) = -1;
		kernel.at<float>(1,0) = -1;
		kernel.at<float>(1,1) = g+8;
		kernel.at<float>(1,2) = -1;
		kernel.at<float>(2,0) = -1;
		kernel.at<float>(2,1) = -1;
		kernel.at<float>(2,2) = -1;
	}	
	return kernel;
}

void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0){
	assert(
		in.type() == CV_32FC1 && filter.type() == CV_32FC1
	);

	//cv::filter2D(in, out, in.depth(),filter);
	
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
	cv::Mat entrada2;
	cv::Mat kernel = create_sharp_filter(tipo,g);
	cv::Mat salida = entrada.clone();
	cv::Mat salida2;

	entrada.convertTo(entrada2,CV_32F, 1.0/255.0);

	std::vector<cv::Mat> canales;
	std::vector<cv::Mat> canales2;
	cv::split(entrada2,canales);

	for(int i=0;i<canales.size();i++){
		salida = cv::Mat();
		convolve(canales[i],kernel,salida);
		canales2.push_back(salida);
	}
	cv::merge(canales2,salida);

	cv::imshow("Image", entrada);
	cv::imshow("Realce", salida);

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
