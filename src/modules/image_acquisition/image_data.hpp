/**
 * @file image_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef IMAGE_DATA_HPP
#define IMAGE_DATA_HPP

#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <mutex>

//! @addtogroup image_acquisition
//! @{

/**
 * @brief A image data class
 * 
 * This class describes the image data which holds the image data as
 * an OpenCV Matrix and a mutex lock for synchronised accses.
 */
class ImageData {
public:
    ~ImageData() = default;
    
    /**
     * @brief Write image data
     * 
     * This function writes the image data and the aquisition time.
     * 
     * @param image
     */
    void write (cv::Mat image);
    
    /**
     * @brief Read image data
     * 
     * This function reads the input image data.
     * 
     * @return Image matrix and time
     */
    cv::Mat read (void);
    
    /**
     * @brief Set frame aquisition time
     * 
     * This function sets the frame aquisition time.
     * 
     * @param time Aquisition time
     */
    void setTime(std::chrono::high_resolution_clock::time_point time);
    
    /**
     * @brief Get frame aquisition time
     * 
     * This function gets the frame aquisition time.
     * 
     * @return Aquisition time
     */
    std::chrono::high_resolution_clock::time_point getTime();

private:
    cv::Mat data; //!< Image data as matrix
    std::chrono::high_resolution_clock::time_point timeStamp; //!< Time of capture
    std::mutex lock; //!< Mutex lock for synchronized access
    
};

//! @} image_acquisition

#endif // IMAGE_DATA_HPP

