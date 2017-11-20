/**
 * @file configuration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 18.09.2017
 */

#include "configuration.hpp"

ConfigData config;
ConfigState configState;

void initConfig (void)
{
    //! @todo Load config from file
    pthread_mutex_init(&config.lock, NULL);
    configState.mode = CONFIG_MODE_NONE;
    pthread_mutex_init(&configState.lock, NULL);

    ConfigData c;
    cv::FileStorage fs("../config/config.xml", cv::FileStorage::READ);
    if (!fs.isOpened()) {
        fs.release();
        fs.open("../config/default.xml", cv::FileStorage::READ);
        if (!fs.isOpened()) {
            std::cerr << "Couldn't open config file. Generate default config file..." << std::endl;
            generateDefaultConfig();
        }
        else {
            loadDefaultConfig(fs, c);
            if (validateConfig(c)) {
                setConfigData(c);
            }
            else {
                std::cerr << "Invalid config data! Abort..." << std::endl;
            }
        }
    }
    else {
        loadConfig(fs, c);
        if (validateConfig(c)) {
            setConfigData(c);
        }
        else {
            std::cerr << "Invalid config data! Loading default config..." << std::endl;
        }
    }

    fs.release();
}

int getCameraID (void)
{
    int cameraID;

    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    cameraID = config.cameraID;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return cameraID;
}

int getFPS (void)
{
    int cameraFPS;

    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    cameraFPS = config.cameraFPS;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return cameraFPS;
}

cv::Size getImageSize (void)
{
    cv::Size imageSize;

    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    imageSize = config.cameraImageSize;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return imageSize;
}

cv::Size getPatternDim (void)
{
    cv::Size calibPatternDim;

    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    calibPatternDim = config.calibPatternDim;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return calibPatternDim;
}

double getPatternSize (void)
{
    double calibPatternSize;

    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    calibPatternSize = config.calibPatternSize;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return calibPatternSize;
}

void setIntr (cv::Mat cameraMatrix, cv::Mat diffCoeffs)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    config.cameraMatrix = cameraMatrix;
    config.diffCoeffs = diffCoeffs;
    if (!cameraMatrix.empty() || !diffCoeffs.empty()) {
        config.calibIntrDone = true;
    }
    else {
        config.calibIntrDone = false;
    }

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void getIntr (cv::Mat& cameraMatrix, cv::Mat& diffCoeffs)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    cameraMatrix = config.cameraMatrix;
    diffCoeffs = config.diffCoeffs;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void setExtr (cv::Mat homography)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    config.homography = homography;
    if (!homography.empty()) {
        config.calibExtrDone = true;
    }
    else {
        config.calibExtrDone = false;
    }

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void getExtr (cv::Mat& homography)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    homography = config.homography;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void setPxPerMm (float pxPerMm)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    config.pixelPerMm = pxPerMm;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

float getPxPerMm (void)
{
    float pxPerMm;

    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    pxPerMm = config.pixelPerMm;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return pxPerMm;
}

ConfigData getConfigData (void)
{
    ConfigData c;

    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    c.cameraID = config.cameraID;
    c.cameraImageSize = config.cameraImageSize;
    c.cameraFPS = config.cameraFPS;

    c.calibImageSize = config.calibImageSize;
    c.calibPattern = config.calibPattern;
    c.calibPatternDim = config.calibPatternDim;
    c.calibPatternSize = config.calibPatternSize;

    c.calibIntrDone = config.calibIntrDone;
    c.cameraMatrix = config.cameraMatrix;
    c.diffCoeffs = config.diffCoeffs;
    c.calibExtrDone = config.calibExtrDone;
    c.homography = config.homography;
    c.transformation = config.transformation;
    c.pixelPerMm = config.pixelPerMm;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return c;
}

