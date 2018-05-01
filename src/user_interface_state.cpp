/**
 * @file user_interface_state.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#include "user_interface_state.hpp"

void UserInterfaceState::setKey (char k)
{
    std::lock_guard<std::mutex> guard(lock);
    key = k;
    if (key != (char)(-1)) {
        lastKey = key;
    }
}

char UserInterfaceState::getKey (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return key;
}

char UserInterfaceState::getLastKey (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return lastKey;
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
