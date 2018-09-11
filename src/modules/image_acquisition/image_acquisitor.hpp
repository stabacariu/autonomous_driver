/**
 * @file    image_acquisitor.hpp
 * @author  Sergiu-Petru Tabacariu
 * @date    28.3.2018
 */

/**
 * @ingroup module
 * @defgroup image_acquisition Image Acquisition
 * @brief A module for image acquisition.
 */
 
#ifndef IMAGE_ACQUISITOR_HPP
#define IMAGE_ACQUISITOR_HPP

#include <atomic>
#include <opencv2/opencv.hpp>
#include "module.hpp"
#include "image_data.hpp"

//! @addtogroup image_acquisition
//! @{

/**
 * @brief A image acquisition class
 * 
 * This class defines an image acquistor interface.
 */
class ImageAcquisitor : public Module {
public:
    ~ImageAcquisitor() = default;
    
    /**
     * @brief Read acquisited image
     * 
     * This function reads the last acquisited image.
     * 
     * @return Acquisited image
     */
    virtual cv::Mat read (void) = 0;
    
    /**
     * @brief Write image to image acquisitor
     * 
     * This function writes an image to the image acquisitor.
     * 
     * @param image Image matrix
     */
    virtual void write (cv::Mat image) = 0;
    
    /**
     * @brief Run image acquisition
     * 
     * This function runs an image acquisition thread
     * 
     * @param image Acquisited image
     */
    virtual void run (ImageData& image) = 0;
    
protected:
    ImageData image; //!< Acquisited image
};

//! @} image_acquisition

#endif // IMAGE_ACQUISITOR_HPP
