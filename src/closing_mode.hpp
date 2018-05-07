/**
 * @file closing_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.4.2018
 */

#ifndef CLOSING_MODE_HPP
#define CLOSING_MODE_HPP

#include <iostream>
#include "system_mode.hpp"

//! @addtogroup closing_mode
//! @brief A mode for closing the system safely
//! @{

class ClosingMode : public SystemMode {
public:
    ~ClosingMode() = default;

    void run (SystemState* s) override;
    void quit (void) override;
};

//! @} closing_mode

#endif // CLOSING_MODE_HPP
