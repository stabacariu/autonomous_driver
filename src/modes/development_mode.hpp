/**
 * @file development_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#ifndef DEVELOPMENT_MODE_HPP
#define DEVELOPMENT_MODE_HPP

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
#include "remote_control.hpp"
#include "vehicle_data.hpp"
#include "vehicle_control.hpp"

//! @addtogroup development_mode
//! @brief A mode for development
//! @{

class DevelopmentMode : public SystemMode {
public:
    ~DevelopmentMode () = default;
    
    /**
     * @brief Run development mode
     * 
     * This function runs the development mode.
     */
    void run (SystemState* s) override;
    
    /**
     * @brief Quit development mode
     * 
     * This function quits the development mode.
     */
    void quit (void) override;
    
    /**
     * @brief Stop development mode modules
     * 
     * This function stops all development mode modules.
     */
    void stopModules (void);

private:
    ImageData outputImage; //!< Output image data to show on user interface
    UserInterfaceState uiState; //!< User interface user input data
    UserInterface ui; //!< User interface
    
    ImageData inputImage; //!< Input image data from an image acquisitor
    CameraImageAcquisitor camera; //!< Camera image acquisitor
    
    LaneData lane; //!< Lane data of actual detected lane
    LaneDetector laneDetector; //!< Lane detector
    
    TrafficSignData trafficSignData; //!< Traffic sign data of detected traffic sign
    TrafficSignDetector trafficSignDetector; //!< Traffic sign detector
    
    ObstacleData obstacle; //!< Obstacle data
    ObstacleDetector obstacleDetector; //!< Obstacle detector
    
    RemoteController remoteController; //!< Remote controller
    
    VehicleModel vehicle; //!< Vehicle data
    VehicleController vehicleController; //!< Vehicle controler
};

//! @} development_mode

#endif // DEVELOPMENT_MODE_HPP

