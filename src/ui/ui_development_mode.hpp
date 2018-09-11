/**
 * @file ui_development_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#ifndef UI_AUTONOMOUS_MODE_HPP
#define UI_AUTONOMOUS_MODE_HPP

#include <opencv2/opencv.hpp>
#include "user_interface_mode.hpp"
#include "vehicle_data.hpp"
#include "lane_data.hpp"
#include "obstacle_data.hpp"
#include "traffic_sign_data.hpp"

//! @addtogroup user_interface_mode
//! @{


/**
 * @brief A user interface for the Development Mode
 * 
 * This user interface shows development mode. It shows the same as the
 * autonomous driving mode, but offers on-screen controls for remote
 * controlling the system.
 */
class UIDevelopmentMode : public UserInterfaceMode {
public:
    UIDevelopmentMode (VehicleModel& v, LaneData& l, ObstacleData& o, TrafficSignData& t) : vehicle(v), lane(l), obstacle(o), trafficSign(t) {};
    ~UIDevelopmentMode () = default;
    
    /**
     * @brief Draw development driving user interface mode
     * 
     * This function draws the development driving user interface mode.
     * 
     * @param image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected) override;

private:
    VehicleModel& vehicle;
    LaneData& lane;
    ObstacleData& obstacle;
    TrafficSignData& trafficSign;
};

//! @} user_interface_mode

#endif // UI_AUTONOMOUS_MODE_HPP

