//! \file common_code.hpp
//! \author FSIV

#ifndef __COMMON_CODE_HPP__
#define __COMMON_CODE_HPP__

#include <string>
#include <utility>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

/*!
  \brief Compute a confusion matrix
*/
cv::Mat compute_confusion_matrix(int n_categories, const cv::Mat& true_labels, const cv::Mat& predicted_labels);

/*!
  \brief Given a confusion matrix, compute accuracy
*/
void compute_recognition_rate(const cv::Mat& cmat, double& mean, double& dev);


/*!
  \brief Given a txt file with a path per file, load it into a vector
  \param[in]  filepath Path to input txt file
  \param[out] lfiles Output vector with elements read from the input file
*/
int load_filenames_from_txt(const std::string &filepath, std::vector<std::string> & lfiles);

/*!
  \brief Reads images given in lfiles and compute their LBP descriptor, storing all into matrix train_lbp (one per row)
  \param[in]  lfiles list of file paths
  \param[out] train_lbp output matrix with computed descriptors
  \param[in]  ncells E.g. [6,4]
  \param[in]  normalize to normalize output descriptors
  \param[in]  asrows each row of train_lbp is a descriptor
  \param[in]  withmirror to compute descriptor of mirror images as well
  \return     Number of samples in output matrix
*/
int compute_lbp_from_list(const std::vector<std::string> & lfiles, cv::Mat & train_lbp, const int * ncells, const bool normalize=true, const bool asrows=true, const bool withmirror=false);

/*!
  @brief Compute the IoU measure given two rectangles.

  For more details, see
  https://www.pyimagesearch.com/2016/11/07/intersection-over-union-iou-for-object-detection/

  @param[in] boxA,
  @param[in] boxB are the rectangles to use.
  @return the Interesection over Union measure.
*/
double
compute_intersection_over_union(const cv::Rect& boxA, const cv::Rect& boxB);

/*!
  \brief compute number of True positives and false positives.
  \param[in] gt is a vector with the ground truth boxes.
  \param[in] pred is a vector with the predicted boxes.
  \param[in] iou_th is the Intersection over Union threshold to consider a correct match.
  \param[out] tp is the number of true positives.
  \param[out] fp is the number of false negatives.
*/
void compute_tp_fp(const std::vector<cv::Rect>& gt,
                   const std::vector<cv::Rect>& pred,
                   const float iou_th,
                   int& tp, int& fp);
/**!
 * \brief read annotated boxes from a INRIA annotation file.
 * \param[in] filename.
 * \param[out] annotated_boxes is the vector with the annotated_boxes.
 * \return false if the file could not be parsed.
 */
bool read_INRIA_annotations(const std::string& filename,
                            std::vector<cv::Rect>& annotated_boxes);


#endif //__COMMON_CODE_HPP__
