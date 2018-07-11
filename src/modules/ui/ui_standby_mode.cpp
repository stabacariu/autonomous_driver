/**
 * @file ui_standby_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "cvui.h"
#include "ui_standby_mode.hpp"

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

void UIStandbyMode::draw (cv::Mat& image)
{
    cvui::text(image, 10, 10, "Main Menu");
    
    cvui::button(image, 10, 30, 150, 40, "&Autonomous");
    cvui::button(image, 10, 80, 150, 40, "&Remote Control");
    cvui::button(image, 10, 130, 150, 40, "&Configuration");
    cvui::button(image, 10, 180, 150, 40, "&About");
    cvui::button(image, 10, 230, 150, 40, "&Quit");
}

void UIStandbyMode::getMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(A)utonomous");
    menuList.push_back("(R)emote Control");
    menuList.push_back("(C)onfigure");
    menuList.push_back("(S)About");
    menuList.push_back("(Q)uit");
}

