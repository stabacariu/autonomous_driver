/**
 * @file ui_standby_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_standby_mode.hpp"
#include "cvui.h"

cv::Mat quitButton (int width, int height);

void UIStandbyMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Main Menu", 0.6);
    cvui::space(5);
    
    if (cvui::button(140, 40, "&Autonomous")) {
        selected = 'A';
    }
    if (cvui::button(140, 40, "&Development")) {
        selected = 'D';
    }
    if (cvui::button(140, 40, "&Remote Control")) {
        selected = 'R';
    }
    if (cvui::button(140, 40, "&Configuration")) {
        selected = 'C';
    }
    if (cvui::button(140, 40, "A&bout")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::endColumn();
}

cv::Mat quitButton (int width, int height)
{
    cv::Mat button = cv::Mat(height, width, CV_8UC3, cv::Scalar(0x29,0x29,0x29));
    cv::Rect theShape = cv::Rect(cv::Point(0,0), cv::Point((width), (height)));
    // Outline
    cv::rectangle(button, theShape, cv::Scalar(0x29, 0x29, 0x29));
    // Border
    theShape.x++; theShape.y++; theShape.width -= 2; theShape.height -= 2;
    cv::rectangle(button, theShape, cv::Scalar(0x4A, 0x4A, 0x4A));
    // Inside
    //~ theShape.x++; theShape.y++; theShape.width -= 2; theShape.height -= 2;
    //~ cv::rectangle(button, theShape, theState == OUT ? cv::Scalar(0x42, 0x42, 0x42) : (theState == OVER ? cv::Scalar(0x52, 0x52, 0x52) : cv::Scalar(0x32, 0x32, 0x32)), CVUI_FILLED);
    
    return button; 
}


//~ void UIStandbyMode::draw (cv::Mat& image)
//~ {
    //~ // Draw a side bar
    //~ cv::Point pt1(0, 0);
    //~ cv::Point pt2(200, image.size().height-1);
    //~ rectangle(image, pt1, pt2, cv::Scalar::all(218), -1);
    
    //~ // Configure text
    //~ std::string titleText = "menu";
    //~ int fontFace = CV_FONT_HERSHEY_DUPLEX;
    //~ double fontScale = 1;
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
        //~ textOrg.y = textOrg.y + 20 + textSize.height;
        //~ putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    //~ }
//~ }

//~ void UIStandbyMode::getMenuList (std::vector<std::string>& menuList)
//~ {
    //~ menuList.clear();
    
    //~ menuList.push_back("(A)utonomous");
    //~ menuList.push_back("(R)emote Control");
    //~ menuList.push_back("(C)onfigure");
    //~ menuList.push_back("(S)About");
    //~ menuList.push_back("(Q)uit");
//~ }

//~ void UIStandbyMode::getMenuList (std::vector<std::string>& menuList)
//~ {
    //~ menuList.clear();
    
    //~ menuList.push_back("(A)utonomous");
    //~ menuList.push_back("(D)evelopment");
    //~ menuList.push_back("(R)emote Control");
    //~ menuList.push_back("(C)onfigure");
    //~ menuList.push_back("A(B)out");
    //~ menuList.push_back("(Q)uit");
//~ }

