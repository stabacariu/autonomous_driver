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
    VideoCapture camera(CV_CAP_ANY);
    camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 360); //480
    camera.set(CV_CAP_PROP_FPS, 10);
    
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
            //~ Mat intrinsics, diffCoeffs;
            //~ getIntrinsics(intrinsics, diffCoeffs);
            //~ if (!intrinsics.empty() && !diffCoeffs.empty()) {
                //~ undistort(image, image, intrinsics, diffCoeffs);
            //~ }
            //~ // Apply perspective transform
            //~ Mat homography;
            //~ getHomography(homography);
            //~ if (!homography.empty()) {
                //~ inversePerspectiveTransform(image, image, homography);
            //~ }
            setInputImageData(image);
        }
    }
    
    cout << "THREAD: Camera capture ended." << endl;
    
    return NULL;
}
