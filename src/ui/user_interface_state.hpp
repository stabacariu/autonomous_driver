/**
 * @file user_interface_state.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

/**
 * @defgroup user_interface_state User Interface State
 * @brief User Interface State
 */

#ifndef USER_INTERFACE_STATE_HPP
#define USER_INTERFACE_STATE_HPP

#include <iostream>
#include <atomic>
#include <mutex>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface_state
//! @{

class UserInterfaceState {
public:
    ~UserInterfaceState() = default;
    
    /**
     * @brief Set user input key
     * 
     * @param k User input key
     */
    void setKey (char k);
    
    /**
     * @brief Get user input key
     * 
     * @return User input key
     */
    char getKey (void);
    
    /**
     * @brief Set user interface mode
     * 
     * @param m User interface mode
     */
    void setMode (UserInterfaceMode* m);
    
    /**
     * @brief Get user interface mode
     * 
     * @return User interface mode
     */
    UserInterfaceMode* getMode (void);
    
    /**
     * @brief Draw user interface
     * 
     * This function draws the user interface.
     * 
     * @param image Image matrix
     * @param selected Selected button
     */
    void draw (cv::Mat& image, char& selected);

private:
    std::atomic_char key {(char)(-1)}; //!< Actual user input key
    UserInterfaceMode* mode; //!< Actual user interface mode pointer
    std::mutex lock; //!< Mutex lock for synchronized access
};

//! @} user_interface_state

#endif // USER_INTERFACE_STATE_HPP
