/**
 * @file image_data.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef IMAGE_DATA_HPP
#define IMAGE_DATA_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pthread.h>

struct ImageData {
    cv::Mat data;
    pthread_mutex_t lock;
};

void initInputData (void);
void initOutputData (void);

void setInputImageData (cv::Mat image);
void getInputImageData (cv::Mat& image);
void setOutputImageData (cv::Mat image);
void getOutputImageData (cv::Mat& image);

#endif // IMAGE_DATA_HPP

