/**
 * @file camera_capture.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "camera_capture.hpp"

using namespace std;
using namespace cv;

void *cameraCapture (void *arg)
{
    cout << "THREAD: Camera capture started." << endl;
    // Initalize camera
    VideoCapture camera(getCameraID());
    camera.set(CV_CAP_PROP_FRAME_WIDTH, getImageSize().width);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, getImageSize().height); //480
    camera.set(CV_CAP_PROP_FPS, getFPS());
    
    if (!camera.isOpened()) {
        cerr << "ERROR: Could not open camera!" << endl;
    }
    
    // Initalize image data
    initInputData();
    initOutputData();
    
    // Caputre image
    while ((getModuleState() & MODULE_CAP_CAM_IMAGE) == MODULE_CAP_CAM_IMAGE) {
        Mat image;
        camera >> image;
        if (image.empty()) {
            cerr << "ERROR: Couldn't aquire image data!" << endl;
        }
        else {
            //! @note Do not undistort or warp image here!
            // Undistort captured image
            //~ Mat cameraMatrix, diffCoeffs;
            //~ getIntr(cameraMatrix, diffCoeffs);
            //~ if (!cameraMatrix.empty() && !diffCoeffs.empty()) {
                //~ undistort(image, image, cameraMatrix, diffCoeffs);
            //~ }
            //~ // Apply perspective transform
            //~ Mat homography;
            //~ getExtr(homography);
            //~ if (!homography.empty()) {
                //~ inversePerspectiveTransform(image, image, homography);
            //~ }
            setInputImageData(image);
        }
    }
    
    cout << "THREAD: Camera capture ended." << endl;
    
    return NULL;
}
