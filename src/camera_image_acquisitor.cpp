/**
 * @file camera_capture.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "camera_image_acquisitor.hpp"
#include <ctime>

cv::Mat CameraImageAcquisitor::read ()
{
    return capturedImage;
}

void CameraImageAcquisitor::write (cv::Mat image)
{
    capturedImage = image;
}

void CameraImageAcquisitor::start (ImageData& imageData)
{
    std::cout << "THREAD: Camera capture started." << std::endl;
    running = true;
    
    // Initalize camera
    //~ cv::VideoCapture camera(getCameraID());
    cv::VideoCapture camera(id);
    camera.set(CV_CAP_PROP_FRAME_WIDTH, dimensions.width);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, dimensions.height);
    camera.set(CV_CAP_PROP_FPS, fps);
    //~ camera.set(CV_CAP_PROP_AUTO_EXPOSURE, 3); //! Doesn't work!
    //~ camera.set(CV_CAP_PROP_EXPOSURE, calcExposure(12));
    //~ camera.set(CV_CAP_PROP_EXPOSURE, calcExposure(7));
    
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera!" << std::endl;
    }
    
    // FPS measurement
    time_t frameStart, frameEnd;
    int timeTick = 0;
    long frameTotal = 0;
    long frameCnt = 0;
    
    // Caputre image
    while (running) {
        camera >> capturedImage;
        
        time_t ts;
        time(&ts);
        
        if (frameCnt == 0) {
            frameStart = ts;
        }
        // FPS measurement
        frameCnt++;
        time(&frameEnd);
        
        if (capturedImage.empty()) {
            std::cerr << "ERROR: Couldn't aquire image data!" << std::endl;
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
            
            
            // FPS measurement
            if (difftime(frameEnd, frameStart) >= 3) {
                timeTick++;
                frameTotal += frameCnt;
                //~ std::cout << "Captured FPS: " << frameTotal/timeTick << std::endl;
                std::cout << "Captured FPS: " << frameCnt/3 << std::endl;
                frameCnt = 0;
            }
            imageData.write(capturedImage);
        }
        
    }

    std::cout << "THREAD: Camera capture ended." << std::endl;
}

void CameraImageAcquisitor::runIntrinsicCalibration (ImageData& inputImage, ImageData& outputImage)
{
    std::cout << "THREAD: Intrinsics calibarion started." << std::endl;

    cv::Mat image, warpedImage;
    //~ cv::Mat homography;

    while (running) {
        image = inputImage.read();
        
        if (!image.empty()) {
            calibExtr(image, homography, calibData.patternSize, calibData.patternMm);
        }
        if (!homography.empty()) {
            //~ inversePerspectiveTransform(image, warpedImage, homography);
            warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            line(warpedImage, cv::Point(warpedImage.cols/2, 0), cv::Point(warpedImage.cols/2, warpedImage.rows), cv::Scalar(0, 0, 255), 1);
            line(warpedImage, cv::Point(0, warpedImage.rows/2), cv::Point(warpedImage.cols, warpedImage.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(image);
        }
        else {
            line(image, cv::Point(image.cols/2, 0), cv::Point(image.cols/2, image.rows), cv::Scalar(0, 0, 255), 1);
            line(image, cv::Point(0, image.rows/2), cv::Point(image.cols, image.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(image);
        }
    }

    if (!homography.empty()) {
        //~ setExtr(homography);
        //~ setPxPerMm(calcPixelPerMm(warpedImage, getPatternSize(), getPatternMm()));
        calibData.pixelPerMm = calcPixelPerMm(warpedImage, calibData.patternSize, calibData.patternMm);
    }
    else {
        std::cerr << "Homography couldn't be aquired!" << std::endl;
    }
    
    std::cout << "THREAD: Intrinsics calibarion ended." << std::endl;
}
    
void CameraImageAcquisitor::runExtrinsicCalibration (ImageData& inputImage, ImageData& outputImage) 
{
    std::cout << "THREAD: Extrinsics calibarion started." << std::endl;

    cv::Mat image, warpedImage;
    //~ cv::Mat homography;

    while (running) {
        image = inputImage.read();
        
        if (!image.empty()) {
            //~ calibExtr(image, homography, getPatternSize(), getPatternMm());
            calibExtr(image, homography, calibData.patternSize, calibData.patternMm);
        }
        if (!homography.empty()) {
            //~ inversePerspectiveTransform(image, warpedImage, homography);
            warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            line(warpedImage, cv::Point(warpedImage.cols/2, 0), cv::Point(warpedImage.cols/2, warpedImage.rows), cv::Scalar(0, 0, 255), 1);
            line(warpedImage, cv::Point(0, warpedImage.rows/2), cv::Point(warpedImage.cols, warpedImage.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(image);
        }
        else {
            line(image, cv::Point(image.cols/2, 0), cv::Point(image.cols/2, image.rows), cv::Scalar(0, 0, 255), 1);
            line(image, cv::Point(0, image.rows/2), cv::Point(image.cols, image.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(image);
        }
    }

    if (!homography.empty()) {
        //~ setExtr(homography);
        //~ setPxPerMm(calcPixelPerMm(warpedImage, getPatternSize(), getPatternMm()));
        calibData.pixelPerMm = calcPixelPerMm(warpedImage, calibData.patternSize, calibData.patternMm);
    }
    else {
        std::cerr << "Homography couldn't be aquired!" << std::endl;
    }
    
    std::cout << "THREAD: Extrinsics calibarion ended." << std::endl;
}

void CameraImageAcquisitor::changeImagePosition (ImageData& inputImage, ImageData& outputImage, UserInterfaceData& uiData)
{
    std::cout << "THREAD: Image position configuration started." << std::endl;

    cv::Mat image, adjustedImage;
    
    while (running) {
        image = inputImage.read();
        
        if (!image.empty() && !homography.empty()) {
            char key = uiData.getKey();
            adjustImagePosition(image, adjustedImage, key, homography);
            outputImage.write(adjustedImage);
        }
    }
    
    std::cout << "THREAD: Image position configuration ended." << std::endl;
}

void CameraImageAcquisitor::showChessBoard (ImageData& inputImage, ImageData& outputImage)
{
    std::cout << "THREAD: Show chessboard started." << std::endl;
    
    cv::Mat image;
    
    while (running) {
        image = inputImage.read();
        
        if (!image.empty()) {
            //~ drawChessBoard(image, getPatternSize());
            drawChessBoard(image, calibData.patternSize);
            outputImage.write(image);
        }
    }

    std::cout << "THREAD: Show chessboard ended." << std::endl;
}

double calcExposure (int value)
{
    const int minVal = 5; //!< 500 us or 0.0005 s
    const int maxVal = 20000; //!< 20000 us or 2 s
    const double range = maxVal-minVal; //!< Exposure range in 100 us

    return ((maxVal/pow(2.0, value)) - minVal) / range;
}

void calcBoardCornerPosition (cv::Size calibPatternSize, float calibPatternMm, std::vector<cv::Point3f>& corners)
{
    corners.clear();
    // Calculate corner position of chessboard squares
    for (auto i = 0; i < calibPatternSize.height; i++) {
        for (auto j = 0; j < calibPatternSize.width; j++) {
            corners.push_back(cv::Point3f(j*calibPatternMm, i*calibPatternMm, 0));
        }
    }
}

void calibIntr (cv::Mat image, cv::Mat& cameraMatrix, cv::Mat& distCoeffs, cv::Size calibPatternSize, double calibPatternMm)
{
    double aspRatio = 1.0;

    std::vector<std::vector<cv::Point2f> >imagePoints;
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;

    bool found = findChessboardCorners(image, calibPatternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        // Save corners
        imagePoints.push_back(corners);
    }
    
    cameraMatrix = cv::Mat::eye(3, 3, CV_64F); //< Intrinsic camera matrix
    distCoeffs = cv::Mat::zeros(8, 1, CV_64F); //!< Distorion coefficients
    std::vector<cv::Mat> rvecs; //< Rotation vectors
    std::vector<cv::Mat> tvecs; //< Translation vectors

    // Set aspect ratio
    cameraMatrix.at<double>(1, 1) = aspRatio;
    // Calculate cornerpoints
    std::vector<std::vector<cv::Point3f> > objectPoints(1);
    calcBoardCornerPosition(calibPatternSize, calibPatternMm, objectPoints[0]);
    objectPoints.resize(imagePoints.size(), objectPoints[0]);

    // Calibrate camera and get reprojection error rms
    double rms = calibrateCamera(objectPoints, imagePoints, cv::Size(image.cols, image.rows), cameraMatrix, distCoeffs, rvecs, tvecs, CV_CALIB_USE_INTRINSIC_GUESS);
    
    // Wait to reposition chessboard

    //std::vector<double> reprojErrs;
    //double totalAvgError = computeReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs, 1);
}

void calibExtr (cv::Mat image, cv::Mat& homography, cv::Size calibPatternSize, double calibPatternMm)
{
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool found = findChessboardCorners(image, calibPatternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

        cv::Point2f objectPoints[4];
        objectPoints[0] = cv::Point2f(0, 0);
        objectPoints[1] = cv::Point2f((calibPatternSize.width-1)*calibPatternMm, 0);
        objectPoints[2] = cv::Point2f(0, (calibPatternSize.height-1)*calibPatternMm);
        objectPoints[3] = cv::Point2f((calibPatternSize.width-1)*calibPatternMm, (calibPatternSize.height-1)*calibPatternMm);
        cv::Point2f imagePoints[4];
        imagePoints[0] = corners[0];
        imagePoints[1] = corners[calibPatternSize.width-1];
        imagePoints[2] = corners[(calibPatternSize.height-1)*calibPatternSize.width];
        imagePoints[3] = corners[(calibPatternSize.height-1)*calibPatternSize.width + calibPatternSize.width-1];


        homography = getPerspectiveTransform(objectPoints, imagePoints);

        // Shift to image center
        cv::Mat t = cv::Mat::eye(3, 3, CV_64F);
        t.at<double>(0, 2) = 0.5*(image.cols-1) * (-1) + 0.5 * (calibPatternMm * 0.5 * (calibPatternSize.width-1)); // Shift width
        t.at<double>(1, 2) = (image.rows-1) * (-1) + 1.5 * (calibPatternMm * 0.5 * (calibPatternSize.height-1)); // Shift height
        t.at<double>(2, 2) = 0.5;
        homography *= t;
    }
}

float euclidDist (cv::Point2f p1, cv::Point2f p2)
{
    cv::Point2f diff = p1 - p2;
    return sqrt(diff.x*diff.x + diff.y*diff.y);
}

float calcPixelPerMm (cv::Mat image, cv::Size calibPatternSize, float calibPatternMm)
{
    float pxDist;
    float avgPxDist = 0.0;
    int distCnt = 0;
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool found = findChessboardCorners(image, calibPatternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, calibPatternMm, 0.1));

        for (auto i = 0; i < (corners.size()-1); i++) {
            if ((i%calibPatternSize.width) < (calibPatternSize.width-1)) {
                pxDist = euclidDist(corners[i+1], corners[i]);
                avgPxDist += pxDist;
                distCnt++;
            }
            else {
                i++;
            }
        }
        avgPxDist /= distCnt;
        std::cout << "Avg distance in px " << avgPxDist << std::endl;
        std::cout << "Px per mm " << avgPxDist/calibPatternMm << std::endl;
    }
    return avgPxDist/calibPatternMm;
}

void drawChessBoard (cv::Mat& image, cv::Size calibPatternSize)
{
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool found = findChessboardCorners(grayImage, calibPatternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        drawChessboardCorners(image, calibPatternSize, corners, found);
    }
}

void adjustImagePosition (cv::Mat image, cv::Mat& adjustedImage, char key, cv::Mat& homography)
{
    double xOffset = 0;
    double yOffset = 0;
    double zOffset = 0;

    if (!image.empty()) {
        // Zoom in
        if (key == '+') {
            zOffset = -5;
        }
        // Zoom out
        else if (key == '-') {
            zOffset = 5;
        }
        // Move left
        else if (key == 'a') {
            xOffset = -5;
        }
        // Move up
        else if (key == 'w') {
            yOffset = -5;
        }
        // Move right
        else if (key == 'd') {
            xOffset = 5;
        }
        // Move down
        else if (key == 's') {
            yOffset = 5;
        }

        if (homography.empty()) {
            homography = cv::Mat::eye(3, 3, CV_64F);
        }
        homography.at<double>(0, 2) += xOffset;
        homography.at<double>(1, 2) += yOffset;
        homography.at<double>(2, 2) += zOffset;
    }
}
