/**
 * @file closing_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

/**
 * @ingroup system_mode
 * @defgroup closing_mode Closing Mode
 * @brief A mode to close the system safetly
 */

#ifndef CLOSING_MODE_HPP
#define CLOSING_MODE_HPP

#include <iostream>
#include "system_mode.hpp"

//! @addtogroup closing_mode
//! @{

class ClosingMode : public SystemMode {
public:
    ~ClosingMode() = default;

    void run (SystemState* s) override;
    void quit (void) override;
};

//! @} closing_mode

#endif // CLOSING_MODE_HPP
