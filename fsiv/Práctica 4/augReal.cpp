#include <iostream>
#include <exception>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@rows        |<none>| calib. pattern rows  }"
    "{@cols        |<none>| calib. pattern cols. }"
    "{@size        |<none>| calib. pattern cols size.}"
    "{@calibfile   |<none>| intrinsics file.     }"
    "{@input       |<none>| input video.         }"
    ;

using namespace cv;
using namespace std;

void crearPuntos(std::vector<cv::Point3f> &puntos3d, int size){
	puntos3d.push_back(cv::Point3f(0,0,0));
	puntos3d.push_back(cv::Point3f(size,0,0));
	puntos3d.push_back(cv::Point3f(0,size,0));
	puntos3d.push_back(cv::Point3f(0,0,-size));
}

void dibujarEjesXYZ(){

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
      int rows = parser.get<int>(1);
      int cols = parser.get<int>(2);
      float size = parser.get<float>(3);
      String calibfile = parser.get<String>(4);
      String input_file = parser.get<String>(5);

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    //Abrir el vídeo
    VideoCapture vid;
    vid.open(input_file, FileStorage::READ);
    if(! vid.isOpened()){
        cerr << "Error video."<<endl;
        return EXIT_FAILURE;
    }

    cv::FileStorage intr (calibfile, FileStorage::READ);
    if(!intr.isOpened()){
        cerr <<"Error calib." << endl;
        return EXIT_FAILURE;
    }

    cv::Mat camera_mat;
    cv::Mat dist_coefs;
    intr["camera-matrix"] >> camera_mat;
    intr["distorsion-coefficients"] >> dist_coefs;

    cv::Mat frame;

    vid >> frame;

    int k = 0;
    while(!frame.empty() && k != 27){
        //detectar el tablero
		cv::Mat gray;
		std::vector<Point3f> obj_pts = create obj_points();
	    std::vector<Point2f> corners;
        cv::imshow("Video",frame);
        if(findChessboardCorners(frame, Size(cols-1,rows-1), corners)){
            cv::cvtColor(frame, gray, COLOR_BGR2GRAY);

			//refinar esquinas detectadas
            cv::cornerSubPix(gray, corners, Size(11,11), Size(-1,-1),
                             TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

			//Estimar orientación de la cámara
			cv::Mat rotation_vec, translation_vec;
            cv::solvePnP(obj_points, corners, camera_mat, dist_coefs, rotation_vec, translation_vec);

			//Proyectar sobre la imagen información 3D
			std::vector<cv::Point3f> puntos3d;
			std::vector<cv::Point2f> puntosResultado;

			crearPuntos(puntos3d,size);
			cv::projectPoints(puntos3d, rotation_vec, translation_vec, camera_mat, dist_coefs, puntosResultado);
			cv::dibujarEjesXYZ(frame,puntosResultado);
        }
    }

    //Wait for any key press
    cv::waitKey(0);

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
parametro C hace referencia al kernel Chi2
