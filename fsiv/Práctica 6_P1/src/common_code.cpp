//! \file common_code.cpp
//! \author FSIV

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include "common_code.hpp"
#include "lbp.h"

int compute_lbp_from_list(const std::vector<std::string> & lfiles, cv::Mat & train_lbp, const int * ncells, const bool normalize, const bool asrows, const bool withmirror)
{
	
	 	 
  for (int fix =0; fix < lfiles.size(); fix++)
  {
		 
	  auto imagePath = lfiles[fix].c_str();

    // TODO: compute LBP descriptor for current image and add to output matrix
	
	}
	
	return 0;

}

int load_filenames_from_txt(const std::string &filepath, std::vector<std::string> & lfiles)
{
	std::ifstream in (filepath);
	int retCode = 0;

   if (!in)
       retCode = 1;
   else
   {
       while((in) && (retCode==0) )
       {
           std::string sample;
           
           in >> sample;
           if (!in)
           {
               if (! in.eof())
                retCode = 2;
           }
           else
           {
               lfiles.push_back(sample);
               //std::cout <<                sample << std::endl;
           }
       }
   }
   return retCode;    
      
}


cv::Mat compute_confusion_matrix(int n_categories, const cv::Mat& true_labels, const cv::Mat& predicted_labels)
{
    CV_Assert(true_labels.rows == predicted_labels.rows);
    CV_Assert(true_labels.type()==CV_32FC1);
    CV_Assert(predicted_labels.type()==CV_32FC1);
    cv::Mat confussion_mat = cv::Mat::zeros(n_categories, n_categories, CV_32F);
    for (int i = 0; i < true_labels.rows; ++i)
    {
        confussion_mat.at<float>(true_labels.at<float>(i), predicted_labels.at<float>(i)) += 1.0;
    }
    return confussion_mat;
}


void compute_recognition_rate(const cv::Mat& cmat, double& mean, double& dev)
{
    CV_Assert(cmat.rows == cmat.cols && cmat.rows>1);
    CV_Assert(cmat.depth()==CV_32F);

    mean = 0.0;
    dev = 0.0;
    for (int c=0; c<cmat.rows; ++c)
    {
        const double class_Rate = cmat.at<float>(c,c)/cv::sum(cmat.row(c))[0];
        mean += class_Rate;
        dev += class_Rate*class_Rate;
    }
    mean /= double(cmat.rows);
    dev = sqrt(dev/double(cmat.rows) - mean*mean);
}


double
compute_intersection_over_union(const cv::Rect& boxA, const cv::Rect& boxB)
{
    const int xA = std::max(boxA.x, boxB.x);
    const int yA = std::max(boxA.y, boxB.y);
    const int xB = std::min(boxA.x+boxA.width-1, boxB.x+boxB.width-1);
    const int yB = std::min(boxA.y+boxA.height-1, boxB.y+boxB.height-1);

    // compute the area of intersection rectangle
    const int interArea = std::max(0, xB - xA + 1) * std::max(0, yB - yA + 1);

    // compute the intersection over union by taking the intersection
    // area and dividing it by the sum of prediction + ground-truth
    // areas - the interesection area
    return static_cast<double>(interArea) /
            static_cast<double>(boxA.area() + boxB.area() - interArea);
}


void compute_tp_fp(const std::vector<cv::Rect>& gt,
                   const std::vector<cv::Rect>& pred, float iou_th,
                   int& tp, int& fp)
{
    tp = 0;
    fp = pred.size();
    for (size_t i=0;i<gt.size();++i)
    {
        for (size_t j=0; j<pred.size(); ++j)
            if (compute_intersection_over_union(gt[i], pred[j])>= iou_th)
            {
                tp += 1;
                fp --;
                break; //we want only one match gt <-> pred.
            }
        if (fp==0)
            break; //There is none prediction to match with.
    }
}

bool read_INRIA_annotations(const std::string& filename,
                            std::vector<cv::Rect>& annotated_boxes)
{
    std::ifstream f (filename);
    bool retVal = false;
    if (f)
    {
        while (f && !retVal)
        {
            float xc, yc, w, h;
            std::string type;
            f >> xc >> yc >> w >> h >> type;
            if (f.eof())
                retVal=true;
            else if (f)
                annotated_boxes.push_back(cv::Rect(xc-w/2.0+0.5, yc-h/2.0+0.5, w, h));
        }
    }
    return retVal;
}

/// Extra functions

void basename(const std::string& path,
                     std::string& dirname,
                     std::string& filename,
                     std::string& ext)
{
    dirname="";
    filename=path;
    ext="";

    auto pos = path.rfind("/");

    if (pos != std::string::npos)
    {
      dirname=path.substr(0, pos);
      filename=path.substr(pos+1);
    }

    pos = filename.rfind(".");

    if (pos != std::string::npos)
    {
      ext = filename.substr(pos+1);
      filename = filename.substr(0,pos);
    }
    return;
}


void random_sampling (int total, int ntrain, int ntest,
                      std::vector< int >& train_samples,
                      std::vector< int >& test_samples)
{
    assert(ntrain<total);
    train_samples.resize(0);
    test_samples.resize(0);
    std::vector<bool> sampled(total, false);
    while (ntrain>0)
    {
        int s = int(double(total) * rand()/(RAND_MAX+1.0));
        int i=0;
        while(sampled[i] && i<sampled.size()) ++i; //the first unsampled.
        int c=0;
        while (c<s) //count s unsampled.
        {
            while (sampled[++i]); //advance to next unsampled.
            ++c;
        }
        assert(!sampled[i]);
        train_samples.push_back(i+1);
        sampled[i]=true;
        --total;
        --ntrain;
    }
    if (ntest>=total)
    {
        for (size_t i=0 ; i<sampled.size(); ++i)
            if (!sampled[i])
                train_samples.push_back(i);
    }
    else
    {
        while (ntest>0)
        {
            int s = int(double(total) * rand()/(RAND_MAX+1.0));
            int i=0;
            while(sampled[i] && i<sampled.size()) ++i; //the first unsampled.
            int c=0;
            while (c<s) //count s unsampled.
            {
                while (sampled[++i]); //advance to next unsampled.
                ++c;
            }
            test_samples.push_back(i+1);
            sampled[i]=true;
            --total;
            --ntest;
        }
    }
}
