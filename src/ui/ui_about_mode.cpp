/**
 * @file ui_about_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_about_mode.hpp"
#include "cvui.h"

void UIAboutMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("About", 0.6);
    cvui::space(5);
    
    if (cvui::button(140, 40, "&Back")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::endColumn();
    
    cvui::beginColumn(image, 200, 30, -1, -1, 3);
    cvui::text("Master Thesis Project");
    cvui::text("Autonomous Driver", 0.6);
    cvui::text("An Autonomous Driving Development Platform");
    cvui::text("by Sergiu-Petru Tabacariu");
    cvui::text("<sergiu.tabacariu@fh-campuswien.ac.at>");
    cvui::text("Date 1.5.2018");
    cvui::text("Version 1.0.0");
    cvui::endColumn();
}

//~ void UIAboutMode::draw (cv::Mat& image, char& selected)
//~ {
    //~ cv::Point pt1(0, 0);
    //~ cv::Point pt2(200, image.rows);
    //~ rectangle(image, pt1, pt2, cv::Scalar::all(218), -1);
    
    //~ std::string titleText = "About";
    //~ int fontFace = CV_FONT_HERSHEY_DUPLEX;
    //~ double fontScale = 0.7;
    //~ int thickness = 1;
    //~ int baseline = 0;
    //~ cv::Size textSize = cv::getTextSize(titleText, fontFace, fontScale, thickness, &baseline);
    
    //~ // Get center of the text
    //~ cv::Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    //~ putText(image, titleText, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    
    //~ std::vector<std::string> menuList;
    //~ getMenuList(menuList);
    //~ fontFace = CV_FONT_HERSHEY_PLAIN;
    //~ fontScale = 1;
    //~ textOrg.x = 10;
    //~ for (size_t i = 0; i < menuList.size(); i++) {
        //~ std::string text = menuList[i];
        //~ textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        //~ textOrg.y = textOrg.y + 15 + textSize.height;
        //~ putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    //~ }
    
    //~ cv::Mat textImage = cv::Mat(image.rows, image.cols - 200, CV_8UC3, cv::Scalar::all(0));
    //~ drawText(textImage);
    //~ cv::Rect insert = cv::Rect(200, 0, image.cols, image.rows);
    //~ textImage.copyTo(image(insert));
//~ }

//~ void UIAboutMode::drawText (cv::Mat& image)
//~ {
    //~ rectangle(image, cv::Point(0, 0), cv::Point(image.cols, image.rows), cv::Scalar::all(218), -1);
        
    //~ int fontFace = CV_FONT_HERSHEY_DUPLEX;
    //~ double fontScale = 0.7;
    //~ int thickness = 1;
    //~ int baseline = 0;
    
    //~ std::vector<std::string> textList;
    //~ getTextList(textList);
    //~ fontFace = CV_FONT_HERSHEY_PLAIN;
    //~ fontScale = 1;
    //~ cv::Point textOrg;
    //~ cv::Size textSize;
    //~ textOrg.x = 10;
    //~ textOrg.y = 0;
    //~ for (size_t i = 0; i < textList.size(); i++) {
        //~ std::string text = textList[i];
        //~ textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        //~ textOrg.y = textOrg.y + 15 + textSize.height;
        //~ putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    //~ }
//~ }

void UIAboutMode::getMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(Q)uit");
}

void UIAboutMode::getTextList (std::vector<std::string>& textList)
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
