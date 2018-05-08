/**
 * @file user_interface_state.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.4.2018
 */

#ifndef USER_INTERFACE_STATE_HPP
#define USER_INTERFACE_STATE_HPP

#include <iostream>
#include <atomic>
#include <mutex>
#include "user_interface_mode.hpp"

//! @addtogroup user_interface
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
     * @brief image Image matrix
     */
    void draw (cv::Mat& image);

private:
    std::atomic_char key {(char)(-1)}; //!< Actual user input key
    UserInterfaceMode* mode; //!< Actual user interface mode pointer
    std::mutex lock; //!< Mutex lock for synchronized access
};

//! @} user_interface

#endif // USER_INTERFACE_STATE_HPP
