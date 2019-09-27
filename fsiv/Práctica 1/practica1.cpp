#include <iostream>
#include <exception>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{path           |.     | path to file         }"
    "{fps            | -1.0 | fps for output video }"
    "{N count        |100   | count of objects     }"
    "{ts timestamp   |      | use time stamp       }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    "{@repeat        |1     | number               }"
    ;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//Rectangle values
Rect cropRect(0,0,0,0);

Mat final,mask;
Mat src,src_grey,img,ROI;
Point P1(0,0);
Point P2(0,0);
Point Paux(0,0);
vector<Point> pp1;
int i=0;
const char* winName="Image";
bool clicked=false;
char imgName[15];
bool mode = true; /*true -> rectangle || false -> polygone*/
int var = 0;
int drag = 0;
double contorno;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void changePolyColor(){
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			Paux.x=j;
			Paux.y=i;
			contorno=pointPolygonTest(pp1,Paux,false);
			if(contorno<0){
				Vec3b grey = img.at<Vec3b>(i,j);
					img.at<Vec3b>(i,j)[0] = grey.val[0]*0.114+grey.val[1]*0.587+grey.val[2]*0.299;
					img.at<Vec3b>(i,j)[1] = grey.val[0]*0.114+grey.val[1]*0.587+grey.val[2]*0.299;
					img.at<Vec3b>(i,j)[2] = grey.val[0]*0.114+grey.val[1]*0.587+grey.val[2]*0.299;
			}
		}
	}
}

void changeColor(){
	if(!(cropRect.width==0 && cropRect.height == 0)){
		//Color changes only when an rectangle exists
		for(int i=0; i<img.rows; i++){
			for(int j=0; j<img.cols;j++){
				Paux.x=j;
				Paux.y=i;
				if(!cropRect.contains(Paux)){
					//Pixels that are inside the rectangle doesn't change color
					Vec3b grey = img.at<Vec3b>(i,j);
					img.at<Vec3b>(i,j)[0] = grey.val[0]*0.114+grey.val[1]*0.587+grey.val[2]*0.299;
					img.at<Vec3b>(i,j)[1] = grey.val[0]*0.114+grey.val[1]*0.587+grey.val[2]*0.299;
					img.at<Vec3b>(i,j)[2] = grey.val[0]*0.114+grey.val[1]*0.587+grey.val[2]*0.299;
				}
			}
		}
	}
}	

void checkBoundary(){
	//check croping rectangle exceed image boundary
    if(cropRect.width>img.cols-cropRect.x)
		cropRect.width=img.cols-cropRect.x;

    if(cropRect.height>img.rows-cropRect.y)
    	cropRect.height=img.rows-cropRect.y;
}

void showImage(){
    img=src.clone();
    checkBoundary();

    if(cropRect.width>0 && cropRect.height>0){
        ROI=src(cropRect);
    }

	if(mode){
		rectangle(img, cropRect, Scalar(0,200,0), 0, 8, 0 );
		changeColor();
    	imshow(winName,img);
	}
}


void onMouse( int event, int x, int y, int f, void* ){
	switch(event){
    	case CV_EVENT_LBUTTONDOWN:
			if(mode == false){
				if (var == 0){
                	img = src.clone();
				}

				Paux = Point(x,y);
           	 	circle(img, Paux, 2, Scalar(0, 200, 0), -1, 8, 0);
           	 	pp1.push_back(Paux);
           	 	var++;
           	 	drag=1;

            	if (var>1){
                	line(img,pp1[var-2], Paux, Scalar(0, 200, 0), 2, 8, 0);
				}

            	imshow(winName, img);
			}else{
	        	clicked=true;
    	        P1.x=x;
    	        P1.y=y;
    	        P2.x=x;
    	        P2.y=y;
			}			
            break;

		case CV_EVENT_RBUTTONDOWN:
			if(mode == false){
    		    img = src.clone();
    	    	if (var != 0){
    	    	    polylines( img, pp1, 1, Scalar(0,200,0), 2, 8, 0);
    	    	}
    	    //	imshow("Source", img);
			}
			break;

		case CV_EVENT_RBUTTONUP:
			if(mode == false){
	 	       ROI = Mat::zeros(src.size(), CV_8UC3);
    		    mask = Mat::zeros(src.size(), CV_8UC1);
    	    vector<vector<Point> > vpts;
    		    vpts.push_back(pp1);
    		    fillPoly(mask, vpts, Scalar(255, 255, 255), 8, 0);
    		    bitwise_and(src, src, ROI, mask);
				changePolyColor();
    	    	imshow(winName, img);
			}
			break;

        case CV_EVENT_LBUTTONUP:
			if(mode == false){
				imshow(winName, img);
			}else{
	            P2.x=x;
    	        P2.y=y;
    	        clicked=false;
			}
   	        break;

        case CV_EVENT_MOUSEMOVE:
            if(clicked){
  	         	P2.x=x;
               	P2.y=y;
            }
            break;

        default: break;
    }

	if(clicked){
    	if(P1.x>P2.x){
			if(P2.x<0){
				cropRect.x=0;
				cropRect.width=P1.x;
			}else{
				cropRect.x=P2.x;
    	        cropRect.width=P1.x-P2.x;
			} 
		}
        else{
			cropRect.x=P1.x;
    	    cropRect.width=P2.x-P1.x;

		}
        if(P1.y>P2.y){ 
			if(P2.y<0){
				cropRect.y=0;
				cropRect.height=P1.y;
			}else{
			cropRect.y=P2.y;
            cropRect.height=P1.y-P2.y; 
			}
		}
        else{
	        cropRect.y=P1.y;
            cropRect.height=P2.y-P1.y; 
		}
    }

	if(mode)
		showImage();
}

