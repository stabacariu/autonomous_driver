/**
 * @file ui_about_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_about_mode.hpp"

void UIAboutMode::draw (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
    std::string titleText = "About";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(titleText, fontFace, fontScale, thickness, &baseline);
    
    // Get center of the text
    cv::Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    
    std::vector<std::string> menuList;
    getAboutMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        std::string text = menuList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
    drawAboutText(image);
}

void UIAboutMode::drawAboutText (cv::Mat& image)
{
    rectangle(image, cv::Point(0, 0), cv::Point(image.cols-1, image.rows-1), cv::Scalar(218, 218, 218), -1);
    
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    
    pt1.y += 25;
    pt1.x = 200/2 - 120/2;
    
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    
    std::vector<std::string> textList;
    getAboutTextList(textList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    cv::Point textOrg;
    cv::Size textSize;
    textOrg.x = 10;
    for (size_t i = 0; i < textList.size(); i++) {
        std::string text = textList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
}

void UIAboutMode::getAboutMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(Q)uit");
}

void UIAboutMode::getAboutTextList (std::vector<std::string>& textList)
{
    textList.clear();
    
    textList.push_back("Master Thesis Project");
    textList.push_back("Autonomous Driver");
    textList.push_back("An Autonomous Driving Development Platform");
    textList.push_back("by Sergiu-Petru Tabacariu");
    textList.push_back("<sergiu.tabacariu@fh-campuswien.ac.at>");
    textList.push_back("Date 1.5.2018");
    textList.push_back("Version 1.0.0");
    
}
