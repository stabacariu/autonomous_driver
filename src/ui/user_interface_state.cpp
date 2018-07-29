/**
 * @file user_interface_state.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#include "user_interface_state.hpp"

void UserInterfaceState::setKey (char k)
{
    key = k;
}

char UserInterfaceState::getKey (void)
{
    return key;
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

void UserInterfaceState::draw (cv::Mat& image, char& selected)
{
    mode->draw(image, selected);
}
