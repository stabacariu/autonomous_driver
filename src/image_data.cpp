/**
 * @file image_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_data.hpp"

ImageData inputImage;  //!< Holds input image
ImageData interImage;  //!< Holds intermidiate image
ImageData outputImage; //!< Holds output image

void initInputImageData (void)
{
    pthread_mutex_init(&inputImage.lock, NULL);
}

void initInterImageData (void)
{
    pthread_mutex_init(&interImage.lock, NULL);
}

void initOutputImageData (void)
{
    pthread_mutex_init(&outputImage.lock, NULL);
}

void setInputImageData (cv::Mat data, time_t t)
{
    if (pthread_mutex_lock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    data.copyTo(inputImage.data);
    inputImage.timeStamp = t;
    
    if (pthread_mutex_unlock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

time_t getInputImageData (cv::Mat& image)
{
    time_t t;
    
    if (pthread_mutex_lock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    inputImage.data.copyTo(image);
    t = inputImage.timeStamp;
    
    if (pthread_mutex_unlock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
    
    return t;
}

void setInterImageData (cv::Mat data, time_t t)
{
    if (pthread_mutex_lock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    data.copyTo(interImage.data);
    interImage.timeStamp = t;
    
    if (pthread_mutex_unlock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

time_t getInterImageData (cv::Mat& image)
{
    time_t t;
    
    if (pthread_mutex_lock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    interImage.data.copyTo(image);
    t = interImage.timeStamp;
    
    if (pthread_mutex_unlock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
    
    return t;
}

void setOutputImageData (cv::Mat data, time_t t)
{
    if (pthread_mutex_lock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    data.copyTo(outputImage.data);
    outputImage.timeStamp = t;
    
    if (pthread_mutex_unlock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

time_t getOutputImageData (cv::Mat& image)
{
    time_t t;
    
    if (pthread_mutex_lock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    outputImage.data.copyTo(image);
    t = outputImage.timeStamp;
    
    if (pthread_mutex_unlock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
    
    return t;
}
