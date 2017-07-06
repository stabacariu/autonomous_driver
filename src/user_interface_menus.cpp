/**
 * @file user_inteface_menus.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 4.7.2017
 */

#include "user_interface_menus.hpp"

using namespace std;
using namespace cv;

void getMainMenuList (vector<string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(A)utonomous");
    menuList.push_back("(R)emote Control");
    menuList.push_back("(D)evelop");
    menuList.push_back("(C)onfigure");
    menuList.push_back("(Q)uit");
}

void getAutoMenuList (vector<string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(S)top");
    menuList.push_back("(S)tart");
    menuList.push_back("(Q)uit");
}

void getAutoStateList (vector<string>& stateList)
{
    stateList.clear();
    
    stateList.push_back("Direction: ");
    stateList.push_back("Speed: ");
    stateList.push_back("Steering: ");
}

void getAutoDetectList (vector<string>& detectList)
{
    detectList.clear();
    
    detectList.push_back("Lines: ");
    detectList.push_back("Lane: ");
    detectList.push_back("Objects: ");
    detectList.push_back("Signs: ");
}

void getRcMenuList (vector<string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(A)utonomous");
    menuList.push_back("(Q)uit");
}

void getDevMenuList (vector<string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(A)utonomous");
    menuList.push_back("(S)creenshot");
    menuList.push_back("(C)alibrate");
    menuList.push_back("(Q)uit");
}

void getConfigMenuList (vector<string>& menuList)
{
    menuList.clear();
    
    menuList.push_back("(B)ack");
    menuList.push_back("(S)ave");
    menuList.push_back("(Q)uit");
}

void drawMainMenu (Mat& image)
{
    // Draw a side bar
    Point pt1(0, 0);
    Point pt2(200, image.size().height-1);
    rectangle(image, pt1, pt2, Scalar(218, 218, 218), -1);
    
    // Configure text
    string titleText = "menu";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 1;
    int thickness = 1;
    int baseline = 0;
    Size textSize = getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    
    vector<string> menuList;
    getMainMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_SIMPLEX;
    fontScale = 0.5;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        string text = menuList[i];
        textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    }
}

void drawAutoMode (Mat& image)
{
    Point pt1(0, 0);
    Point pt2(200, (image.size().height-1));
    rectangle(image, pt1, pt2, Scalar(218, 218, 218), -1);
    
    string titleText = "Auto mode";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    Size textSize = getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    
    vector<string> menuList;
    getAutoMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_SIMPLEX;
    fontScale = 0.5;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        string text = menuList[i];
        textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    }
    
    textOrg.y += 20;
    pt1 = Point(0, textOrg.y);
    pt2 = Point(200, pt1.y);
    line(image, pt1, pt2, Scalar(180, 180, 180), 1);
    
    vector<string> stateList;
    getAutoStateList(stateList);
    fontFace = CV_FONT_HERSHEY_SIMPLEX;
    fontScale = 0.5;
    textOrg.x = 10;
    for (size_t i = 0; i < stateList.size(); i++) {
        string text = stateList[i];
        textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    }
    
    textOrg.y += 20;
    pt1 = Point(0, textOrg.y);
    pt2 = Point(200, pt1.y);
    line(image, pt1, pt2, Scalar(180, 180, 180), 1);
    
    vector<string> detectList;
    getAutoDetectList(detectList);
    fontFace = CV_FONT_HERSHEY_SIMPLEX;
    fontScale = 0.5;
    textOrg.x = 10;
    for (size_t i = 0; i < detectList.size(); i++) {
        string text = detectList[i];
        textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    }
}

