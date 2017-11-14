/**
 * @file image_show.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_show.hpp"

/**
 * @brief Thread to copy input image to output image.
 */
void *showInputImage (void *arg)
{
    std::cout << "THREAD: Show input image started." << std::endl;
    
    while ((getModuleState() & MODULE_SHOW_IN_IMAGE) == MODULE_SHOW_IN_IMAGE) {
        cv::Mat image;
        getInputImageData(image);
        
        if (!image.empty()) {
            // Undistort captured image
            cv::Mat cameraMatrix, diffCoeffs;
            getIntr(cameraMatrix, diffCoeffs);
            if (!cameraMatrix.empty() && !diffCoeffs.empty()) {
                cv::undistort(image, image, cameraMatrix, diffCoeffs);
            }
            // Apply perspective transform
            cv::Mat homography;
            getExtr(homography);
            if (!homography.empty()) {
                cv::warpPerspective(image, image, homography, image.size(), CV_INTER_LINEAR);
            }
            
            setOutputImageData(image);
        }
    }
    
    std::cout << "THREAD: Show input image ended." << std::endl;
    return NULL;
}

/**
 * @brief Thread for showing output image on GUI.
 */
void *showOutputImage (void *arg)
{
    std::cout << "THREAD: Show output image started." << std::endl;
    
    cv::namedWindow("Autonomous Driver", CV_WINDOW_AUTOSIZE);
    char key = getUiInputKey();
    
    while ((getModuleState() & MODULE_SHOW_OUT_IMAGE) == MODULE_SHOW_OUT_IMAGE) {
        cv::Mat image;
        getOutputImageData(image);
        
        if (image.empty()) {
            cv::Size imageSize = getImageSize();
            image = cv::Mat(imageSize.width, imageSize.height, CV_8UC3, cv::Scalar(0));
        }
        else {
            // Invers perspective transform to normal view
            //~ cv::Mat homography;
            //~ getExtr(homography);
            //~ if (!homography.empty()) {
                //~ cv::warpPerspective(image, image, homography, image.size(), CV_INTER_LINEAR);
            //~ }
        }
        
        // Create output image composition from UI menu and output image
        cv::Mat outputImage = cv::Mat(image.rows, image.cols + 200, CV_8UC3, cv::Scalar(0));
        
        // Process input and insert menu to output image
        processUiInput(outputImage, key);
        
        if (!image.empty()) {
            // Insert processed image to output image
            cv::Rect insert = cv::Rect(200,0, image.cols, image.rows);
            image.copyTo(outputImage(insert));
            
            imshow("Autonomous Driver", outputImage);
            key = cv::waitKey(20);
            setUiInputKey(key);
        }
    }
    
    std::cout << "THREAD: Show output image ended." << std::endl;
    return NULL;
}
