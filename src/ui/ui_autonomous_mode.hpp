/**
 * @file ui_autonomous_mode.hpp
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
 * @brief A user interface for the Autonomous Driving Mode
 * 
 * This user interface shows the IPT camera image, the vehicle telemetry
 * and the detected lines, obstacle distance and traffic sign position.
 */
class UIAutonomousMode : public UserInterfaceMode {
public:
    UIAutonomousMode (VehicleModel& v, LaneData& l, ObstacleData& o, TrafficSignData& t) : vehicle(v), lane(l), obstacle(o), trafficSign(t) {};
    ~UIAutonomousMode () = default;
    
    /**
     * @brief Draw autonomous driving user interface mode
     * 
     * This function draws the autonomous driving user interface mode.
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
