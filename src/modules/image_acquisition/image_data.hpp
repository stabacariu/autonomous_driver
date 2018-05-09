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
     * This function writes the image data and the creation time.
     * 
     * @param image
     */
    void write (cv::Mat image);
    
    /**
     * @brief Read image data
     * 
     * This function reads the input image data and the creation time.
     * 
     * @return Image matrix and time
     */
    cv::Mat read (void);

private:
    cv::Mat data; //!< Image data as matrix
    //~ std::queue<cv::Mat> buffer; //!< Image data as matrix
    std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds> timeStamp; //!< Time of capture
    std::mutex lock; //!< Mutex lock for synchronized access
    
};

#endif // IMAGE_DATA_HPP

