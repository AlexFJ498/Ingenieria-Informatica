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
	"{i              |      | interactive mode     }"
	"{luma           |      | enable hsv option    }"
	"{c              |      | border_type = 1      }"
    "{path           |.     | path to file         }"
    "{fps            | -1.0 | fps for output video }"
    "{N count        |100   | count of objects     }"
    "{ts timestamp   |      | use time stamp       }"
	"{f              |0     | tipe of filter       }"
	"{g              |1.0   | ganancia             }"
	"{s              |0.5   | sigma 1              }"
	"{S              |1.0   | sigma 2              }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    "{@repeat        |1     | number               }"
    ;

cv::Mat entrada;
float g,sigma1,sigma2;
int border_type = 0;
int tipo;
bool luma = false;

/*~~~~~~~~~~~~~~~~~~CREAR FILTRO~~~~~~~~~~~~~~~~~~*/
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


/*~~~~~~~~~~~~DIFERENCIA DE GAUSSIANOS~~~~~~~~~~~~*/
cv::Mat createGaussian(float sigma, int size){
	cv :: Mat kernel(size,size,CV_32FC1);
	const double pi = 3.141592653589;
	int valor=size/2;
	float sum=0.0;

	float s = 2.0 * sigma *sigma;
	 
    for(int x = -valor; x <= valor; x++){
        for(int y = -valor; y <= valor; y++){
            kernel.at<float>(x + valor,y + valor)=(exp(-(x * x + y * y) / s)) / (pi * s);
            sum +=kernel.at<float>(x + valor,y + valor);
        }
    }
	kernel /= sum;
	return kernel;
}
cv::Mat create_DoG_filter(float sigma1=0.5 ,float sigma2=1.0, float g=1.0){
	int size = 2*sigma2 + 1 ;
	/*if(size%2 == 0){
		size--;
	}*/

	cv::Mat filter1 = createGaussian(sigma1,size);
	cv::Mat filter2 = createGaussian(sigma2,size);

	cv::Mat kernel(size,size,CV_32FC1);
	kernel = filter1 - filter2;
	int center = (kernel.rows - 1) / 2;

	kernel.at<float>(center,center) = g + kernel.at<float>(center,center);

	return kernel;
}


/*~~~~~~~~~~~~~~~~~~CONVOLUCIÓN~~~~~~~~~~~~~~~~~~~*/
void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0){
	assert(
		in.type() == CV_32FC1 && filter.type() == CV_32FC1
	);

	//matriz de zeros
	cv::Mat img_conv = cv::Mat::zeros(in.rows+filter.rows-1, 
										  in.cols+filter.cols-1, CV_32FC1);
	int border = (filter.rows-1)/2;
	for(int i=0;i<in.rows;i++){
		for(int j=0;j<in.cols;j++){
			img_conv.at<float>(i+border,j+border) = in.at<float>(i,j);
		}
	}

	//convolución circular
	if(border_type == 1){
		int modulo;
		for(int i=1;i<img_conv.rows;i++){
			for(int j=0;j<=img_conv.cols;j++){
				if(j<border){
					modulo = border - j;
					img_conv.at<float>(i,j) = img_conv.at<float>(i,img_conv.cols-modulo-1); 
				}else 
				if(j>in.cols){
					modulo = j - in.cols;
					img_conv.at<float>(i,j) = in.at<float>(i-1,modulo-1);
				}
			}
		}

		for(int j=0;j<=img_conv.cols;j++){
			for(int i=0;i<=img_conv.rows;i++){
				if(i<border){
					modulo = border - i;
					img_conv.at<float>(i,j) = img_conv.at<float>(img_conv.rows-modulo-1,j);
				}else 
				if(i>in.cols){
					modulo = i - in.rows;
					img_conv.at<float>(i,j) = in.at<float>(modulo-1,j-1);
				}
			}
		}
	}

	//convolución
	cv::Rect roi;
	cv::Mat cropped;
	out = in.clone();
	float sum;
	for(int i=border;i<in.rows;i++){
		for(int j=border;j<in.cols;j++){
			sum = 0;
			for(int u=-border;u<=border;u++){
				for(int v=-border;v<=border;v++){
					sum = sum + (img_conv.at<float>(i+u,j+v) * filter.at<float>(u+border, v+border));
					}
				}
				out.at<float>(i-border,j-border) = sum;
			}
		}
}

