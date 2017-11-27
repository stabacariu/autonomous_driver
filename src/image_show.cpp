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

    initOutputData();

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
            //~ cv::Mat homography;
            //~ getExtr(homography);
            //~ if (!homography.empty()) {
                //~ cv::warpPerspective(image, image, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            //~ }

            setOutputImageData(image);
        }
    }

    std::cout << "THREAD: Show input image ended." << std::endl;
    return NULL;
}

bool compareImage(const cv::Mat m1, const cv::Mat m2)
{
    if (m1.empty() && m2.empty()) {
        return true;
    }
    else if ((m1.cols != m2.cols) || (m1.rows != m2.rows) || (m1.dims != m2.dims)) {
        return false;
    }

    cv::Mat diff;
    cv::compare(m1, m2, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    return nz == 0;
}

/**
 * @brief Thread for showing output image on GUI.
 */
void *showOutputImage (void *arg)
{
    std::cout << "THREAD: Show output image started." << std::endl;
    
    initOutputData();
    
    cv::namedWindow("Autonomous Driver", CV_WINDOW_AUTOSIZE);
    char key = getUiInputKey();
    
    cv::Mat image;
    while ((getModuleState() & MODULE_SHOW_OUT_IMAGE) == MODULE_SHOW_OUT_IMAGE) {
        //~ cv::Mat newImage;
        //~ getOutputImageData(newImage);
        //~ 
        //~ if ((!newImage.empty()) && (!image.empty())) {
            //~ cv::Mat grayImage, grayNewImage;
            //~ cvtColor(image, grayImage, CV_BGR2GRAY);
            //~ cvtColor(newImage, grayNewImage, CV_BGR2GRAY);
            //~ 
            //~ if (!compareImage(grayImage, grayNewImage)) {
                //~ newImage.copyTo(image);
            //~ }
        //~ }
        
        cv::Mat image;
        getOutputImageData(image);
        
        if (image.empty()) {
            cv::Size imageSize = getImageSize();
            image = cv::Mat(imageSize.height, imageSize.width, CV_8UC3, cv::Scalar(0));
        }

        // Create output image composition from UI menu and output image
        cv::Mat outputImage = cv::Mat(image.rows, image.cols + 200, CV_8UC3, cv::Scalar(0));

        // Process input and insert menu to output image
        processUiInput(outputImage, key);

        if (!image.empty()) {
            // Insert processed image to output image
            cv::Rect insert = cv::Rect(200, 0, image.cols, image.rows);
            image.copyTo(outputImage(insert));

            imshow("Autonomous Driver", outputImage);
            key = cv::waitKey(20);
            setUiInputKey(key);
        }
    }

    std::cout << "THREAD: Show output image ended." << std::endl;
    return NULL;
}