int main(int argc, char* const* argv){
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
		cv::String img1 = parser.get<cv::String>(0);
		cv::String img2 = parser.get<cv::String>(1);
		int repeat = parser.get<int>(2);
        if (!parser.check()){
        	parser.printErrors();
            return 0;
        }
    	cout<<"Click and drag for Selection"<<endl<<endl;
    	cout<<"------> Press 's' to save"<<endl<<endl;
	
    	cout<<"------> Press '8' to move up"<<endl;
    	cout<<"------> Press '2' to move down"<<endl;
    	cout<<"------> Press '6' to move right"<<endl;
    	cout<<"------> Press '4' to move left"<<endl<<endl;

    	cout<<"------> Press 'w' increas top"<<endl;
    	cout<<"------> Press 'x' increas bottom"<<endl;
    	cout<<"------> Press 'd' increas right"<<endl;
    	cout<<"------> Press 'a' increas left"<<endl<<endl;

    	cout<<"------> Press 't' decrease top"<<endl;
    	cout<<"------> Press 'b' decrease bottom"<<endl;
    	cout<<"------> Press 'h' decrease right"<<endl;
    	cout<<"------> Press 'f' decrease left"<<endl<<endl;

		cout<<"------> Press 'q' to change mode"<<endl<<endl;	
    	cout<<"------> Press 'r' to reset"<<endl;
    	cout<<"------> Press 'Esc' to quit"<<endl<<endl;
	
		//Read image
    	src=imread(img1,1);
	
		//Create window and set mouse 
    	namedWindow(winName,WINDOW_NORMAL);
    	setMouseCallback(winName,onMouse,NULL);
    	imshow(winName,src);
	
    	while(1){
 			char c=waitKey();
    		if(c=='s'&&ROI.data){
    			sprintf(imgName,"%s",argv[2]);
    			imwrite(imgName,ROI);
    			cout<<"  Saved "<<imgName<<endl;
    		}
    		if(c=='6') cropRect.x++;
    		if(c=='4') cropRect.x--;
    		if(c=='8') cropRect.y--;
    		if(c=='2') cropRect.y++;
		
    		if(c=='w') { if(!(cropRect.y==0)){
							cropRect.y--; cropRect.height++;}
					   }
    		if(c=='d') cropRect.width++;
    		if(c=='x') cropRect.height++;
    		if(c=='a') { if(!cropRect.x==0){
							cropRect.x--; cropRect.width++;}
					   }
		
    		if(c=='t') { cropRect.y++; cropRect.height--;}
    		if(c=='h') cropRect.width--;
    		if(c=='b') cropRect.height--;
    		if(c=='f') { cropRect.x++; cropRect.width--;}
		
    		if(c==27) break;
    		if(c=='r'){
				cropRect.x=0;cropRect.y=0;cropRect.width=0;cropRect.height=0;
					pp1.clear();
					var = 0;
					drag = 0;		
			}
    		showImage();
			if(c=='q') {
				if(mode){
					mode = false;
					std::cout<<"Mode set to polygone"<<std::endl;
					pp1.clear();
					var = 0;
					drag = 0;
				}
				else{
					mode = true;
					std::cout<<"Mode set to rectangle"<<std::endl;
					cropRect.x=0;cropRect.y=0;cropRect.width=0;cropRect.height=0;
				}
			}
    	}
	
    	return 0;
	}
	catch (std::exception& e){
	    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
	    retCode = EXIT_FAILURE;
	}
	return retCode;
}
