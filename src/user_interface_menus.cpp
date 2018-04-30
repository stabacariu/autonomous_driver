/**
 * @file user_interface_menus.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.7.2017
 */

#include "user_interface_menus.hpp"

void getMainMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(A)utonomous");
    menuList.push_back("(R)emote Control");
    menuList.push_back("(C)onfigure");
    menuList.push_back("(S)About");
    menuList.push_back("(Q)uit");
}

void getAutoMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(Q)uit");
}

void getAutoStateList (std::vector<std::string>& stateList, VehicleData& vehicle)
{
    stateList.clear();
    std::ostringstream text;
    
    text << "Steering: " << vehicle.getSteering() << " rad";
    stateList.push_back(text.str());
    text.str("");
    text.clear();
    text << "Acceleration: " << vehicle.getAcceleration() << " %";
    stateList.push_back(text.str());
    text.str("");
    text.clear();
}

void getAutoDetectList (std::vector<std::string>& detectList, LaneData& lane, ObstacleData& obstacle)
{
    detectList.clear();
    std::ostringstream text;
    cv::Vec4i leftLine = cvtRoadMarkingToVec4i(lane.getLeftLine());
    cv::Vec4i rightLine = cvtRoadMarkingToVec4i(lane.getRightLine());
    
    text << "Lane:";
    detectList.push_back(text.str());
    text.str("");
    text.clear();
    //~ if (lane.size() > 0) {
        //~ text << "L: [" << leftLine[0] << "," << leftLine[1] << "][" << leftLine[2] << "," << leftLine[3] << "]";
    //~ }
    //~ else {
        //~ text << "No lane found...";
    //~ }
    text << "L: [" << leftLine[0] << "," << leftLine[1] << "][" << leftLine[2] << "," << leftLine[3] << "]";
    detectList.push_back(text.str());
    text.str("");
    text.clear();
    //~ if (lane.size() > 0) {
        //~ text << "R: [" << rightLine[0] << "," << rightLine[1] << "][" << rightLine[2] << "," << rightLine[3] << "]";
    //~ }
    //~ else {
        //~ text << "No lane found...";
    //~ }
    text << "R: [" << rightLine[0] << "," << rightLine[1] << "][" << rightLine[2] << "," << rightLine[3] << "]";
    detectList.push_back(text.str());
    text.str("");
    text.clear();
    
    text << "Obstacle: ";
    if (obstacle.getDistance() > (-1)) {
        text << obstacle.getDistance() << " cm";
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

void getRcMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(A)utonomous");
    menuList.push_back("(Q)uit");
}

void getConfigMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(R)eset");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}

void getConfigModeList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(I)ntrinsics");
    menuList.push_back("(E)xtrinsics");
    menuList.push_back("(P)osition image");
}

void getCalibIntrinsicsMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(R)eset");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}

void getCalibExtrinsicsMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(R)eset");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}

void getPositionImageMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(R)eset");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}

void getAboutMenuList (std::vector<std::string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(Q)uit");
}

void getAboutTextList (std::vector<std::string>& textList)
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

void drawMainMenu (cv::Mat& image)
{
    // Draw a side bar
    cv::Point pt1(0, 0);
    cv::Point pt2(200, image.size().height-1);
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
    // Configure text
    std::string titleText = "menu";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 1;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(titleText, fontFace, fontScale, thickness, &baseline);
    
    // Get center of the text
    cv::Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    
    std::vector<std::string> menuList;
    getMainMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_PLAIN;
    fontScale = 1;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        std::string text = menuList[i];
        textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness);
    }
}

void drawAutoMode (cv::Mat& image, VehicleData& vehicle, LaneData& lane, ObstacleData& obstacle)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
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

void drawRcCom (cv::Mat& image, cv::Point position)
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

void drawRcMode (cv::Mat& image, VehicleData& vehicle)
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
}

void drawConfigMode (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
    std::string titleText = "Config mode";
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
    getConfigMenuList(menuList);
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
    
    menuList;
    getConfigModeList(menuList);
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

void drawCalibIntrinsics (cv::Mat& image)
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
    getCalibIntrinsicsMenuList(menuList);
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

void drawCalibExtrinsics (cv::Mat& image)
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
    getCalibExtrinsicsMenuList(menuList);
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

void drawPositionImage (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, cv::Scalar(218, 218, 218), -1);
    
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
    getPositionImageMenuList(menuList);
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

void drawAboutText (cv::Mat& image)
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

void drawAboutMode (cv::Mat& image)
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

void drawErrorMode (cv::Mat& image)
{
    cv::Point pt1(0, 0);
    cv::Point pt2(200, (image.size().height-1));
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
