/**
 * @file standby_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#ifndef STANDBY_MODE_HPP
#define STANDBY_MODE_HPP

#include <iostream>
#include <thread>
#include "system_mode.hpp"
#include "system_state.hpp"
#include "user_interface_data.hpp"
#include "image_data.hpp"
#include "user_interface.hpp"
#include "camera_image_acquisitor.hpp"

//! @addtogroup standby_mode
//! @brief A mode for system standby
//! @{

class StandbyMode : public SystemMode {
public:
    ~StandbyMode() = default;
    
    /**
     * @brief Start standby system mode
     * 
     * This function starts the system standby mode.
     * This mode displays the main menu and the actual camera view.
     * 
     * @param s System state pointer
     */
    void start (SystemState* s) override;
    
    /**
     * @brief Stop standby system mode
     * 
     * This function stops the system standby mode.
     */
    void stop (void) override;
    
    /**
     * @brief Stop autonomous driving mode modules
     * 
     * This function stops all autonomous driving mode modules.
     */
    void stopModules (void);

private:
    ImageData inputImage; //!< Input image captured by an image acquisitor
    UserInterfaceData uiData; //!< User inderface user input data
    UserInterface ui; //!< User interface
    CameraImageAcquisitor camera; //!< Camera image acquisitor
};

//! @} standby_mode

#endif // STANDBY_MODE_HPP
