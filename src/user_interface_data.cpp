/**
 * @file user_interface_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#include "user_interface_data.hpp"

void UserInterfaceData::setKey (char k)
{
    std::lock_guard<std::mutex> guard(lock);
    key = k;
    if (key != (char)(-1)) {
        lastKey = key;
    }
}

char UserInterfaceData::getKey (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return key;
}

char UserInterfaceData::getLastKey (void)
{
    std::lock_guard<std::mutex> guard(lock);
    return lastKey;
}

