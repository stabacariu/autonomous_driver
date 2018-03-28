/**
 * @file    image_acquisitor.hpp
 * @author  Sergiu-Petru Tabacariu
 * @date    28.3.2018
 */

/**
 * @defgroup image_acquisition Image Acquisition
 * @brief A module for image acquisition.
 * @{
 *     @defgroup image_acquisitor Image Acquisiton Interface
 *     @defgroup camera_image_acquisitor Camera Image Acquisitor
 *     @{
 *         @defgroup camera_calibration Camera Calibration
 *     @}
 *     @defgroup image_sequence_acquisitor Image Sequence Acquisitor
 *     @defgroup video_file_image_acquisitor Video File Image Acquisitor
 * @}
 */
 
#ifndef IMAGE_ACQUISITOR_HPP
#define IMAGE_ACQUISITOR_HPP

#include "image_data.hpp"

//! @addtogroup image_acquisitor
//! @brief A module to acquisit images
//! @{

/**
 * @brief A image acquisition class
 * 
 * This class defines an image acquistor interface.
 */
class ImageAcquisitor {
public:
    //~ virtual ImageAcquisitor();
    //~ virtual ImageAcquisitor(int id, ImageDataClass image, cv::Size size);
    virtual ~ImageAcquisitor();
    
    virtual ImageDataClass read();
    virtual void write (ImageDataClass image);
    virtual bool start();
    virtual bool stop();
    
private:
    int id;
    ImageDataClass image;
    int width;
    int height;
    bool running;
};

//! @} image_acquisitor

#endif // IMAGE_ACQUISITOR_HPP
