#include <iostream>
#include <exception>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

const cv::String keys =
    "{help h usage ? |      | print this message        }"
	"{v              |      | renderice video option    }"
	"{i              |      | renderice video option    }"
    "{@rows          |      | calib. pattern rows       }"
    "{@cols          |      | calib. pattern cols.      }"
    "{@size          |      | calib. pattern cols size. }"
    "{@calibfile     |      | intrinsics file.          }"
    "{@input_file    |<none>| input video.              }"
	"{@image         |      | image for -i              }"
    ;

using namespace cv;
using namespace std;

void crearVerticesInput(std::vector<cv::Point3f> &vertices, int size, int cols, int rows){
	vertices.push_back(cv::Point3f(0,0,0));
	vertices.push_back(cv::Point3f(0,size*(rows-1),0));
	vertices.push_back(cv::Point3f(size*(cols-1),size*(rows-1),0));
	vertices.push_back(cv::Point3f(size*(cols-1),0,0));
}

void crearVerticesOutput(std::vector<cv::Point2f> &vertices, int cols, int rows){
	vertices.push_back(cv::Point2f(0,0));
	vertices.push_back(cv::Point2f(0,rows-1));
	vertices.push_back(cv::Point2f(cols-1,rows-1));
	vertices.push_back(cv::Point2f(cols-1,0));
}

void crearPuntos(std::vector<cv::Point3f> &puntos3d, int size){
	puntos3d.push_back(cv::Point3f(0,0,0));
	puntos3d.push_back(cv::Point3f(size,0,0));
	puntos3d.push_back(cv::Point3f(0,size,0));
	puntos3d.push_back(cv::Point3f(0,0,-size));
}

void dibujarEjesXYZ(cv::Mat frame, std::vector<cv::Point2f> puntosRespuesta){
	cv::line(frame, puntosRespuesta[0], puntosRespuesta[1], cv::Scalar(0,0,255), 6); //Azul
	cv::line(frame, puntosRespuesta[0], puntosRespuesta[2], cv::Scalar(0,255,0), 6); //Verde
	cv::line(frame, puntosRespuesta[0], puntosRespuesta[3], cv::Scalar(255,0,0), 6); //Rojo
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
      int rows = parser.get<int>(0);
      int cols = parser.get<int>(1);
      float size = parser.get<float>(2);
      cv::String calibfile = parser.get<String>(3);
      cv::String input_file = parser.get<String>(4);

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    //Abrir el vídeo
    VideoCapture vid;
    vid.open(input_file);
    if(! vid.isOpened()){
        cerr << "Error video."<<endl;
        return EXIT_FAILURE;
    }

	VideoCapture video;
	if(parser.has("v")){
		cv::String nombre = parser.get<cv::String>(5);
		video.open(nombre);
	}

	cv::Mat input;
	if(parser.has("i")){
		cv::String nombre = parser.get<cv::String>(5);
		input = cv::imread(nombre);
	}

    cv::FileStorage intr (calibfile, FileStorage::READ);
    if(!intr.isOpened()){
        cerr <<"Error calib." << endl;
        return EXIT_FAILURE;
    }

    cv::Mat camera_mat;
    cv::Mat dist_coefs;
    intr["camera_matrix"] >> camera_mat;
    intr["distorsion_coefficients"] >> dist_coefs;

	std::vector<Point3f> obj_pts;
	for(int i=0;i<rows-1;i++){
		for(int j=0;j<cols-1;j++){
			obj_pts.push_back(cv::Point3f(j*size,i*size,0));
		}
	}
	std::vector<Point2f> corners;
    int k = 0;
	cv::Mat frame;
	vid >> frame;

	if(parser.has("v"))
		video >> input;

    while(!frame.empty() && k != 27){
        //detectar el tablero
		cv::Mat gray;

        if(findChessboardCorners(frame, Size(cols-1,rows-1), corners,cv::CALIB_CB_FAST_CHECK)){
            cv::cvtColor(frame, gray, COLOR_BGR2GRAY);

			//refinar esquinas detectadas
            cv::cornerSubPix(gray, corners, Size(11,11), Size(-1,-1),
                             TermCriteria(cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03)));

			//Estimar orientación de la cámara
			cv::Mat rotation_vec, translation_vec;
            cv::solvePnP(obj_pts, corners, camera_mat, dist_coefs, rotation_vec, translation_vec);

			//Proyectar sobre la imagen información 3D
			if(parser.has("v") && !input.empty()){
				std::vector<cv::Point3f> vertices;
				std::vector<cv::Point2f> verticesInput;
				std::vector<cv::Point2f> verticesOutput;

				crearVerticesInput(vertices,size,cols-1,rows-1);
				cv::projectPoints(vertices, rotation_vec, translation_vec, camera_mat, dist_coefs,verticesInput);

				crearVerticesOutput(verticesOutput,frame.cols,frame.rows);

				cv::Mat matrix = cv::getPerspectiveTransform(verticesOutput,verticesInput);
				cv::warpPerspective(input,frame,matrix,frame.size(),1,cv::BORDER_TRANSPARENT);

				video >> input;
			}
			if(!parser.has("v")){
				if(parser.has("i")){
					std::vector<cv::Point3f> vertices;
					std::vector<cv::Point2f> verticesInput;
					std::vector<cv::Point2f> verticesOutput;
	
					crearVerticesInput(vertices,size,cols-1,rows-1);
					cv::projectPoints(vertices, rotation_vec, translation_vec, camera_mat, dist_coefs,verticesInput);
	
					crearVerticesOutput(verticesOutput,frame.cols,frame.rows);
	
					cv::Mat matrix = cv::getPerspectiveTransform(verticesOutput,verticesInput);
					cv::warpPerspective(input,frame,matrix,frame.size(),1,cv::BORDER_TRANSPARENT);
				}
				else{
					std::vector<cv::Point3f> puntos3d;
					std::vector<cv::Point2f> puntosResultado;
	
					crearPuntos(puntos3d,size);
					cv::projectPoints(puntos3d, rotation_vec, translation_vec, camera_mat, dist_coefs, puntosResultado);
					dibujarEjesXYZ(frame,puntosResultado);
				}
			}
		}
    	    
    	    cv::imshow("Video",frame);
			k = cv::waitKey(20);

		    vid >> frame;
    }

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
