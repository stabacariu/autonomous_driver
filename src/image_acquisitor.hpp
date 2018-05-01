/**
 * @file    image_acquisitor.hpp
 * @author  Sergiu-Petru Tabacariu
 * @date    28.3.2018
 */

/**
 * @defgroup image_acquisition Image Acquisition
 * @brief A module for image acquisition.
 * @{
 *     @defgroup camera_image_acquisitor Camera Image Acquisitor
 *     @brief A module for camera image acquisition
 *     @{
 *         @defgroup camera_calibration Camera Calibration
 *         @brief A module for camera calibration
 *     @}
 *     @defgroup image_sequence_acquisitor Image Sequence Acquisitor
 *     @brief A module for image sequence acquisiton from a file
 *     @defgroup video_file_image_acquisitor Video File Image Acquisitor
 *     @brief A module for image aquisition from a video file
 * @}
 */
 
#ifndef IMAGE_ACQUISITOR_HPP
#define IMAGE_ACQUISITOR_HPP

#include <atomic>
#include <opencv2/opencv.hpp>
#include "image_data.hpp"

//! @addtogroup image_acquisition
//! @brief A module to acquisit images
//! @{

/**
 * @brief A image acquisition class
 * 
 * This class defines an image acquistor interface.
 */
class ImageAcquisitor {
public:
    ~ImageAcquisitor() = default;
    
    virtual cv::Mat read (void) = 0;
    virtual void write (cv::Mat image) = 0;
    
    virtual void start (ImageData& image) = 0;
    
    /**
     * @brief Stop image acquisition
     * 
     * This function stops the image acquisition thread.
     */
    virtual void stop (void) { running = false; };
    
    /**
     * @brief Checks if image aquisition is running
     * 
     * This function checks if the image aquisition is running.
     * 
     * @return True if acquisition is running, else false-.
     */
    virtual bool isRunning (void) { return running; };
    
protected:
    int id;
    ImageData image;
    int width;
    int height;
    std::atomic_bool running;
};

//! @} image_acquisition

#endif // IMAGE_ACQUISITOR_HPP
