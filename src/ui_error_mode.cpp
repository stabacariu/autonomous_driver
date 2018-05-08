/**
 * @file ui_error_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_error_mode.hpp"

void UIErrorMode::draw (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, image.rows);
    rectangle(image, pt1, pt2, cv::Scalar(0, 0, 218), -1);
    
    std::string titleText = "Error";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(titleText, fontFace, fontScale, thickness, &baseline);
    cv::Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
}
