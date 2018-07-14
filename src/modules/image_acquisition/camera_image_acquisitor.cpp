/**
 * @file camera_capture.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "camera_image_acquisitor.hpp"
#include <thread>
#include "configuration.hpp"

cv::Mat CameraImageAcquisitor::read ()
{
    return capturedImage;
}

void CameraImageAcquisitor::write (cv::Mat image)
{
    capturedImage = image;
}

void CameraImageAcquisitor::run (ImageData& imageData)
{
    std::cout << "THREAD: Camera capture started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camConfig = config.camConfig;
    
    // Initalize camera
    cv::VideoCapture camera(camConfig.id);
    camera.set(CV_CAP_PROP_FRAME_WIDTH, camConfig.imageSize.width);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, camConfig.imageSize.height);
    camera.set(CV_CAP_PROP_FPS, camConfig.fps);
    //~ camera.set(CV_CAP_PROP_EXPOSURE, calcExposure(12));
    //~ camera.set(CV_CAP_PROP_EXPOSURE, calcExposure(7));
    
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera!" << std::endl;
    }
    
    // FPS measurement
    std::chrono::high_resolution_clock::time_point frameTimerStart, frameTimerEnd;
    long frameCnt = 0;
    
    // Caputre image
    while (running) {
        camera >> capturedImage;
        
        if (frameCnt == 0) {
            frameTimerStart = std::chrono::high_resolution_clock::now();
        }
        
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
            //~ cv::Mat camCalibConfig.homography;
            //~ getExtr(camCalibConfig.homography);
            //~ if (!camCalibConfig.homography.empty()) {
                //~ inversePerspectiveTransform(image, image, camCalibConfig.homography);
            //~ }
            
            // FPS measurement
            frameCnt++;
            frameTimerEnd = std::chrono::high_resolution_clock::now();
            
            if (std::chrono::duration_cast<std::chrono::seconds>(frameTimerEnd - frameTimerStart).count() >= 3) {
                std::cout << "Captured FPS: " << frameCnt/3 << std::endl;
                frameCnt = 0;
            }
            imageData.write(capturedImage);
        }
        
    }

    std::cout << "THREAD: Camera capture ended." << std::endl;
}

void CameraImageAcquisitor::runIntrinsicCalibration (ImageData& inputImage, ImageData& outputImage, UserInterfaceState& uiState)
{
    std::cout << "THREAD: Intrinsics calibarion started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camCalibConfig = config.getCameraCalibrationConfig();
    
    bool saveConfigFlag = false;

    cv::Mat image, undistorted, cameraMatrix, distCoeffs;
    std::vector<std::vector<cv::Point2f> > imagePoints;
    int sampleCnt = 0;

    while (running) {
        image = inputImage.read();
        
        if (!image.empty() && (sampleCnt <= camCalibConfig.numSamples)) {
            bool ok = calibrateIntrinsics(image, cameraMatrix, distCoeffs, imagePoints, camCalibConfig.patternSize, camCalibConfig.patternMm);
            if (ok) {
                sampleCnt++;
            }
            std::cout << "Calibration sample counter: " << sampleCnt << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        
        if (!cameraMatrix.empty() && !distCoeffs.empty()) {
            cv::undistort(image, undistorted, cameraMatrix, distCoeffs);
            line(undistorted, cv::Point(undistorted.cols/2, 0), cv::Point(undistorted.cols/2, undistorted.rows), cv::Scalar(0, 0, 255), 1);
            line(undistorted, cv::Point(0, undistorted.rows/2), cv::Point(undistorted.cols, undistorted.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(undistorted);
        }
        else {
            line(image, cv::Point(image.cols/2, 0), cv::Point(image.cols/2, image.rows), cv::Scalar(0, 0, 255), 1);
            line(image, cv::Point(0, image.rows/2), cv::Point(image.cols, image.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(image);
        }
        
        if (uiState.getKey() == 'S') {
            saveConfigFlag = true;
        }
    }
    
    if ((sampleCnt == camCalibConfig.numSamples) && (!cameraMatrix.empty() && !distCoeffs.empty())) {
        camCalibConfig.cameraMatrix = cameraMatrix;
        camCalibConfig.distCoeffs = distCoeffs;
        camCalibConfig.timeOfIntrCalib = std::chrono::high_resolution_clock::now();
        camCalibConfig.intrCalibDone = true;
    }
    else {
        camCalibConfig.intrCalibDone = false;
        std::cerr << "WARNING: Intrinsic camera calibration not successful!" << std::endl;
    }
    
    if (saveConfigFlag && camCalibConfig.intrCalibDone) {
        config.setCameraCalibrationConfig(camCalibConfig);
        config.saveCameraCalibrationConfig();
        config.save();
        std::cout << "THREAD: Intrinsic camera calibration saved!" << std::endl;
    }
    
    std::cout << "THREAD: Intrinsics calibarion ended." << std::endl;
}
    
void CameraImageAcquisitor::runExtrinsicCalibration (ImageData& inputImage, ImageData& outputImage, UserInterfaceState& uiState) 
{
    std::cout << "THREAD: Extrinsics calibarion started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camCalibConfig = config.getCameraCalibrationConfig();
    
    bool saveConfigFlag = false;

    cv::Mat image, warpedImage, homography;

    while (running) {
        image = inputImage.read();
        
        if (!image.empty()) {
            calibrateExtrinsics(image, homography, camCalibConfig.patternSize, camCalibConfig.patternMm);
            //~ calibrateExtrinsics(image, camCalibConfig.homography, camCalibConfig.patternSize, camCalibConfig.patternMm);
        }
        
        if (!image.empty() && !homography.empty()) {
        //~ if (!image.empty() && !camCalibConfig.homography.empty()) {
            //~ inversePerspectiveTransform(image, warpedImage, camCalibConfig.homography);
            warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            //~ warpPerspective(image, warpedImage, camCalibConfig.homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            line(warpedImage, cv::Point(warpedImage.cols/2, 0), cv::Point(warpedImage.cols/2, warpedImage.rows), cv::Scalar(0, 0, 255), 1);
            line(warpedImage, cv::Point(0, warpedImage.rows/2), cv::Point(warpedImage.cols, warpedImage.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(warpedImage);
        }
        else {
            line(image, cv::Point(image.cols/2, 0), cv::Point(image.cols/2, image.rows), cv::Scalar(0, 0, 255), 1);
            line(image, cv::Point(0, image.rows/2), cv::Point(image.cols, image.rows/2), cv::Scalar(0, 0, 255), 1);
            outputImage.write(image);
        }

        if (uiState.getKey() == 'S') {
            saveConfigFlag = true;
            std::cout << "Saving extrinsic camera calibration." << std::endl;
        }
    }

    if (!homography.empty()) {
        camCalibConfig.homography = homography;
        camCalibConfig.mmPerPixel = calcPixelPerMm(warpedImage, camCalibConfig.patternSize, camCalibConfig.patternMm);
        camCalibConfig.timeOfExtrCalib = std::chrono::high_resolution_clock::now();
        camCalibConfig.extrCalibDone = true;
        std::cout << "Avg px per mm: " << camCalibConfig.mmPerPixel << std::endl;
    }
    else {
        camCalibConfig.extrCalibDone = false;
        std::cerr << "WARNING: Extrinsic camera calibration not successful!" << std::endl;
    }
    
    if (saveConfigFlag && camCalibConfig.extrCalibDone) {
        config.setCameraCalibrationConfig(camCalibConfig);
        config.saveCameraCalibrationConfig();
        config.save();
        std::cout << "THREAD: Intrinsic camera calibration saved!" << std::endl;
    }
        
    std::cout << "THREAD: Extrinsics calibarion ended." << std::endl;
}

void CameraImageAcquisitor::runImageAdjustment (ImageData& inputImage, ImageData& outputImage, UserInterfaceState& uiState)
{
    std::cout << "THREAD: Image position configuration started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camCalibConfig = config.getCameraCalibrationConfig();

    cv::Mat image, adjustedImage;
    
    while (running) {
        image = inputImage.read();
        
        if (!image.empty() && !camCalibConfig.homography.empty()) {
            char key = uiState.getKey();
            adjustImagePosition(image, adjustedImage, key, camCalibConfig.homography);
            outputImage.write(adjustedImage);
        }
    }
    
    std::cout << "THREAD: Image position configuration ended." << std::endl;
}

void CameraImageAcquisitor::runChessBoardShow (ImageData& inputImage, ImageData& outputImage)
{
    std::cout << "THREAD: Show chessboard started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camCalibConfig = config.getCameraCalibrationConfig();
    
    cv::Mat image;
    
    while (running) {
        image = inputImage.read();
        
        if (!image.empty()) {
            drawChessBoard(image, camCalibConfig.patternSize);
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

void calcBoardCornerPosition (cv::Size patternSize, float patternMm, std::vector<cv::Point3f>& corners)
{
    corners.clear();
    // Calculate corner position of chessboard squares
    for (auto i = 0; i < patternSize.height; i++) {
        for (auto j = 0; j < patternSize.width; j++) {
            corners.push_back(cv::Point3f(j*patternMm, i*patternMm, 0));
        }
    }
}

bool calibrateIntrinsics (cv::Mat& image, cv::Mat& cameraMatrix, cv::Mat& distCoeffs, std::vector<std::vector<cv::Point2f> > imagePoints, cv::Size patternSize, double patternMm)
{
    double aspRatio = 1.0;
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;

    bool found = cv::findChessboardCorners(image, patternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        // Save corners
        imagePoints.push_back(corners);
        
        drawChessboardCorners(image, patternSize, corners, found);
    }
    
    cameraMatrix = cv::Mat::eye(3, 3, CV_64F); //< Intrinsic camera matrix
    distCoeffs = cv::Mat::zeros(8, 1, CV_64F); //!< Distorion coefficients
    std::vector<cv::Mat> rvecs; //< Rotation vectors
    std::vector<cv::Mat> tvecs; //< Translation vectors

    // Set aspect ratio
    cameraMatrix.at<double>(0, 0) = aspRatio;
    // Calculate cornerpoints
    std::vector<std::vector<cv::Point3f> > objectPoints(1);
    calcBoardCornerPosition(patternSize, patternMm, objectPoints[0]);
    objectPoints.resize(imagePoints.size(), objectPoints[0]);
    
    if (imagePoints.size() > 0) {
        // Calibrate camera and get reprojection error rms
        double rms = cv::calibrateCamera(objectPoints, imagePoints, cv::Size(image.cols, image.rows), cameraMatrix, distCoeffs, rvecs, tvecs, CV_CALIB_USE_INTRINSIC_GUESS);
    }
    bool ok = cv::checkRange(cameraMatrix) && cv::checkRange(distCoeffs);

    //std::vector<double> reprojErrs;
    //double totalAvgError = computeReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs, 1);
    return ok;
}

void calibrateExtrinsics (cv::Mat& image, cv::Mat& homography, cv::Size patternSize, double patternMm)
{
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool found = findChessboardCorners(image, patternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

        cv::Point2f objectPoints[4];
        objectPoints[0] = cv::Point2f(0, 0);
        objectPoints[1] = cv::Point2f((patternSize.width-1)*patternMm, 0);
        objectPoints[2] = cv::Point2f(0, (patternSize.height-1)*patternMm);
        objectPoints[3] = cv::Point2f((patternSize.width-1)*patternMm, (patternSize.height-1)*patternMm);
        cv::Point2f imagePoints[4];
        imagePoints[0] = corners[0];
        imagePoints[1] = corners[patternSize.width-1];
        imagePoints[2] = corners[(patternSize.height-1)*patternSize.width];
        imagePoints[3] = corners[(patternSize.height-1)*patternSize.width + patternSize.width-1];


        homography = getPerspectiveTransform(objectPoints, imagePoints);

        // Shift to image center
        cv::Mat t = cv::Mat::eye(3, 3, CV_64F);
        t.at<double>(0, 2) = 0.5*(image.cols-1) * (-1) + 0.5 * (patternMm * 0.5 * (patternSize.width-1)); // Shift width
        t.at<double>(1, 2) = (image.rows-1) * (-1) + 1.5 * (patternMm * 0.5 * (patternSize.height-1)); // Shift height
        t.at<double>(2, 2) = 0.5;
        homography *= t;
        
        drawChessboardCorners(image, patternSize, corners, found);
    }
}

float euclidDist (cv::Point2f p1, cv::Point2f p2)
{
    cv::Point2f diff = p1 - p2;
    return sqrt(diff.x*diff.x + diff.y*diff.y);
}

float calcPixelPerMm (cv::Mat image, cv::Size patternSize, float patternMm)
{
    float pxDist;
    float avgPxDist = 0.0;
    int distCnt = 0;
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool found = findChessboardCorners(image, patternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, patternMm, 0.1));

        for (auto i = 0; i < (corners.size()-1); i++) {
            if ((i%patternSize.width) < (patternSize.width-1)) {
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
        std::cout << "Px per mm " << avgPxDist/patternMm << std::endl;
    }
    return avgPxDist/patternMm;
}

void drawChessBoard (cv::Mat& image, cv::Size patternSize)
{
    cv::Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    bool found = findChessboardCorners(grayImage, patternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        drawChessboardCorners(image, patternSize, corners, found);
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
