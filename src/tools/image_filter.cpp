/**
 * @file image_filter.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_filter.hpp"

void autoAdjustBrightness (cv::Mat& image)
{
    double minValue, maxValue;
    minMaxLoc(image, &minValue, &maxValue);
    double range = maxValue - minValue;
    double targetRange = 255;
    double alpha = targetRange/range;
    double beta = (-1) * minValue * alpha;
    image.convertTo(image, -1, alpha, beta);
    
    //~ cv::Mat yuvImage;
    //~ cvtColor(image, yuvImage, CV_BGR2YUV);
    //~ vector<cv::Mat> yuvChannels;
    //~ split(yuvImage, yuvChannels);
    //~ equalizeHist(yuvChannels[0], yuvChannels[0]);
    //~ merge(yuvChannels, yuvImage);
    //~ cvtColor(yuvImage, image, CV_YUV2BGR);
}

void whiteColorFilter (cv::Mat image, cv::Mat& filteredImage)
{
    //~ cv::Mat imageHLS;
    //~ cvtColor(image, imageHLS, CV_BGR2HLS);
    //~ inRange(imageHLS, cv::Scalar(175, 0, 0), cv::Scalar(180, 255, 255), filteredImage);
    //~ cvtColor(filteredImage, filteredImage, CV_HLS2BGR);
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    threshold(grayImage, filteredImage, 230, 255, CV_THRESH_BINARY); // lower threshold 235 - 240
}

void yellowColorFilter (cv::Mat image, cv::Mat& filteredImage)
{
    cv::Mat imageHSV;
    cvtColor(image, imageHSV, CV_BGR2HSV);
    inRange(imageHSV, cv::Scalar(17, 76, 127), cv::Scalar(30, 255, 255), filteredImage);
}
