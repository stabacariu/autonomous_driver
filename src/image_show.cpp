/**
 * @file image_show.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "image_show.hpp"
#include <wiringPi.h>

void *showInputImage (void *arg)
{
    std::cout << "THREAD: Show input image started." << std::endl;

    initOutputImageData();
    time_t prevTs = 0;

    while ((getModuleState() & MODULE_SHOW_IN_IMAGE) == MODULE_SHOW_IN_IMAGE) {
        cv::Mat image;
        time_t ts = getInputImageData(image);

        if (!image.empty()) {
            // Undistort captured image
            cv::Mat cameraMatrix, distCoeffs;
            getIntr(cameraMatrix, distCoeffs);
            if (!cameraMatrix.empty() && !distCoeffs.empty()) {
                cv::undistort(image, image, cameraMatrix, distCoeffs);
            }
            // Apply perspective transform
            //~ cv::Mat homography;
            //~ getExtr(homography);
            //~ if (!homography.empty()) {
                //~ cv::warpPerspective(image, image, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            //~ }
            
            
            setOutputImageData(image, ts);
            prevTs = ts;
        }
        // Slow thread down
        //~ delay(20);
    }

    std::cout << "THREAD: Show input image ended." << std::endl;
    return NULL;
}

void *showOutputImage (void *arg)
{
    std::cout << "THREAD: Show output image started." << std::endl;
    
    initOutputImageData();
    time_t prevTs = 0;
    
    // FPS measurement
    time_t frameStartTime, frameEndTime;
    int timeTick = 0;
    long frameCnt = 0;
    
    cv::namedWindow("Autonomous Driver", CV_WINDOW_AUTOSIZE);
    char key = getUiInputKey();
    
    //~ while ((getModuleState() & MODULE_SHOW_OUT_IMAGE) == MODULE_SHOW_OUT_IMAGE) {
    while ((getModuleState() & MODULE_SHOW_OUT_IMAGE) == MODULE_SHOW_OUT_IMAGE) {
        cv::Mat image;
        time_t ts;
        if ((getModuleState() & MODULE_SHOW_IN_IMAGE) == MODULE_SHOW_IN_IMAGE) {
            ts = getInputImageData(image);
        }
        else {
            ts = getOutputImageData(image);
        }
        
        if (image.empty()) {
            cv::Size imageSize = getImageSize();
            image = cv::Mat(imageSize.height, imageSize.width, CV_8UC3, cv::Scalar(0));
            time(&ts);
        }
        
        // FPS measurement
        if (frameCnt == 0) {
            frameStartTime = ts;
        }
        frameCnt++;
        time(&frameEndTime);
        
        if (difftime(frameEndTime, frameStartTime) >= 1) {
            std::cout << "Output FPS: " << frameCnt << std::endl;
            frameCnt = 0;
        }

        // Create output image composition from UI menu and output image
        cv::Mat outputImage = cv::Mat(image.rows, image.cols + 200, CV_8UC3, cv::Scalar(0));

        // Process input and insert menu to output image
        processUiInput(outputImage, key);

        if (!image.empty() && (ts >= prevTs)) {
            // Insert processed image to output image
            cv::Rect insert = cv::Rect(200, 0, image.cols, image.rows);
            image.copyTo(outputImage(insert));

            imshow("Autonomous Driver", outputImage);
            key = cv::waitKey(60);
            setUiInputKey(key);
            prevTs = ts;
        }
    }

    std::cout << "THREAD: Show output image ended." << std::endl;
    return NULL;
}
