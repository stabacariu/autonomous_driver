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
        if (!image.empty()) {
            uiState.draw(image);
            
            imshow("Autonomous Driver 1.0", image);
            guiInputKey = cv::waitKey(1000/30);
        }
        
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                
        char key = consoleInputKey;
        if (std::cin.readsome(&key, 1) < 1) {
            consoleInputKey = (char)(-1);
        }
        
        if (uiState.getKey() == (char)(-1)) {
            uiState.setKey(consoleInputKey);
        }
    }
    
    std::ios_base::sync_with_stdio(true);
    
    std::cout << "THREAD: User input ended." << std::endl;
}

void UserInterface::setUserInput (char c)
{
    std::lock_guard<std::mutex> guard(lock);
    guiInputKey = c;
    consoleInputKey = c;
}

char UserInterface::getUserInput ()
{
    std::lock_guard<std::mutex> guard(lock);
    if (guiInputKey == consoleInputKey) {
        return guiInputKey;
    }
    else if ((guiInputKey == (char)(-1)) && (consoleInputKey != (char)(-1))) {
        return consoleInputKey;
    }
    else if ((guiInputKey != (char)(-1)) && (consoleInputKey == (char)(-1))) {
        return guiInputKey;
    }
    else {
        return guiInputKey;
    }
}
