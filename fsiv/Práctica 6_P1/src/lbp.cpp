//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>

using namespace std;


void fsiv_lbp(const cv::Mat & imagem, cv::Mat & lbp)
{
	for(int i = 1; i < (imagem.rows-1); i++){
		for(int j=1;j<(imagem.cols-1);j++){
			int x = i; 
			int y = j; 

			unsigned char value = imagem.at<uchar>(x,y); 
			unsigned char aux; 
			unsigned char result = 0; 

			//Pixel 0
			aux = imagem.at<uchar>(x,y-1);
			if(aux > value)
				result = result | (1 << 7);
			else
				result = result | (0 << 7);

			//Pixel 1
			aux = imagem.at<uchar>(x+1,y-1);
			if(aux > value)
				result = result | (1 << 6);
			else
				result = result | (0 << 6);

			//Pixel 2
			aux = imagem.at<uchar>(x+1,y);
			if(aux > value)
				result = result | (1 << 5);
			else
				result = result | (0 << 5);

			//Pixel 3
			aux = imagem.at<uchar>(x+1,y+1);
			if(aux > value)
				result = result | (1 << 4);
			else
				result = result | (0 << 4);

			//Pixel 4
			aux = imagem.at<uchar>(x,y+1);
			if(aux > value)
				result = result | (1 << 3);
			else
				result = result | (0 << 3);

			//Pixel 5
			aux = imagem.at<uchar>(x-1,y+1);
			if(aux > value)
				result = result | (1 << 2);
			else
				result = result | (0 << 2);

			//Pixel 6
			aux = imagem.at<uchar>(x-1,y);
			if(aux > value)
				result = result | (1 << 1);
			else
				result = result | (0 << 1);

			//Pixel 7
			aux = imagem.at<uchar>(x-1,y-1);
			if(aux > value)
				result = result | (1 << 0);
			else
				result = result | (0 << 0);

			lbp.at<uchar>(x,y) = result;
		}
	}

	for(int i=0;i<imagem.rows;i++){
		lbp.at<uchar>(i,0) = 0;
		lbp.at<uchar>(i,lbp.cols-1) = 0;
	}
	for(int i=0;i<imagem.cols;i++){
		lbp.at<uchar>(0,i) = 0;
		lbp.at<uchar>(lbp.rows-1,i) = 0;
	}
}

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool normalize)
{	    
	int nbins = 256;
	lbp_hist == cv::Mat::zeros(1, nbins, CV_32FC1);

	float range[] = {0,256};
	const float* histRange = {range};

	calcHist(&lbp, 1, 0, cv::Mat(), lbp_hist, 1, &nbins, &histRange);

	//Normalizar
	if(normalize == true){
		float num = lbp.rows * lbp.cols;
		lbp_hist.convertTo(lbp_hist, CV_32FC1);
		for(int i = 0; i < nbins; i++){
			lbp_hist.at<float>(i) = (lbp_hist.at<float>(i)/num);
		}
	}

	lbp_hist = lbp_hist.t();	 
}

void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, bool asrows)
{
	int nbins = 256;
	int nx = ncells[0]; 
	int ny = ncells[1]; 
	vector <cv::Mat> vector;

	int rows = image.rows; 
	int cols = image.cols; 
	int c = cols/nx; 
	int r = rows/ny; 

	int numero = 0;
	for(int i = 1; i <= ny; i++){ 
		for(int j = 1; j <= nx; j++){ 
			numero += 1;

			int oldx = (j-1)*c;
			int oldy = (i-1)*r;
			int newx = j*c;
			int newy = i*r;
			int ccopy = c;
			int rcopy = r;

			if(j == nx)
				ccopy += cols%nx; 
			if(i == ny)
				rcopy += rows%ny; 

			cv::Rect rect(oldx, oldy, ccopy, rcopy);
			cv::Mat region = image(rect);
			cv::Mat aux = region.clone();
			cv::Mat lbpregion;

			fsiv_lbp(region, aux);
			lbpregion = aux.clone();
			fsiv_lbp_hist(aux, lbpregion, normalize);

			if(numero == 1)
				lbp_desc = lbpregion.clone();
			else
				hconcat(lbpregion, lbp_desc, lbp_desc);
		}
	}
}

void fsiv_lbp_disp(const cv::Mat & lbpmat, const std::string & winname)
{
	//show lbpmat.
	cv::imshow(winname,lbpmat);

	cv::waitKey(0);
}

float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
	 float dist= 0.0;
	//compute chi^2 distance. do not assume 256 bins allways!!
	float x,y,aux;

	for(int i=0;i<h1.cols;i++){
		x = (h1.at<float>(0,i) - h2.at<float>(0,i));
		aux = pow(x,2);

		x = aux;
		y = (h1.at<float>(0,i) + h2.at<float>(0,i));

		if(y == 0.0){
			dist+=0.0;
		}
		else{
			x = x/y;
			dist+=x;
		}
	}
	dist *=0.5;

    return dist;
}

