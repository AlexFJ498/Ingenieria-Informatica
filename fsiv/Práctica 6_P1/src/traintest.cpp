//! \file traintest.cpp
//! \author FSIV

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include "common_code.hpp"
#include "lbp.h"


using namespace std;
using namespace cv::ml;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@train_pos     |<none>| positive samples for training.}"
    "{@train_neg     |<none>| negative samples for training.}"
    "{@test_pos      |<none>| positive samples for testing.}"
    "{@test_neg      |<none>| negative samples for testing.}"    
    "{notrain        |      | no training a model? Only testing.}"
    "{model          |model_svm.yml| filename for model.}"    
    ;

int
main(int argc, char * argv[])
{
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Train/test a pedestrian classifier using LBP as feature.");
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    setvbuf(stdout, NULL, _IONBF, 0);


    bool notraining = parser.has("notrain");

    // Load sample names
    std::vector<std::string> lfiles_pos, lfiles_neg, lfiles_pos_test, lfiles_neg_test;
    cv::String filepath, filepath_neg , filepath_pos_test , filepath_neg_test;

    if (notraining)
    {
    	filepath_pos_test  = parser.get<cv::String>(0);
    	filepath_neg_test  = parser.get<cv::String>(1);        
    }
    else
    {
    	filepath = parser.get<cv::String>(0);
    	filepath_neg  = parser.get<cv::String>(1);    	
        filepath_pos_test  = parser.get<cv::String>(2);
        filepath_neg_test  = parser.get<cv::String>(3);
    }


	int retCode = -1;
    if (!notraining)
    {
    
		retCode = load_filenames_from_txt(filepath, lfiles_pos);	 
		if (retCode != 0)
		{
			 std::cerr << "Error loading filenames from: " << filepath << std::endl;
			 exit(-1);
		}
		 
		retCode = load_filenames_from_txt(filepath_neg, lfiles_neg);	 
		if (retCode != 0)
		{
			 std::cerr << "Error loading filenames from: " << filepath_neg << std::endl;
			 exit(-1);
		}	 
	}

	retCode = load_filenames_from_txt(filepath_neg_test, lfiles_neg_test);	 
	if (retCode != 0)
	{
		 std::cerr << "Error loading filenames from: " << filepath_neg_test << std::endl;
		 exit(-1);
	}	 

	retCode = load_filenames_from_txt(filepath_pos_test, lfiles_pos_test);	 
	if (retCode != 0)
	{
		 std::cerr << "Error loading filenames from: " << filepath_pos_test << std::endl;
		 exit(-1);
	}	 	 
	 
	 std::cout << lfiles_pos.size() << " positive training samples" << std::endl;
	 std::cout << lfiles_neg.size() << " negative training samples" << std::endl;

	 // Split image into cells to compute LBP full descriptor
	 int ncells[] = {6,4}; // Rows x cols // 6x4
	 cv::Mat train_lbp_pos, train_lbp_neg;

	/// Training a new model?    
   string modelname = parser.get<std::string>("model");
   if (!notraining)
   {
	   /// LBP
	   std::cout << "Computing LBP descriptors for training samples... ";
	   std::vector<float> train_labels_v;
	   int npos = compute_lbp_from_list(lfiles_pos, train_lbp_pos, ncells, true, true);
	   
	   int nneg = compute_lbp_from_list(lfiles_neg, train_lbp_neg, ncells, true, true);
	   
	   std::cout << "done!" << std::endl;
	   
	   for (int i =0; i<npos; i++)
	      train_labels_v.push_back(1);
	   for (int i =0; i<nneg; i++)
	      train_labels_v.push_back(-1);
	      
	   cv::Mat labelsMat(npos+nneg, 1, CV_32SC1);
	   for (int i =0; i < train_labels_v.size(); i++)
	      labelsMat.at<int32_t>(i,0) = train_labels_v[i];
	   
	   cv::Mat train_labels(train_labels_v);
	   cv::Mat train_lbp;
	   cv::vconcat(train_lbp_pos, train_lbp_neg, train_lbp);
	   
	   // TODO: create and configure your classifier      	   
	   // ...

	   CV_Assert(train_lbp.type()==CV_32F);
	   
	   std::cout << "Starting training ...";

	   // TODO: Start training	   
	   // ...
	   
	   
	   std::cout << "Trained" << std::endl;

	   // TODO: Save model to disk
  		// ...
	   // svm->save(modelname);
	}
	else
	{
		// TODO: load existing model
		// ...
		
		std::cout << "+ Model loaded from: " << modelname << std::endl;
	}

   
   /// Test time!
   cv::Mat test_lbp_pos, test_lbp_neg;
   std::cout << "Computing LBP on test samples..." << std::endl;
   int npos_test = compute_lbp_from_list(lfiles_pos_test, test_lbp_pos, ncells, true, true);   
   int nneg_test = compute_lbp_from_list(lfiles_neg_test, test_lbp_neg, ncells, true, true);

   cv::Mat predictions_pos, predictions_neg, predictions_pos_raw, predictions_neg_raw;

   // TODO: run the trained model on the LBP descriptors, positive and negative samples
   // ...
   	
	std::cout << "Test done!" << std::endl;

	cv::Mat true_labels(npos_test+nneg_test, 1, CV_32F);
	cv::Mat predicted_labels(npos_test+nneg_test, 1, CV_32F);

	for (int i = 0; i < npos_test; i++)
	{
		true_labels.at<float>(i,0) = +1;
		predicted_labels.at<float>(i,0) = MAX(0, predictions_pos.at<float>(i,0)); 
	}

	for (int i = 0; i < nneg_test; i++)
	{
		true_labels.at<float>(npos_test+i,0) = 0;
		predicted_labels.at<float>(npos_test+i,0) = MAX(0, predictions_neg.at<float>(i,0)); 
	} 

	// Some statistics about performance
	cv::Mat CM = compute_confusion_matrix(2, true_labels, predicted_labels);

	std::cout << CM << std::endl;

    double mean, dev;
	compute_recognition_rate(CM, mean, dev);

	std::cout << "Accuracy: " << mean << " (" << dev << ")" << std::endl;
	
	std::cout << "End! " <<std::endl;
   
   return 0;
}
