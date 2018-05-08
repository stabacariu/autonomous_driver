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
    UIRemoteControlMode (VehicleModel& v) : vehicle(v) {};
    ~UIRemoteControlMode () = default;
    
    /**
     * @brief Draw remote control user interface mode
     * 
     * This function draws the remote control user interface mode.
     * 
     * @brief image Image matrix
     */
    void draw (cv::Mat& image) override;
    
private:
    void drawRcCom (cv::Mat& image, cv::Point position);
    void getMenuList (std::vector<std::string>& menuList);
    void getStateList (std::vector<std::string>& stateList, VehicleModel& v);
    
    VehicleModel& vehicle;
};

//! @} user_interface

#endif // UI_REMOTE_CONTROL_MODE_HPP
