/**
 * @file autonomous_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#ifndef AUTONOMOUS_MODE_HPP
#define AUTONOMOUS_MODE_HPP

#include <iostream>
#include "system_mode.hpp"
#include "system_state.hpp"
#include "image_data.hpp"
#include "user_interface_state.hpp"
#include "user_interface.hpp"
#include "camera_image_acquisitor.hpp"
#include "lane_data.hpp"
#include "lane_detection.hpp"
#include "traffic_sign_data.hpp"
#include "traffic_sign_detection.hpp"
#include "obstacle_data.hpp"
#include "obstacle_detection.hpp"
#include "path_planning.hpp"
#include "vehicle_data.hpp"
#include "vehicle_control.hpp"

//! @addtogroup autonomous_driving_mode
//! @brief A mode for autonomous driving
//! @{

class AutonomousMode : public SystemMode {
public:
    ~AutonomousMode () = default;
    
    /**
     * @brief Start autonomous driving mode
     * 
     * This function starts the autonomous driving mode.
     */
    void start (SystemState* s) override;
    
    /**
     * @brief Stop autonomous driving mode
     * 
     * This function stops the autonomous driving mode.
     */
    void stop (void) override;
    
    /**
     * @brief Stop autonomous driving mode modules
     * 
     * This function stops all autonomous driving mode modules.
     */
    void stopModules (void);

private:
    ImageData outputImage; //!< Output image data to show on user interface
    UserInterfaceState uiState; //!< User interface user input data
    UserInterface ui; //!< User interface
    
    ImageData inputImage; //!< Input image data from an image acquisitor
    CameraImageAcquisitor camera; //!< Camera image acquisitor
    
    LaneData lane; //!< Lane data of actual detected lane
    LaneDetector laneDetetor; //!< Lane detector
    
    TrafficSignData trafficSignData; //!< Traffic sign data of detected traffic sign
    TrafficSignDetector trafficSignDetector; //!< Traffic sign detector
    
    ObstacleData obstacle; //!< Obstacle data
    ObstacleDetector obstacleDetector; //!< Obstacle detector
    
    PathPlanner pathPlanner; //!< Path planner
    
    VehicleData vehicle; //!< Vehicle data
    VehicleControler vehicleControler; //!< Vehicle controler
};

//! @} autonomous_driving_mode

#endif // AUTONOMOUS_MODE_HPP