cv::Mat checkType(int tipo){
	cv::Mat kernel;
	if(tipo == 2){
		kernel = create_DoG_filter(sigma1,sigma2,g);
	}else if (tipo == 0 || tipo == 1){
		kernel = create_sharp_filter(tipo,g);
	}
	else{
		std::cout<<"Error: Valor incorrecto de -f"<<std::endl;
	}

	return kernel;
}

cv::Mat makeConvolution(const cv::Mat& entrada, const cv::Mat& kernel){
	cv::Mat entrada2;
	cv::Mat salida = entrada.clone();
	entrada.convertTo(entrada2,CV_32F, 1.0/255.0);

	std::vector<cv::Mat> canales;
	std::vector<cv::Mat> canales2;
	cv::split(entrada2,canales);

	for(int i=0;i<canales.size();i++){
		salida = cv::Mat();
		convolve(canales[i],kernel,salida,border_type);
		canales2.push_back(salida);
	}
	cv::merge(canales2,salida);

	cv::imshow("Realce", salida);

	return salida;
}

cv::Mat makeLumaConvolution(const cv::Mat& entrada, const cv::Mat& kernel){
	cv::Mat entrada2;
	cv::Mat salida = entrada.clone();
	entrada.convertTo(entrada2,CV_32F, 1.0/255.0);
	cvtColor(entrada2,entrada2,CV_BGR2HSV);

	std::vector<cv::Mat> canales;
	std::vector<cv::Mat> canales2;
	cv::split(entrada2,canales);

	convolve(canales[2],kernel,salida,border_type);
	canales2 = canales;
	canales2[2] = salida;

	cv::merge(canales2,salida);
	cvtColor(salida,salida,CV_HSV2BGR);
	cv::imshow("Realce", salida);

	return salida;
}

/*~~~~~~TRACKBARS~~~~~~*/
void tipoCallBack(int position, void *){
	tipo = position;
	cv::Mat kernel = checkType(tipo);

	if(luma){
		cv::Mat salida = makeLumaConvolution(entrada,kernel);
	}
	else{
		cv::Mat salida = makeConvolution(entrada,kernel);
	}
}

void gananciaCallBack(int position, void *){
	g = (float)position/10;
	cv::Mat kernel = checkType(tipo);
	
	if(luma){
		cv::Mat salida = makeLumaConvolution(entrada,kernel);
	}
	else{
		cv::Mat salida = makeConvolution(entrada,kernel);
	}
}

void lumaCallBack(int position, void *){
	cv::Mat kernel = checkType(tipo);
	luma = position;

	if(luma){
		cv::Mat salida = makeLumaConvolution(entrada,kernel);
	}
	else{
		cv::Mat salida = makeConvolution(entrada,kernel);
	}
}
/*~~~~~~~~~~~~~~~~~~~~~*/


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
	
	//Recoger datos
	tipo = parser.get<int>("f");
	g = parser.get<float>("g");
	sigma1 = parser.get<float>("s");
	sigma2 = parser.get<float>("S");

	cv::namedWindow("Realce",CV_WINDOW_NORMAL);

	//Tipo de borde
	if(parser.has("c")){
		border_type = 1;
	}

	//Modo HSV
	int lumaValue = 0;
	if(parser.has("luma")){
		luma = true;
		lumaValue = 1;
	}

	//Modo interactivo
	if(parser.has("i")){
		int g2 = g*10;
		cv::createTrackbar("Tipo","Realce",&tipo,2,tipoCallBack);
		cv::createTrackbar("Ganancia","Realce",&g2,100,gananciaCallBack);
		if(parser.has("i")){
			cv::createTrackbar("Luma","Realce",&lumaValue,1,lumaCallBack);
		}
	}

	//Convolución
    entrada = imread(img1);
	cv::Mat kernel= checkType(tipo);
	cv::Mat salida;

	if(luma){
		salida = makeLumaConvolution(entrada,kernel); 
	}
	else{
		salida = makeConvolution(entrada,kernel);
	}

	//Wait for any key press
	char k=cv::waitKey();
	if(!(k==27) && salida.data){
				  salida.convertTo(salida, CV_8UC3, 255.0); 
    			  imwrite(img2,salida);
    			std::cout<<"  Saved "<<img2<<std::endl;
	};

	//Destroy the window
	cv::destroyWindow("Realce");

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