void drawRcCom (Mat& image, Point position)
{
    Rect controls(position, Size(120, 70));
    // Up arrow
    Point pt1(controls.x + (controls.width/2-1)-15, controls.y + (controls.height/2-1)-35);
    Point pt2(controls.x + (controls.width/2-1)+15, controls.y + (controls.height/2-1)-5);
    rectangle(image, pt1, pt2, Scalar(180, 180, 180), -1);
    Point textOrg(pt1.x, pt2.y);
    putText(image, "<UP>", textOrg, CV_FONT_HERSHEY_PLAIN, 0.5, Scalar::all(0), 1);
    // Down arrow
    pt1 = Point(controls.x + (controls.width/2-1)-15, controls.y + (controls.height/2-1)+5);
    pt2 = Point(controls.x + (controls.width/2-1)+15, controls.y + (controls.height/2-1)+35);
    rectangle(image, pt1, pt2, Scalar(180, 180, 180), -1);
    textOrg = Point(pt1.x, pt2.y);
    putText(image, "<DOWN>", textOrg, CV_FONT_HERSHEY_PLAIN, 0.5, Scalar::all(0), 1);
    // Left arrow
    pt1 = Point(controls.x + (controls.width/2-1)-55, controls.y + (controls.height/2-1)-15);
    pt2 = Point(controls.x + (controls.width/2-1)-25, controls.y + (controls.height/2-1)+15);
    rectangle(image, pt1, pt2, Scalar(180, 180, 180), -1);
    textOrg = Point(pt1.x, pt2.y);
    putText(image, "<LEFT>", textOrg, CV_FONT_HERSHEY_PLAIN, 0.5, Scalar::all(0), 1);
    // Right arrow
    pt1 = Point(controls.x + (controls.width/2-1)+25, controls.y + (controls.height/2-1)-15);
    pt2 = Point(controls.x + (controls.width/2-1)+55, controls.y + (controls.height/2-1)+15);
    rectangle(image, pt1, pt2, Scalar(180, 180, 180), -1);
    textOrg = Point(pt1.x, pt2.y);
    putText(image, "<RIGHT>", textOrg, CV_FONT_HERSHEY_PLAIN, 0.5, Scalar::all(0), 1);
}

void drawRcMode (Mat& image)
{
    Point pt1(0, 0);
    Point pt2(200, (image.size().height-1)/2);
    rectangle(image, pt1, pt2, Scalar(218, 218, 218), -1);
    
    string titleText = "RC mode";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    Size textSize = getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    
    vector<string> menuList;
    getRcMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_SIMPLEX;
    fontScale = 0.5;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        string text = menuList[i];
        textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    }
    
    textOrg.y += 20;
    pt1 = Point(0, textOrg.y);
    pt2 = Point(200, pt1.y);
    line(image, pt1, pt2, Scalar(180, 180, 180), 1);
    
    pt1.y += 25;
    pt1.x = 200/2 - 120/2;
    drawRcCom(image, pt1);
}

void drawDevMode (Mat& image)
{
    Point pt1(0, 0);
    Point pt2(200, (image.size().height-1)/2);
    rectangle(image, pt1, pt2, Scalar(218, 218, 218), -1);
    
    string titleText = "Dev mode";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    Size textSize = getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    
    vector<string> menuList;
    getDevMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_SIMPLEX;
    fontScale = 0.5;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        string text = menuList[i];
        textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    }
}

void drawConfigMode (Mat& image)
{
    Point pt1(0, 0);
    Point pt2(200, (image.size().height-1)/2);
    rectangle(image, pt1, pt2, Scalar(218, 218, 218), -1);
    
    string titleText = "Config mode";
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    int baseline = 0;
    Size textSize = getTextSize(titleText, fontFace, fontScale, 
    thickness, &baseline);
    
    // Get center of the text
    Point textOrg((200 - textSize.width)/2, (10 + textSize.height));
    putText(image, titleText, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    
    vector<string> menuList;
    getConfigMenuList(menuList);
    fontFace = CV_FONT_HERSHEY_SIMPLEX;
    fontScale = 0.5;
    textOrg.x = 10;
    for (size_t i = 0; i < menuList.size(); i++) {
        string text = menuList[i];
        textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
        textOrg.y = textOrg.y + 20 + textSize.height;
        putText(image, text, textOrg, fontFace, fontScale, Scalar::all(0), thickness);
    }
    
    textOrg.y += 20;
    pt1 = Point(0, textOrg.y);
    pt2 = Point(200, pt1.y);
    line(image, pt1, pt2, Scalar(180, 180, 180), 1);
}
