/**
 * @file image_filter.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_filter.hpp"

using namespace std;
using namespace cv;

/**
 *  @brief This function adjusts the image brightness and contrast by spreeding the histogram
 *  @param image a image matrix
 *  @return void
 */
void autoAdjustImage (Mat& image)
{
    double minValue, maxValue;
    minMaxLoc(image, &minValue, &maxValue);
    double range = maxValue - minValue;
    double targetRange = 255;
    double alpha = targetRange/range;
    double beta = (-1) * minValue * alpha;
    image.convertTo(image, -1, alpha, beta);
}

/**
 *  @brief This function filters the white 'color' of an image
 *  @param image a input image matrix
 *  @param filteredImage a output image matrix
 *  @return void
 */
void whiteColorFilter (Mat image, Mat& filteredImage)
{
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    //autoAdjustImage(grayImage);
    threshold(grayImage, filteredImage, 240, 255, CV_THRESH_BINARY);
}

/**
 *  @brief This function filters the yellow color of an image
 *  @param image a input image matrix
 *  @param filteredImage a output image matrix
 *  @return void
 */
void yellowColorFilter (Mat image, Mat& filteredImage)
{
    Mat imageHSV;
    cvtColor(image, imageHSV, CV_BGR2HSV);
    inRange(imageHSV, Scalar(17, 76, 127), Scalar(30, 255, 255), filteredImage);
}
