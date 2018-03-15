/**
 * @file image_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef IMAGE_DATA_HPP
#define IMAGE_DATA_HPP

#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <pthread.h>

/**
 * @brief A struct to hold image data
 * 
 * This structure describes image with synchronised access.
 */
struct ImageData {
    cv::Mat data; //!< Image data as matrix
    time_t timeStamp; //!< Time of capture
    pthread_mutex_t lock; //!< Mutex lock for synchronized access
};

/**
 * @brief A function to initialize input image data
 * 
 * This function initializes the input image data.
 */
void initInputImageData (void);

/**
 * @brief A function to initialize inter image data
 * 
 * This function initializes the inter image data.
 */
void initInterImageData (void);

/**
 * @brief A function to initialize output image data
 * 
 * This function initializes the output image data.
 */
void initOutputImageData (void);

/**
 * @brief A function to set input image data
 * 
 * This function sets the input image data.
 * 
 * @param image
 */
void setInputImageData (cv::Mat image, time_t t);

/**
 * @brief A function to get input image data
 * 
 * This function gets the input image data.
 * 
 * @param image
 */
time_t getInputImageData (cv::Mat& image);

/**
 * @brief A function to set inter image data
 * 
 * This function sets the inter image data.
 * 
 * @param image
 */
void setInterImageData (cv::Mat image, time_t t);

/**
 * @brief A function to get inter image data
 * 
 * This function gets the inter image data.
 * 
 * @param image
 */
time_t getInterImageData (cv::Mat& image);

/**
 * @brief A function to set output image data
 * 
 * This function sets the output image data.
 * 
 * @param image
 */
void setOutputImageData (cv::Mat image, time_t t);

/**
 * @brief A function to get output image data
 * 
 * This function gets the output image data.
 * 
 * @param image
 */
time_t getOutputImageData (cv::Mat& image);

#endif // IMAGE_DATA_HPP

