/**
 * @file user_interface_state.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#include "user_interface_state.hpp"

void UserInterfaceState::setKey (char k)
{
    //~ std::lock_guard<std::mutex> guard(lock);
    key = k;
}

char UserInterfaceState::getKey (void)
{
    //~ std::lock_guard<std::mutex> guard(lock);
    char k = key;
    key = (char)(-1);
    return k;
}

void UserInterfaceState::setMode (UserInterfaceMode* m)
{
    std::lock_guard<std::mutex> guard(lock);
    mode = m;
}

UserInterfaceMode* UserInterfaceState::getMode (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return mode;
}

void UserInterfaceState::draw (cv::Mat& image)
{
    mode->draw(image);
}
