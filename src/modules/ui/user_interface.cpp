/**
 * @file user_interface.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 10.4.2018
 */

#include "user_interface.hpp"
#include "configuration.hpp"

#define CVUI_IMPLEMENTATION
#include "cvui.h"

void UserInterface::run (ImageData& imageData, UserInterfaceState& uiState)
{
    std::cout << "THREAD: User interface started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    //~ uiConfig = config.getUserInterfaceConfig();
    camConfig = config.getCameraConfig();
    int menuWith = 200;
        
    //~ cv::namedWindow(uiConfig.mainWindowName, CV_WINDOW_AUTOSIZE);
    cvui::init(uiConfig.mainWindowName);
    
    while (running) {
        image = imageData.read();
        if (image.empty()) {
            image = cv::Mat(uiConfig.imageSize.height, uiConfig.imageSize.width, CV_8UC3, cv::Scalar::all(0));
            drawMessage(image, "No Image!");
        }
        // Create output image composition from UI menu and output image
        cv::Mat outputImage = cv::Mat(image.rows, image.cols + menuWith, CV_8UC3, cv::Scalar(49, 52, 49));
        //~ cv::Rect insert = cv::Rect(menuWith, 0, image.cols, image.rows);
        //~ image.copyTo(outputImage(insert));
        
        cvui::image(outputImage, menuWith, 0, image);
        
        uiState.draw(outputImage);
        
        //~ cvui::update();
        //~ imshow(uiConfig.mainWindowName, outputImage);
        
        cvui::imshow(uiConfig.mainWindowName, outputImage);
        inputKey = cv::waitKey((1000/uiConfig.fps)*(1.5));
        
        if (inputKey == (char)(-1)) {
            inputKey = getConsoleInput();
        }
        
        if (uiState.getKey() == (char)(-1)) {
            uiState.setKey(inputKey);
        }
    }

    std::cout << "THREAD: User interface ended." << std::endl;
}

void UserInterface::quit ()
{
    running = false;
}

bool UserInterface::isRunning ()
{
    return running;
}

char getConsoleInput (void)
{
    std::ios_base::sync_with_stdio(false);
    char key;
    if (std::cin.readsome(&key, 1) < 1) {
        key = (char)(-1);
    }
    std::ios_base::sync_with_stdio(true);
    return key;
}

void drawMessage (cv::Mat& image, std::string text)
{
    cv::Point pt1(image.cols/2 - 200/2, image.rows/2 - 100/2);
    cv::Point pt2(image.cols/2 + 200/2, image.rows/2 + 100/2);
    rectangle(image, pt1, pt2, cv::Scalar::all(218), -1);
    
    int fontFace = CV_FONT_HERSHEY_DUPLEX;
    double fontScale = 1;
    int thickness = 1;
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
    
    // Get center of the text
    cv::Point textOrg(pt1.x + (pt2.x - pt1.x)/2 - textSize.width/2, pt1.y + (pt2.y - pt1.y)/2 + textSize.height/2);
    putText(image, text, textOrg, fontFace, fontScale, cv::Scalar(0, 0, 255), thickness);
}
