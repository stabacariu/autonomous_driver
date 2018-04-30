/**
 * @file    detector.hpp
 * @author  Sergiu-Petru Tabacariu
 * @date    28.3.2018
 */

/**
 * @defgroup perception Perception
 * @brief Perception modules
 * @{
 *     @defgroup lane_detection Lane Detection
 *     @defgroup traffic_sign_detection Traffic Sign Detection
 *     @defgroup obstacle_detection Obstacle Detection
 * @}
 */
 
#ifndef DETECTOR_HPP
#define DETECTOR_HPP

//! @addtogroup perception
//! @{

/**
 * @brief A detector interface class
 */
class Detector {
public:
    ~Detector() = default;
    
    /**
     * @brief Start detection
     * 
     * This function starts the detection thread.
     */
    virtual void start (void) const = 0;
    
    /**
     * @brief Stop detection
     * 
     * This function stops the detection thread.
     */
    virtual void stop (void) const = 0;
    
    /**
     * @brief Check if detection is running
     * 
     * This function checks if the detection is running…
     * 
     * @return True if detection is running, else false.
     */
    virtual bool isRunning (void) const = 0;
    
private:
    bool running {false}; //!< Detection running flag
};

//! @} perception

#endif // DETECTOR_HPP
