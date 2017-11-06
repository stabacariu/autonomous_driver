/**
 * @file image_show.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_show.hpp"

using namespace std;
using namespace cv;

/**
 * @brief Thread to copy input image to output image.
 */
void *showInputImage (void *arg)
{
    cout << "THREAD: Show input image started." << endl;
    
    while ((getModuleState() & MODULE_SHOW_IN_IMAGE) == MODULE_SHOW_IN_IMAGE) {
        Mat image;
        getInputImageData(image);
        
        // Undistort captured image
        Mat cameraMatrix, diffCoeffs;
        getIntrinsics(cameraMatrix, diffCoeffs);
        if (!cameraMatrix.empty() && !diffCoeffs.empty()) {
            undistort(image, image, cameraMatrix, diffCoeffs);
        }
        // Apply perspective transform
        Mat homography;
        getExtrinsics(homography);
        if (!homography.empty()) {
            inversePerspectiveTransform(image, image, homography);
        }
        
        setOutputImageData(image);
    }
    
    cout << "THREAD: Show input image ended." << endl;
    return NULL;
}

/**
 * @brief Thread for showing output image on GUI.
 */
void *showOutputImage (void *arg)
{
    cout << "THREAD: Show output image started." << endl;
    namedWindow("Autonomous Driver", CV_WINDOW_AUTOSIZE);
    char key = getUiInputKey();
    
    while ((getModuleState() & MODULE_SHOW_OUT_IMAGE) == MODULE_SHOW_OUT_IMAGE) {
        Mat image;
        getOutputImageData(image);
        
        if (image.empty()) {
            image = Mat(640, 360, CV_8UC3, Scalar(0));
        }
        
        // Create output image composition from UI menu and output image
        Mat outputImage = Mat(image.rows, image.cols + 200, CV_8UC3, Scalar(0));
        
        // Process input and insert menu to output image
        processUiInput(outputImage, key);
        
        if (!image.empty()) {
            // Insert processed image to output image
            Rect insert = Rect(200,0, image.cols, image.rows);
            image.copyTo(outputImage(insert));
            
            imshow("Autonomous Driver", outputImage);
            key = waitKey(20);
            setUiInputKey(key);
        }
    }
    
    cout << "THREAD: Show output image ended." << endl;
    return NULL;
}
