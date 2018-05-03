/**
 * @file user_interface.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 10.4.2018
 */

#include "user_interface.hpp"

void UserInterface::start (ImageData& imageData, UserInterfaceState& uiState)
{
    std::cout << "THREAD: User interface started." << std::endl;
    running = true;
    
    cv::namedWindow("Autonomous Driver 1.0", CV_WINDOW_AUTOSIZE);
    
    while (running) {
        image = imageData.read();
        if (image.empty()) {
            image = cv::Mat(360, 640, CV_8UC3, cv::Scalar::all(0));
            drawMessage(image, "No Image!");
        }
        // Create output image composition from UI menu and output image
        cv::Mat outputImage = cv::Mat(image.rows, image.cols + 200, CV_8UC3, cv::Scalar::all(0));
        cv::Rect insert = cv::Rect(200, 0, image.cols, image.rows);
        image.copyTo(outputImage(insert));
        
        uiState.draw(outputImage);
        
        imshow("Autonomous Driver 1.0", outputImage);
        guiInputKey = cv::waitKey(1000/30);
        
        if (uiState.getKey() == (char)(-1)) {
            uiState.setKey(guiInputKey);
        }
        
    }

    std::cout << "THREAD: User interface ended." << std::endl;
}

void UserInterface::stop ()
{
    running = false;
}

bool UserInterface::isRunning ()
{
    return running;
}

void UserInterface::consoleInput (UserInterfaceState& uiState)
{
    std::cout << "THREAD: User input started." << std::endl;
    running = true;
    std::ios_base::sync_with_stdio(false);
    
    while (running) {
        char key;
        if (std::cin.readsome(&key, 1) < 1) {
            key = (char)(-1);
        }
        consoleInputKey = key;
        
        if (uiState.getKey() == (char)(-1)) {
            uiState.setKey(consoleInputKey);
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
    std::ios_base::sync_with_stdio(true);
    
    std::cout << "THREAD: User input ended." << std::endl;
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
