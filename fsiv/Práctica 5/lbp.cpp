//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>

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
    lbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
	//TODO compute lbp codes.
	
}

void fsiv_ulbp(const cv::Mat & imagem, cv::Mat & ulbp)
{
    ulbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
	//TODO compute u-LBP codes.
}

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool normalize, int nbins)
{	    
	 lbp_hist == cv::Mat::zeros(1, nbins, CV_32FC1);
    //TODO compute lbp hist. \see cv::calcHist. Establish the number of bins

    // Normalize?
    if (normalize)
    {
		//TODO normalize histogram to meet cv::sum(lbp_hist)[0] == 1.0
		;
    }
}

void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, int nbins)
{
	//TODO compute lbp desc.
    if (normalize)
    {
		//TODO normaliza lbp_desc to mett cv::sum(lbp_desc)[0] == 1.0
		;
    }
}

void fsiv_lbp_disp(const cv::Mat & lbpmat, const std::string & winname)
{
	//TODO show lbpmat.
	;
}

float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
	 float dist= 0.0;
	//TODO compute chi^2 distance. do not assume 256 bins allways!!
    return dist;
}

