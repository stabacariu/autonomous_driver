/**
 * @file configuration_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#ifndef CONFIGURATION_MODE_HPP
#define CONFIGURATION_MODE_HPP

#include <iostream>
#include "system_mode.hpp"
#include "system_state.hpp"
#include "image_data.hpp"
#include "user_interface_state.hpp"
#include "user_interface.hpp"
#include "camera_image_acquisitor.hpp"

//! @addtogroup configuration_mode
//! @brief A mode to configure the system
//! @{

class ConfigurationMode : public SystemMode {
public:
    ~ConfigurationMode() = default;

    void start (SystemState* s) override;
    void stop (void) override;
    void stopModules (void);

private:
    ImageData inputImage; //!< Input image captured by an image acquisitor
    UserInterfaceState uiState; //!< User inderface input data
    UserInterface ui; //!< User interface
    CameraImageAcquisitor camera; //!< Camera image acquisitor
};

//! @} configuration_mode

#endif // CONFIGURATION_MODE_HPP
