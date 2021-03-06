/**
 * @file error_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

/**
 * @ingroup system_mode
 * @defgroup error_mode Error Mode
 * @brief A mode to catch all system errors and safely close the system
 */

#ifndef ERROR_MODE_HPP
#define ERROR_MODE_HPP

#include <iostream>
#include "system_mode.hpp"
#include "system_state.hpp"

//! @addtogroup error_mode
//! @{

class ErrorMode : public SystemMode {
public:
    ~ErrorMode() = default;

    void run (SystemState* s) override;
    void quit (void) override;
};

//! @} error_mode

#endif // ERROR_MODE_HPP
