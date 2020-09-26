//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>
#include <iostream>

using namespace std;

static const int uniform[256] =
{   
0,1,2,3,4,58,5,6,7,58,58,58,8,58,9,10,11,58,58,58,58,58,58,58,12,58,58,58,13,58,
14,15,16,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,17,58,58,58,58,58,58,58,18,
58,58,58,19,58,20,21,22,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,23,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,24,58,58,58,58,58,58,58,25,58,58,58,26,58,27,28,29,30,58,31,58,58,58,32,58,
58,58,58,58,58,58,33,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,34,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,35,36,37,58,38,58,58,58,39,58,58,58,58,58,58,58,40,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,41,42,43,58,44,58,58,58,45,58,58,58,58,58,58,58,46,47,48,58,49,
58,58,58,50,51,52,58,53,54,55,56,57
};

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
			result = result | uchar(value >= imagem.at<uchar>(x-1,y-1));

			//Pixel 1
			result <<=1;
			result = result | uchar(value >= imagem.at<uchar>(x-1,y));

			//Pixel 2
			result <<=1;
			result = result | uchar(value >= imagem.at<uchar>(x-1,y+1));

			//Pixel 3
			result <<=1;
			result = result | uchar(value >= imagem.at<uchar>(x,y+1));

			//Pixel 4
			result <<=1;
			result = result | uchar(value >= imagem.at<uchar>(x+1,y+1));

			//Pixel 5
			result <<=1;
			result = result | uchar(value >= imagem.at<uchar>(x+1,y));

			//Pixel 6
			result <<=1;
			result = result | uchar(value >= imagem.at<uchar>(x+1,y-1));

			//Pixel 7
			result <<=1;
			result = result | uchar(value >= imagem.at<uchar>(x,y-1));

/*
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
*/
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

void fsiv_ulbp(const cv::Mat & imagem, cv::Mat & ulbp)
{
    ulbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
	//TODO compute u-LBP codes.
}

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool normalize, int nbins)
{	    
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

	lbp_hist = lbp_hist.reshape(0,1);
}

void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, int nbins)
{
	int nx = ncells[0]; 
	int ny = ncells[1]; 

	int ancho = image.cols/ny;
	int alto = image.rows/nx;

	//Tendremos nx*ny histogramas de nbins flotantes

	lbp_desc = cv::Mat(nx*ny,nbins,CV_32FC1);

	//Calculamos el lbp de toda la imagen de una vez para ir más rápido

	cv::Mat lbp = image.clone();

	fsiv_lbp(image, lbp);

	int fila = 0;
	for(int i = 0; i < nx; i++){ 
		for(int j = 0; j < ny; j++){ 
			cv::Mat region = lbp(cv::Rect(j*ancho,i*alto,ancho,alto));							
			cv::Mat lbpregion;

			fsiv_lbp_hist(region, lbpregion, normalize, nbins);
			lbpregion.copyTo(lbp_desc.row(fila));
			fila++;
		}
	}

	lbp_desc.reshape(0, 1); //ahora lo ponemos todo como una sola fila
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

