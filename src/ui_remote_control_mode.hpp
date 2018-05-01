/**
 * @file ui_remote_control_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_REMOTE_CONTROL_MODE_HPP
#define UI_REMOTE_CONTROL_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"
#include "vehicle_data.hpp"

//! @addtogroup user_interface
//! @{

class UIRemoteControlMode : public UserInterfaceMode {
public:
    UIRemoteControlMode (VehicleData& v) : vehicle(v) {};
    ~UIRemoteControlMode () = default;
    
    //~ void draw (cv::Mat& image, VehicleData& vehicle);
    void draw (cv::Mat& image) override;
    
private:
    void drawRcCom (cv::Mat& image, cv::Point position);
    void getRcMenuList (std::vector<std::string>& menuList);
    void getRcStateList (std::vector<std::string>& stateList, VehicleData& v);
    
    VehicleData& vehicle;
};

//! @} user_interface

#endif // UI_REMOTE_CONTROL_MODE_HPP
