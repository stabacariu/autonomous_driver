/**
 * @file user_interface_state.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#ifndef USER_INTERFACE_STATE_HPP
#define USER_INTERFACE_STATE_HPP

#include <iostream>
#include <atomic>
#include <mutex>
#include "user_interface_mode.hpp"

class UserInterfaceState {
public:
    ~UserInterfaceState() = default;
    
    void setKey (char k);
    char getKey (void);
    char getLastKey (void);
    void setMode (UserInterfaceMode* m);
    UserInterfaceMode* getMode (void);
    void draw (cv::Mat& image);

private:
    char key {(char)(-1)};
    char lastKey {(char)(-1)};
    UserInterfaceMode* mode;
    std::mutex lock; //!< Mutex lock for synchronized access
};

#endif // USER_INTERFACE_STATE_HPP
