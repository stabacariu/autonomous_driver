/**
 * @file remote_control.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#ifndef REMOTE_CONTROL_MODE_HPP
#define REMOTE_CONTROL_MODE_HPP

#include <iostream>
#include "system_mode.hpp"
#include "image_data.hpp"
#include "user_interface_state.hpp"
#include "user_interface.hpp"
#include "camera_image_acquisitor.hpp"
#include "vehicle_data.hpp"
#include "remote_control.hpp"
#include "vehicle_control.hpp"

//! @addtogroup remote_control_mode
//! @brief A mode to manualy remote control the autonomous driving system
//! @{

class RemoteControlMode : public SystemMode {
public:
    ~RemoteControlMode() = default;
    
    /**
     * @brief Start remote control mode
     * 
     * This function starts the remote control mode.
     * 
     * @param s System state pointer
     */
    void run (SystemState* s) override;
    
    /**
     * @brief Stop remote control mode
     * 
     * This function stops the remote control mode.
     */
    void quit (void) override;
    
    /**
     * @brief Stop autonomous driving mode modules
     * 
     * This function stops all autonomous driving mode modules.
     */
    void stopModules (void);

private:
    ImageData inputImage; //!< Input image data from an image acquisitor
    ImageData outputImage; //!< Output image data from an image acquisitor
    UserInterfaceState uiState; //!< User inderface user input data
    UserInterface ui; //!< User interface
    CameraImageAcquisitor camera; //!< Camera image acquisitor
    VehicleModel vehicle; //!< Vehicle data
    RemoteController remoteController; //!< Remote controller
    VehicleController vehicleController; //!< Vehicle controller
};

//! @} remote_control_mode

#endif // REMOTE_CONTROL_MODE_HPP
