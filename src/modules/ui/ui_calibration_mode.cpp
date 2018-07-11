/**
 * @file ui_calibration_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_calibration_mode.hpp"

void UIIntrinsicsCalibrationMode::draw (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
    std::string titleText = "Calib Intr";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    cv::Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    
    std::vector<std::string> menuList;
    getMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        std::string text = menuList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
}

void UIIntrinsicsCalibrationMode::getMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(R)eset");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}

void UIExtrinsicsCalibrationMode::draw (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
    std::string titleText = "Calib Extr";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    cv::Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    
    std::vector<std::string> menuList;
    getMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        std::string text = menuList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
}

void UIExtrinsicsCalibrationMode::getMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(R)eset");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}

void UIImageAdjustmentMode::draw (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, image.rows);
    rectangle(image, pt1, pt2, cv::Scalar::all(218), -1);
    
    std::string titleText = "Position image";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    cv::Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    
    std::vector<std::string> menuList;
    getMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        std::string text = menuList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
}

void UIImageAdjustmentMode::getMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(R)eset");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}
