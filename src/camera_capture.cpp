/**
 * @file camera_capture.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "camera_capture.hpp"

double calcExposure (int value)
{
    const int minVal = 5; //!< 500 us or 0.0005 s
    const int maxVal = 20000; //!< 20000 us or 2 s
    const double range = maxVal-minVal; //!< Exposure range in 100 us

    return ((maxVal/pow(2.0, value)) - minVal) / range;
}

void *cameraCapture (void *arg)
{
    std::cout << "THREAD: Camera capture started." << std::endl;
    // Initalize camera
    //~ cv::VideoCapture camera(getCameraID());
    cv::VideoCapture camera(CV_CAP_ANY);
    camera.set(CV_CAP_PROP_FRAME_WIDTH, getImageSize().width);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, getImageSize().height);
    camera.set(CV_CAP_PROP_FPS, getFPS());
    //~ camera.set(CV_CAP_PROP_AUTO_EXPOSURE, 3);
    //~ camera.set(CV_CAP_PROP_EXPOSURE, 156);

    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera!" << std::endl;
    }

    // Initalize image data
    initInputImageData();

    // Caputre image
    while ((getModuleState() & MODULE_CAP_CAM_IMAGE) == MODULE_CAP_CAM_IMAGE) {
        cv::Mat image;
        camera >> image;
        if (image.empty()) {
            std::cerr << "ERROR: Couldn't aquire image data!" << std::endl;
            //~ setModuleState(MODULE_NONE);
        }
        else {
            //! @note Do not undistort or warp image here!
            // Undistort captured image
            //~ cv::Mat cameraMatrix, distCoeffs;
            //~ getIntr(cameraMatrix, distCoeffs);
            //~ if (!cameraMatrix.empty() && !distCoeffs.empty()) {
                //~ undistort(image, image, cameraMatrix, distCoeffs);
            //~ }
            //~ // Apply perspective transform
            //~ cv::Mat homography;
            //~ getExtr(homography);
            //~ if (!homography.empty()) {
                //~ inversePerspectiveTransform(image, image, homography);
            //~ }
            setInputImageData(image);
        }
    }

    std::cout << "THREAD: Camera capture ended." << std::endl;

    return NULL;
}
