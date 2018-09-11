/**
 * @file about_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 * 
 * @note This should be part of the User Interface.
 */

/**
 * @ingroup system_mode
 * @defgroup about_mode About Mode
 * @brief A mode provides system version information
 */

#ifndef ABOUT_MODE_HPP
#define ABOUT_MODE_HPP

#include <iostream>
#include "system_mode.hpp"
#include "system_state.hpp"
#include "image_data.hpp"
#include "user_interface_state.hpp"
#include "user_interface.hpp"

//! @addtogroup about_mode
//! @{

class AboutMode : public SystemMode {
public:
    ~AboutMode() = default;

    void run (SystemState* s) override;
    void quit (void) override;
    void stopModules (void);

private:
    ImageData outputImage;
    UserInterfaceState uiState;
    UserInterface ui;
};

//! @} about_mode

#endif // ABOUT_MODE_HPP
