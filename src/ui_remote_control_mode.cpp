/**
 * @file ui_remote_control_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_remote_control_mode.hpp"

//~ void UIRemoteControlMode::draw (cv::Mat& image, VehicleData& vehicle)
void UIRemoteControlMode::draw (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
    std::string titleText = "RC mode";
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
    getRcMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        std::string text = menuList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
    
    textOrg.y += 20;
    pt1 = cv::Point(0, textOrg.y);
    pt2 = cv::Point(200, pt1.y);
    line(image, pt1, pt2, cv::Scalar(180, 180, 180), 1);
    
    pt1.y += 25;
    pt1.x = 200/2 - 120/2;
    drawRcCom(image, pt1);
    
    textOrg.y += 20;
    pt1 = cv::Point(0, textOrg.y);
    pt2 = cv::Point(200, pt1.y);
    line(image, pt1, pt2, cv::Scalar(180, 180, 180), 1);
    
    std::vector<std::string> stateList;
    getRcStateList(stateList, vehicle);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < stateList.size(); i++) {
        std::string text = stateList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
}

void UIRemoteControlMode::drawRcCom (cv::Mat& image, cv::Point position)
{
    cv::Rect controls(position, cv::Size(120, 70));
    // Up arrow
    cv::Point pt1(controls.x + (controls.width/2-1)-15, controls.y + (controls.height/2-1)-35);
    cv::Point pt2(controls.x + (controls.width/2-1)+15, controls.y + (controls.height/2-1)-5);
    rectangle(image, pt1, pt2, cv::Scalar(180, 180, 180), -1);
    cv::Point textOrg(pt1.x, pt2.y);
    putText(image, "w", textOrg, CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(0), 1);
    // Down arrow
    pt1 = cv::Point(controls.x + (controls.width/2-1)-15, controls.y + (controls.height/2-1)+5);
    pt2 = cv::Point(controls.x + (controls.width/2-1)+15, controls.y + (controls.height/2-1)+35);
    rectangle(image, pt1, pt2, cv::Scalar(180, 180, 180), -1);
    textOrg = cv::Point(pt1.x, pt2.y);
    putText(image, "s", textOrg, CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(0), 1);
    // Left arrow
    pt1 = cv::Point(controls.x + (controls.width/2-1)-55, controls.y + (controls.height/2-1)-15);
    pt2 = cv::Point(controls.x + (controls.width/2-1)-25, controls.y + (controls.height/2-1)+15);
    rectangle(image, pt1, pt2, cv::Scalar(180, 180, 180), -1);
    textOrg = cv::Point(pt1.x, pt2.y);
    putText(image, "a", textOrg, CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(0), 1);
    // Right arrow
    pt1 = cv::Point(controls.x + (controls.width/2-1)+25, controls.y + (controls.height/2-1)-15);
    pt2 = cv::Point(controls.x + (controls.width/2-1)+55, controls.y + (controls.height/2-1)+15);
    rectangle(image, pt1, pt2, cv::Scalar(180, 180, 180), -1);
    textOrg = cv::Point(pt1.x, pt2.y);
    putText(image, "d", textOrg, CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(0), 1);
}

void UIRemoteControlMode::getRcMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(A)utonomous");
    menuList.push_back("(Q)uit");
}

void UIRemoteControlMode::getRcStateList (std::vector<std::string>& stateList, VehicleData& v)
{
    stateList.clear();
    std::ostringstream text;
    
    text << "Steering: " << v.getSteering() << " rad";
    stateList.push_back(text.str());
    text.str("");
    text.clear();
    text << "Acceleration: " << v.getAcceleration() << " %";
    stateList.push_back(text.str());
    text.str("");
    text.clear();
}
