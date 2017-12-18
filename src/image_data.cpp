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

void setInputImageData (cv::Mat data)
{
    if (pthread_mutex_lock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    data.copyTo(inputImage.data);
    
    if (pthread_mutex_unlock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

void getInputImageData (cv::Mat& image)
{
    if (pthread_mutex_lock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    inputImage.data.copyTo(image);
    
    if (pthread_mutex_unlock(&inputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

void setInterImageData (cv::Mat data)
{
    if (pthread_mutex_lock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    data.copyTo(interImage.data);
    
    if (pthread_mutex_unlock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

void getInterImageData (cv::Mat& image)
{
    if (pthread_mutex_lock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    interImage.data.copyTo(image);
    
    if (pthread_mutex_unlock(&interImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

void setOutputImageData (cv::Mat data)
{
    if (pthread_mutex_lock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    data.copyTo(outputImage.data);
    
    if (pthread_mutex_unlock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}

void getOutputImageData (cv::Mat& image)
{
    if (pthread_mutex_lock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't lock status mutex!" << std::endl;
    }
    
    outputImage.data.copyTo(image);
    
    if (pthread_mutex_unlock(&outputImage.lock)) {
        std::cerr << "ERROR: Couldn't unlock status mutex!" << std::endl;
    }
}
