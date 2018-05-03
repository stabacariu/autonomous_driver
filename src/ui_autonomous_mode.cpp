/**
 * @file ui_autonomous_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_autonomous_mode.hpp"

//~ void UIAutonomousMode::draw (cv::Mat& image, VehicleData& vehicle, LaneData& lane, ObstacleData& obstacle)
void UIAutonomousMode::draw (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, image.rows);
    rectangle(image, pt1, pt2, cv::Scalar::all(218), -1);
    
    std::string titleText = "Auto mode";
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
    getAutoMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        std::string text = menuList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
    
    textOrg.y += 15;
    pt1 = cv::Point(0, textOrg.y);
    pt2 = cv::Point(200, pt1.y);
    line(image, pt1, pt2, cv::Scalar(180, 180, 180), 1);
    
    std::vector<std::string> stateList;
    getAutoStateList(stateList, vehicle);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < stateList.size(); i++) {
        std::string text = stateList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
    
    textOrg.y += 15;
    pt1 = cv::Point(0, textOrg.y);
    pt2 = cv::Point(200, pt1.y);
    line(image, pt1, pt2, cv::Scalar(180, 180, 180), 1);
    
    std::vector<std::string> detectList;
    getAutoDetectList(detectList, lane, obstacle);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < detectList.size(); i++) {
        std::string text = detectList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 15 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
}
void UIAutonomousMode::getAutoMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(Q)uit");
}

void UIAutonomousMode::getAutoStateList (std::vector<std::string>& stateList, VehicleData& v)
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

void UIAutonomousMode::getAutoDetectList (std::vector<std::string>& detectList, LaneData& l, ObstacleData& o)
{
    detectList.clear();
    std::ostringstream text;
    cv::Vec4i leftLine, rightLine;
    
    text << "Lane:";
    detectList.push_back(text.str());
    text.str("");
    text.clear();
    if (l.getLeftLine().size() > 0) {
        leftLine = cvtRoadMarkingToVec4i(l.getLeftLine());
        text << "L: [" << leftLine[0] << "," << leftLine[1] << "][" << leftLine[2] << "," << leftLine[3] << "]";
    }
    else {
        text << "No left line found.";
    }
    detectList.push_back(text.str());
    text.str("");
    text.clear();
    if (l.getRightLine().size() > 0) {
        rightLine = cvtRoadMarkingToVec4i(l.getRightLine());
        text << "R: [" << rightLine[0] << "," << rightLine[1] << "][" << rightLine[2] << "," << rightLine[3] << "]";
    }
    else {
        text << "No right line found.";
    }
    detectList.push_back(text.str());
    text.str("");
    text.clear();
    
    text << "Obstacle: ";
    if (o.getDistance() > (-1)) {
        text << o.getDistance() << " cm";
    }
    else {
        text << "No detection active!";
    }
    
    detectList.push_back(text.str());
    text.str("");
    text.clear();
    detectList.push_back("Signs: ");
    text.str("");
    text.clear();
}
