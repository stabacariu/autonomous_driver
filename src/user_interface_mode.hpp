/**
 * @file user_interface_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef USER_INTERFACE_MODE_HPP
#define USER_INTERFACE_MODE_HPP

#include <opencv2/opencv.hpp>

class UserInterfaceMode {
public:
    virtual ~UserInterfaceMode () = default;
    
    virtual void draw (cv::Mat& image) = 0;
};

#endif // USER_INTERFACE_MODE_HPP
