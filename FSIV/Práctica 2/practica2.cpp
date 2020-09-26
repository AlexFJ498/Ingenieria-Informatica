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

cv::Mat src, salida, mask;
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
    "{@image3        |""    | mask image           }"
    "{@repeat        |1     | number               }"
    ;

void setMask(){
	if(!mask.empty()){
		/*salida.convertTo(salida, CV_8UC3, 255.0); 
		salida_mask = Mat::zeros(salida.size(), CV_8UC3);
		mask = Mat::zeros(salida.size(), CV_8UC1);
		bitwise_and(salida,salida,salida_mask,mask);
		bitwise_or(salida_mask,src,salida);
	salida.convertTo(salida, CV_32F, 1.0/255.0, 0.0);
		*/
	
		for(int i=0;i<mask.rows;i++){
			for(int j=0;j<mask.cols;j++){
				Vec3f aux = mask.at<Vec3f>(i,j);
				if(aux[0] == 0 && aux[1] == 0 && aux[2] == 0){
					salida.at<Vec3f>(i,j) = src.at<Vec3f>(i,j);
				}
				else{
					salida.at<Vec3f>(i,j) = salida.at<Vec3f>(i,j);
				}
			}
		}

	}
	
}

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
	salida = src.clone();
	cvtColor(salida,salida,CV_BGR2HSV);
	for(int i=0;i<salida.rows;i++){
		for(int j=0;j<salida.cols;j++){
			salida.at<Vec3f>(i,j)[2] = c*(pow(salida.at<Vec3f>(i,j)[2],g)) + b;
		}
	}
	cvtColor(salida,salida,CV_HSV2BGR);
	setMask();
	imshow("Image", salida);
}

void brightnessCallBack(int position, void *){
	b = (float)(position-100)/100;

	if(lumaValue){
		setLumaValues(c,b,g);
	}
	else{
		  setPixelValues(c,b,g);
		//setVectorValues(c,b,g);
		setMask();
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
		setMask();
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
		setMask();
		imshow("Image", salida);
	}
}

void lumaCallBack(int position, void *){
	if(position == 0){
		lumaValue = false;
		  setPixelValues(c,b,g);
		//setVectorValues(c,b,g);
		setMask();
		imshow("Image", salida);
	}
	else{
		setMask();
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
	cv::String img3 = parser.get<cv::String>(2);
    int repeat = parser.get<int>(3);
    if (!parser.check()){
        parser.printErrors();
        return 0;
    }

	//Set mask
	if(!img3.empty()){
		mask = imread(img3);
	}

	//Set values
    src = imread(img1);
	src.convertTo(src, CV_32F, 1.0/255.0, 0.0);
	salida.convertTo(salida, CV_32F, 1.0/255.0, 0.0);
	mask.convertTo(mask, CV_32F, 1.0/255.0, 0.0);

	  setPixelValues(c,b,g);
	//setVectorValues(c,b,g);

	//Create window
	setMask();
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
