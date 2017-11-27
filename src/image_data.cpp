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

void initInputData (void)
{
    pthread_mutex_init(&inputImage.lock, NULL);
}

void initOutputData (void)
{
    pthread_mutex_init(&outputImage.lock, NULL);
}

void setInputImageData (Mat data)
{
    if (pthread_mutex_lock(&inputImage.lock)) {
        cerr << "ERROR: Couldn't lock status mutex!" << endl;
    }
    
    data.copyTo(inputImage.data);
    //~ inputImage.dataQueue.push(Mat());
    //~ data.copyTo(inputImage.dataQueue.back());
    
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
    //~ if (!inputImage.dataQueue.empty()) {
        //~ inputImage.dataQueue.front().copyTo(image);
        //~ inputImage.dataQueue.pop();
    //~ }
    
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
    //~ outputImage.dataQueue.push(Mat());
    //~ data.copyTo(outputImage.dataQueue.back());
    
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
    //~ if (!outputImage.dataQueue.empty()) {
        //~ outputImage.dataQueue.front().copyTo(image);
        //~ outputImage.dataQueue.pop();
    //~ }
    
    if (pthread_mutex_unlock(&outputImage.lock)) {
        cerr << "ERROR: Couldn't unlock status mutex!" << endl;
    }
}