void setConfigData (ConfigData c)
{
    if (pthread_mutex_lock(&config.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    config.cameraID = c.cameraID;
    config.cameraImageSize = c.cameraImageSize;
    config.cameraFPS = c.cameraFPS;

    config.calibImageSize = c.calibImageSize;
    config.calibPattern = c.calibPattern;
    config.calibPatternDim = c.calibPatternDim;
    config.calibPatternSize = c.calibPatternSize;
    config.calibSampleCount = c.calibSampleCount;

    config.calibIntrDone = c.calibIntrDone;
    config.cameraMatrix = c.cameraMatrix;
    config.diffCoeffs = c.diffCoeffs;

    config.calibIntrDone = c.calibIntrDone;
    config.homography = c.homography;
    config.transformation = c.transformation;
    config.pixelPerMm = c.pixelPerMm;

    config.validData = c.validData;

    if (pthread_mutex_unlock(&config.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

void setConfigState (ConfigMode mode)
{
    if (pthread_mutex_lock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    configState.mode = mode;

    if (pthread_mutex_unlock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }
}

ConfigMode getConfigState (void)
{
    ConfigMode mode;

    if (pthread_mutex_lock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't lock config mutex!" << std::endl;
    }

    mode = configState.mode;

    if (pthread_mutex_unlock(&configState.lock)) {
        std::cerr << "ERROR: Couldn't unlock config mutex!" << std::endl;
    }

    return mode;
}

void generateDefaultConfig (void)
{
    ConfigData c;
    // Camera config
    c.cameraID = CV_CAP_ANY;
    c.cameraImageSize = cv::Size(640, 360);
    c.cameraFPS = 10;
    // Calibration config
    c.calibImageSize = c.cameraImageSize;
    c.calibPattern = "CHESSBOARD";
    c.calibPatternDim = cv::Size(7, 5);
    c.calibPatternSize = 30.0;
    c.calibSampleCount = 50;
    c.calibIntrDone = false;
    c.calibExtrDone = false;
    c.validData = false;

    c.defaultConfigFileName = "../config/default.xml";

    setConfigData(c);

    cv::FileStorage fs(c.defaultConfigFileName, cv::FileStorage::WRITE);

    fs.writeComment("Camera config");
    fs << "cameraID" << c.cameraID
    << "cameraImageSize_width" << c.cameraImageSize.width
    << "cameraImageSize_height" << c.cameraImageSize.height
    << "cameraFPS" << c.cameraFPS;

    fs.writeComment("Calibration config");
    fs << "calibImageSize_width" << c.calibImageSize.width
    << "calibImageSize_height" << c.calibImageSize.height
    << "calibPattern" << c.calibPattern
    << "calibPatternDim_width" << c.calibPatternDim.width
    << "calibPatternDim_height" << c.calibPatternDim.height
    << "calibPatternSize" << c.calibPatternSize
    << "calibIntrDone" << c.calibIntrDone
    << "calibExtrDone" << c.calibExtrDone
    << "validData" << c.validData;
}

void loadDefaultConfig (cv::FileStorage fs, ConfigData& c)
{
    fs["cameraID"] >> c.cameraID;
    fs["cameraImageSize_width"] >> c.cameraImageSize.width;
    fs["cameraImageSize_height"] >> c.cameraImageSize.height;
    fs["cameraFPS"] >> c.cameraFPS;

    fs["calibImageSize_width"] >> c.calibImageSize.width;
    fs["calibImageSize_height"] >> c.calibImageSize.height;
    fs["calibPattern"] >> c.calibPattern;
    fs["calibPatternDim_width"] >> c.calibPatternDim.width;
    fs["calibPatternDim_height"] >> c.calibPatternDim.height;
    fs["calibPatternSize"] >> c.calibPatternSize;
    fs["calibSampleCount"] >> c.calibSampleCount;

    fs["calibIntrDone"] >> c.calibIntrDone;
    fs["calibExtrDone"] >> c.calibExtrDone;
}

void saveCalibConfig (cv::FileStorage& fs, ConfigData c)
{
    fs.writeComment("Camera config");
    fs << "cameraID" << c.cameraID
    << "cameraImageSize_width" << c.cameraImageSize.width
    << "cameraImageSize_height" << c.cameraImageSize.height
    << "cameraFPS" << c.cameraFPS;

    fs.writeComment("Calibration config");
    fs << "calibImageSize_width" << c.calibImageSize.width
    << "calibImageSize_height" << c.calibImageSize.height
    << "calibPattern" << c.calibPattern
    << "calibPatternDim_width" << c.calibPatternDim.width
    << "calibPatternDim_height" << c.calibPatternDim.height
    << "calibPatternSize" << c.calibPatternSize;

    fs.writeComment("Calibration data");
    fs << "calibIntrDone" << c.calibIntrDone
    << "cameraMatrix" << c.cameraMatrix
    << "diffCoeffs" << c.diffCoeffs
    << "calibExtrDone" << c.calibExtrDone
    << "homography" << c.homography
    << "transformation" << c.transformation
    << "pixelPerMm" << c.pixelPerMm

    << "validData" << c.validData;

    //~ std::cout << "cameraID" << c.cameraID << std::endl
    //~ << "cameraImageSize_width" << c.cameraImageSize.width << std::endl
    //~ << "cameraImageSize_height" << c.cameraImageSize.height  << std::endl
    //~ << "cameraFPS" << c.cameraFPS  << std::endl
    //~
    //~ << "calibImageSize_width" << c.calibImageSize.width  << std::endl
    //~ << "calibImageSize_height" << c.calibImageSize.height << std::endl
    //~ << "calibPattern" << c.calibPattern  << std::endl
    //~ << "calibPatternDim_width" << c.calibPatternDim.width  << std::endl
    //~ << "calibPatternDim_height" << c.calibPatternDim.height  << std::endl
    //~ << "calibPatternSize" << c.calibPatternSize << std::endl
    //~
    //~ << "calibIntrDone" << c.calibIntrDone << std::endl
    //~ << "cameraMatrix" << c.cameraMatrix << std::endl
    //~ << "diffCoeffs" << c.diffCoeffs << std::endl
    //~ << "calibExtrDone" << c.calibExtrDone << std::endl
    //~ << "homography" << c.homography << std::endl
    //~ << "transformation" << c.transformation << std::endl
    //~ << "pixelPerMm" << c.pixelPerMm << std::endl
    //~
    //~ << "validData" << c.validData  << std::endl;
}

void saveCalibConfig (void)
{
    cv::FileStorage fs("../config/config.xml", cv::FileStorage::WRITE);
    ConfigData c = getConfigData();
    saveCalibConfig(fs, c);
}

void loadConfig (cv::FileStorage fs, ConfigData& c)
{
    fs["cameraID"] >> c.cameraID;
    fs["cameraImageSize_width"] >> c.cameraImageSize.width;
    fs["cameraImageSize_height"] >> c.cameraImageSize.height;
    fs["cameraFPS"] >> c.cameraFPS;

    fs["calibImageSize_width"] >> c.calibImageSize.width;
    fs["calibImageSize_height"] >> c.calibImageSize.height;
    fs["calibPattern"] >> c.calibPattern;
    fs["calibPatternDim_width"] >> c.calibPatternDim.width;
    fs["calibPatternDim_height"] >> c.calibPatternDim.height;
    fs["calibPatternSize"] >> c.calibPatternSize;

    fs["calibIntrDone"] >> c.calibIntrDone;
    fs["cameraMatrix"] >> c.cameraMatrix;
    fs["diffCoeffs"] >> c.diffCoeffs;
    fs["calibExtrDone"] >> c.calibExtrDone;
    fs["homography"] >> c.homography;
    fs["transformation"] >> c.transformation;
    fs["pixelPerMm"] >> c.pixelPerMm;

    fs["validData"] >> c.validData;
}

bool validateConfig (ConfigData& c)
{
    c.validData = true;
    if (!(c.cameraID >= 0) || !(c.cameraID <= 9)) {
        c.validData = false;
        std::cerr << "ERROR: Invalid camera ID " << c.cameraID << std::endl;
    }
    if (!(c.cameraImageSize.width > 0) || !(c.cameraImageSize.height > 0)) {
        c.validData = false;
        std::cerr << "ERROR: Camera image size " << c.cameraImageSize << std::endl;
    }
    if (!(c.cameraFPS > 0)) {
        c.validData = false;
        std::cerr << "ERROR: Camera FPS " << c.cameraFPS << std::endl;
    }
    if (!(c.calibImageSize.width > 0) || !(c.calibImageSize.height > 0)) {
        c.validData = false;
        std::cerr << "ERROR: Invalid calibration image size " << c.calibImageSize << std::endl;
    }
    if (c.calibPattern != "CHESSBOARD") {
        c.validData = false;
        std::cerr << "ERROR: Invalid calibration pattern " << c.calibPattern << std::endl;
    }
    if (!(c.calibPatternDim.width > 2) || !(c.calibPatternDim.height > 2)) {
        c.validData = false;
        std::cerr << "ERROR: Invalid calibration pattern dimension " << c.calibPatternDim << std::endl;
    }
    if (!(c.calibPatternSize > 0)) {
        c.validData = false;
        std::cerr << "ERROR: Invalid calibration patter size " << c.calibPatternSize << std::endl;
    }
    if (c.calibIntrDone) {
        //! @todo intrinsic validation
    }
    if (c.cameraMatrix.empty()) {
        c.calibIntrDone = false;
    }
    if (c.diffCoeffs.empty()) {
        c.calibIntrDone = false;
    }
    if (c.calibExtrDone) {
        //! @todo extrinsisc validation
    }
    if (c.homography.empty()) {
        c.calibExtrDone = false;
    }
    if (c.transformation.empty()) {
        //! @todo transformation validation
    }
    if (!(c.pixelPerMm > 0)) {
        c.calibExtrDone = false;
    }
    return c.validData;
}

void *configCalibIntr(void *arg)
{
    std::cout << "THREAD: cameraMatrix calibarion started." << std::endl;

    cv::Mat inputImage, undistorted;
    cv::Mat cameraMatrix, diffCoeffs;

    while ((getModuleState() & MODULE_CONFIG_CALIB_INTR) == MODULE_CONFIG_CALIB_INTR) {
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            calibIntr(inputImage, cameraMatrix, diffCoeffs, getPatternDim(), 30.0, 50);
            if (!cameraMatrix.empty() && !diffCoeffs.empty()) {
                setIntr(cameraMatrix, diffCoeffs);
            }
            else {
                std::cout << "Camera not calibrated!" << std::endl;
            }
        }
        if (!cameraMatrix.empty() && !diffCoeffs.empty()) {
            undistort(inputImage, undistorted, cameraMatrix, diffCoeffs);
            cv::line(undistorted, cv::Point(undistorted.cols/2, 0), cv::Point(undistorted.cols/2, undistorted.rows), cv::Scalar(0, 0, 255), 1);
            cv::line(undistorted, cv::Point(0, undistorted.rows/2), cv::Point(undistorted.cols, undistorted.rows/2), cv::Scalar(0, 0, 255), 1);
            setOutputImageData(undistorted);
        }
    }

    setConfigState(CONFIG_MODE_NONE);

    std::cout << "THREAD: cameraMatrix calibarion ended." << std::endl;
}

void *configCalibExtr (void *arg)
{
    std::cout << "THREAD: Extrinsics calibarion started." << std::endl;

    cv::Mat inputImage, warpedImage;
    cv::Mat homography;

    while ((getModuleState() & MODULE_CONFIG_CALIB_EXTR) == MODULE_CONFIG_CALIB_EXTR) {
        getInputImageData(inputImage);
        if (!inputImage.empty()) {
            calibExtr(inputImage, homography, getPatternDim(), getPatternSize());
        }
        if (!homography.empty()) {
            //~ inversePerspectiveTransform(inputImage, warpedImage, homography);
            cv::warpPerspective(inputImage, warpedImage, homography, inputImage.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            cv::line(warpedImage, cv::Point(warpedImage.cols/2, 0), cv::Point(warpedImage.cols/2, warpedImage.rows), cv::Scalar(0, 0, 255), 1);
            cv::line(warpedImage, cv::Point(0, warpedImage.rows/2), cv::Point(warpedImage.cols, warpedImage.rows/2), cv::Scalar(0, 0, 255), 1);
            setOutputImageData(warpedImage);
        }
        else {
            cv::line(inputImage, cv::Point(inputImage.cols/2, 0), cv::Point(inputImage.cols/2, inputImage.rows), cv::Scalar(0, 0, 255), 1);
            cv::line(inputImage, cv::Point(0, inputImage.rows/2), cv::Point(inputImage.cols, inputImage.rows/2), cv::Scalar(0, 0, 255), 1);
            setOutputImageData(inputImage);
        }
    }

    if (!homography.empty()) {
        setExtr(homography);
        setPxPerMm(calcPixelPerMm(warpedImage, getPatternDim(), getPatternSize()));
    }
    else {
        std::cout << "Homography couldn't be aquired!" << std::endl;
    }

    setConfigState(CONFIG_MODE_NONE);

    std::cout << "THREAD: Extrinsics calibarion ended." << std::endl;
}

void *configImagePos (void *arg)
{
    std::cout << "THREAD: Image position configuration started." << std::endl;

    cv::Mat inputImage, adjustedImage;
    cv::Mat homography;

    getInputImageData(inputImage);

    while ((getModuleState() & MODULE_CONFIG_IMAGE_POSITION) == MODULE_CONFIG_IMAGE_POSITION) {
        getInputImageData(inputImage);
        getExtr(homography);

        if (!inputImage.empty()) {
            char key = getUiInputKey();
            adjustImagePosition(inputImage, adjustedImage, key, homography);
            setExtr(homography);
            setOutputImageData(adjustedImage);
        }
    }

    setConfigState(CONFIG_MODE_NONE);

    std::cout << "THREAD: Image position configuration ended." << std::endl;
}

void *showChessBoard (void *arg)
{
    std::cout << "THREAD: Show chessboard started." << std::endl;

    while ((getModuleState() & MODULE_SHOW_CHESSBOARD) == MODULE_SHOW_CHESSBOARD) {
        cv::Mat image;
        getInputImageData(image);
        if (!image.empty()) {
            showChessBoardCorners(image, getPatternDim());
            setOutputImageData(image);
        }
    }

    std::cout << "THREAD: Show chessboard ended." << std::endl;
}
