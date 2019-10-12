#include <iostream>
#include <exception>
#include <math.h> 

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

cv::Mat src, salida;
cv::Mat_<Vec3f> vecSrc;
cv::Mat_<Vec3f> vecSalida;
bool interactiveMode = false;
float c,b,g;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
	"{i              |      | interactive mode     }"
	"{c              |1.0   | contrast value       }"
	"{b              |0.0   | brightness value     }"
	"{g              |1.0   | gamma value          }"
    "{path           |.     | path to file         }"
    "{fps            | -1.0 | fps for output video }"
    "{N count        |100   | count of objects     }"
    "{ts timestamp   |      | use time stamp       }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    "{@repeat        |1     | number               }"
    ;

void setPixelValues(float c, float b, float g){
	salida = src.clone();
	for(int i=0;i<salida.rows;i++){
		for(int j=0;j<salida.cols;j++){
			Vec3f aux = salida.at<Vec3f>(i,j);
			for(int k=0;k<salida.channels();k++){
				salida.at<Vec3f>(i,j)[k] = c*(pow(aux[k],g)) + b;
			}
		}
	}
}

void setVectorValues(float c, float b, float g){
	vecSalida = vecSrc.clone();
	
	cv::pow(vecSrc,g,vecSalida);
	vecSalida *= c + b;
	
}

void brightnessCallBack(int position, void *){
	b = (float)(position-100)/100;

	//  setPixelValues(c,b,g);
	setVectorValues(c,b,g);

	//  imshow("Image", salida);
	imshow("Image", vecSalida);
}

void contrastCallBack(int position, void *){
	c = (float)position/100;

	//  setPixelValues(c,b,g);
	setVectorValues(c,b,g);

	//  imshow("Image", salida);
	imshow("Image", vecSalida);
}

void gammaCallBack(int position, void *){
	g = (float)position/100;

	//  setPixelValues(c,b,g);
	setVectorValues(c,b,g);

	//  imshow("Image", salida);
	imshow("Image", vecSalida);
}

int main (int argc, char* const* argv){
  int retCode=EXIT_SUCCESS;
  
  try {    
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Application name v1.0.0");
    if (parser.has("help")){
    	parser.printMessage();
        return 0;
    }
	if (parser.has("i")){
		interactiveMode = true;
	}
    int N = parser.get<int>("N");
    double fps = parser.get<double>("fps");
    cv::String path = parser.get<cv::String>("path");
    bool use_time_stamp = parser.has("timestamp");
	c = parser.get<float>("c");
	b = parser.get<float>("b");
	g = parser.get<float>("g");
    cv::String img1 = parser.get<cv::String>(0);
    cv::String img2 = parser.get<cv::String>(1);
    int repeat = parser.get<int>(2);
    if (!parser.check()){
        parser.printErrors();
        return 0;
    }

	//Set values
    src = imread(img1);

	//  src.convertTo(src, CV_32F, 1.0/255.0, 0.0);
	src.convertTo(vecSrc, CV_32F, 1.0/255.0, 0.0);

	//  salida.convertTo(salida, CV_32F, 1.0/255.0, 0.0);
	vecSalida.convertTo(vecSalida, CV_32F, 1.0/255.0, 0.0);

	//  setPixelValues(c,b,g);
	setVectorValues(c,b,g);

	//Create window
	//  imshow("Image", salida);
	imshow("Image", vecSalida);

	if(interactiveMode){
		int brightInitial = b*100+100;
		int contrastInitial = c*100;
		int gammaInitial = g*100;

		createTrackbar("brightness","Image",&brightInitial,200,brightnessCallBack);
		createTrackbar("contrast","Image",&contrastInitial,200,contrastCallBack);
		createTrackbar("gamma","Image",&gammaInitial,200,gammaCallBack);
	}

	//Wait for any key press
	char k=waitKey();
	if(!(k==27) && (salida.data || vecSalida.data)){
				//  salida.convertTo(salida, CV_8UC3, 255.0); 
				vecSalida.convertTo(salida, CV_8UC3, 255.0);
    			//  imwrite(img2,salida);
				imwrite(img2,salida);
    			cout<<"  Saved "<<img2<<endl;
	};

	//Destroy the window
	destroyWindow("Image");
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
