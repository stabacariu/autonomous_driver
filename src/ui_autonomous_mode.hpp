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

//! @addtogroup user_interface
//! @{

class UIAutonomousMode : public UserInterfaceMode {
public:
    UIAutonomousMode (VehicleModel& v, LaneData& l, ObstacleData& o, TrafficSignData& t) : vehicle(v), lane(l), obstacle(o), trafficSign(t) {};
    ~UIAutonomousMode () = default;
    
    /**
     * @brief Draw autonomous driving user interface mode
     * 
     * This function draws the autonomous driving user interface mode.
     * 
     * @brief image Image matrix
     */
    void draw (cv::Mat& image) override;

private:
    void getMenuList (std::vector<std::string>& menuList);
    void getStateList (std::vector<std::string>& stateList, VehicleModel& v);
    void getDetectList (std::vector<std::string>& detectList, LaneData& l, ObstacleData& o, TrafficSignData& t);
    
    VehicleModel& vehicle;
    LaneData& lane;
    ObstacleData& obstacle;
    TrafficSignData& trafficSign;
};

//! @} user_interface

#endif // UI_AUTONOMOUS_MODE_HPP
