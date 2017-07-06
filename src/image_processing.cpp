/**
 * @file image_preprocessing.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_processing.hpp"

using namespace std;
using namespace cv;

void imageProcessing (void)
{
    pthread_t cameraCaptureThread;
    pthread_t detectLaneThread;
    pthread_t detectTrafficSignThread;
    pthread_t showImageThread;
    
    // Create image processing threads
    if (pthread_create(&cameraCaptureThread, NULL, cameraCapture, NULL)) {
        cerr << "ERROR: Couldn't create camera capture thread!" << endl;
    }
    // Detect lane
    if (pthread_create(&detectLaneThread, NULL, laneDetection, NULL)) {
        cerr << "ERROR: Couldn't create lane detection thread!" << endl;
    }
    // Detect traffic signs
    if (pthread_create(&detectTrafficSignThread, NULL, trafficSignDetection, NULL)) {
        cerr << "ERROR: Couldn't create traffic sign detection thread!" << endl;
    }
    // Show result
    if (pthread_create(&showImageThread, NULL, imageShow, NULL)) {
        cerr << "ERROR: Couldn't create image show thread!" << endl;
    }
    
    // Join image processing threads
    if (pthread_join(cameraCaptureThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(detectLaneThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(detectTrafficSignThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
    if (pthread_join(showImageThread, NULL)) {
        cerr << "ERROR: Couldn't join thread!" << endl;
    }
}

void *imageShow (void *arg)
{
    cout << "Thread image show started." << endl;
    char key = 'n';
    
    while (getSystemState() != SYS_MODE_CLOSING) {
        Mat image;
        getOutputImageData(image);
        
        processUiInput(image, key);
        
        if (!image.empty()) {
            imshow("Image", image);
            key = waitKey(40);
        }
    }
    
    cout << "Thread image show ended." << endl;
    return NULL;
}
