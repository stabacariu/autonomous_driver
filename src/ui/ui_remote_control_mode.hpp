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

//! @addtogroup user_interface_mode
//! @{

/**
 * @brief A user interface for the Remote Control Mode
 * 
 * This user interface shows the remote control mode. It shows the actual
 * camera image and on-screen vehicle control options to remote control
 * the system.
 */
class UIRemoteControlMode : public UserInterfaceMode {
public:
    UIRemoteControlMode (VehicleModel& v) : vehicle(v) {};
    ~UIRemoteControlMode () = default;
    
    /**
     * @brief Draw remote control user interface mode
     * 
     * This function draws the remote control user interface mode.
     * 
     * @param image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;
    
private:
    VehicleModel& vehicle;
};

//! @} user_interface_mode

#endif // UI_REMOTE_CONTROL_MODE_HPP
