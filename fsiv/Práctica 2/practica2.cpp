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
float c,b,g;
bool lumaValue = false;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
	"{i              |      | interactive mode     }"
    "{luma           |      | enable hsv option    }"
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
	salida = src.clone();
	
	cv::pow(src,g,salida);
	salida = c * salida + b;
	
}

void setLumaValues(float c, float b, float g){
	cvtColor(src,salida,CV_BGR2HSV);
	std::vector<cv::Mat> channels;
	split(salida,channels);
	for(int i=0;i<salida.rows;i++){
		for(int j=0;j<salida.cols;j++){
			Vec3f aux = salida.at<Vec3f>(i,j);
			salida.at<Vec3f>(i,j)[3] = c*(pow(aux[2],g)) + b;
		}
	}
	merge(channels,salida);
	cvtColor(salida,salida,CV_HSV2RGB);
	imshow("Image", salida);
}

void brightnessCallBack(int position, void *){
	b = (float)(position-100)/100;

	if(lumaValue){
		setLumaValues(c,b,g);
std::cout<<"hola\n";
	}
	else{
		  setPixelValues(c,b,g);
		//setVectorValues(c,b,g);
		imshow("Image", salida);
	}
}

void contrastCallBack(int position, void *){
	c = (float)position/100;

	if(lumaValue){
		setLumaValues(c,b,g);
	}
	else{
		  setPixelValues(c,b,g);
		//setVectorValues(c,b,g);
		imshow("Image", salida);
	}
}

void gammaCallBack(int position, void *){
	g = (float)position/100;

	if(lumaValue){
		setLumaValues(c,b,g);
	}
	else{
		  setPixelValues(c,b,g);
		//setVectorValues(c,b,g);
		imshow("Image", salida);
	}
}

void lumaCallBack(int position, void *){
	if(position == 0){
		lumaValue = false;
		  setPixelValues(c,b,g);
		//setVectorValues(c,b,g);
		imshow("Image", salida);
	}
	else{
		lumaValue = true;
		setLumaValues(c,b,g);
	}
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

	  src.convertTo(src, CV_32F, 1.0/255.0, 0.0);

	  salida.convertTo(salida, CV_32F, 1.0/255.0, 0.0);

	//  setPixelValues(c,b,g);
	setVectorValues(c,b,g);

	//Create window
	  imshow("Image", salida);

	if(parser.has("i")){
		int brightInitial = b*100+100;
		int contrastInitial = c*100;
		int gammaInitial = g*100;

		createTrackbar("B","Image",&brightInitial,200,brightnessCallBack);
		createTrackbar("C","Image",&contrastInitial,200,contrastCallBack);
		createTrackbar("G","Image",&gammaInitial,200,gammaCallBack);
	}

	if(parser.has("luma")){
		createTrackbar("Luma","Image",0,1,lumaCallBack);
	}

	//Wait for any key press
	char k=waitKey();
	if(!(k==27) && salida.data){
				  salida.convertTo(salida, CV_8UC3, 255.0); 
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
