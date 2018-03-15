/**
 * @file camera_calibration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.3.2017
 */

#include "camera_calibration.hpp"

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

void calibIntr (cv::Mat image, cv::Mat& cameraMatrix, cv::Mat& distCoeffs, cv::Size calibPatternSize, double calibPatternMm, int sampleCnt)
{
    double aspRatio = 1.0;

    std::vector<std::vector<cv::Point2f> >imagePoints;

    while (imagePoints.size() < sampleCnt) {
        cv::Mat grayImage;
        cvtColor(image, grayImage, CV_BGR2GRAY);

        std::vector<cv::Point2f> corners;

        bool found = findChessboardCorners(image, calibPatternSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if (found) {
            cornerSubPix(grayImage, corners, cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            // Save corners
            imagePoints.push_back(corners);
        }
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

void showChessBoardCorners (cv::Mat& image, cv::Size calibPatternSize)
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
