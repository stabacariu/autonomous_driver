/**
 * @file image_data.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_data.hpp"

ImageData inputImage;  //!< Holds input image
ImageData outputImage; //!< Holds output image

using namespace std;
using namespace cv;

void inputDataInit (void)
{
    pthread_mutex_init(&inputImage.lock, NULL);
}

void outputDataInit (void)
{
    pthread_mutex_init(&outputImage.lock, NULL);
}

void setInputImageData (Mat data)
{
    if (pthread_mutex_lock(&inputImage.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    data.copyTo(inputImage.data);
    
    if (pthread_mutex_unlock(&inputImage.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

void getInputImageData (Mat& image)
{
    if (pthread_mutex_lock(&inputImage.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    inputImage.data.copyTo(image);
    
    if (pthread_mutex_unlock(&inputImage.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

void setOutputImageData (Mat data)
{
    if (pthread_mutex_lock(&outputImage.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    data.copyTo(outputImage.data);
    
    if (pthread_mutex_unlock(&outputImage.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}

void getOutputImageData (Mat& image)
{
    if (pthread_mutex_lock(&outputImage.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    outputImage.data.copyTo(image);
    
    if (pthread_mutex_unlock(&outputImage.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}
