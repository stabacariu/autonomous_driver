/**
 * @file camera_calibration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.3.2017
 */

#include "camera_calibration.hpp"

using namespace std;
using namespace cv;

void calcBoardCornerPosition (Size calibPatternDim, float calibPatternSize, vector<Point3f>& corners)
{
    corners.clear();
    // Calculate corner position of chessboard squares
    for (int i = 0; i < calibPatternDim.height; i++) {
        for (int j = 0; j < calibPatternDim.width; j++) {
            corners.push_back(Point3f(j*calibPatternSize, i*calibPatternSize, 0));
        }
    }
}

void calibIntr (Mat image, Mat& cameraMatrix, Mat& distCoeffs, Size calibPatternDim, double calibPatternSize, int sampleCnt)
{
    double aspRatio = 1.0;

    vector<vector<Point2f> >imagePoints;

    while (imagePoints.size() < sampleCnt) {
        Mat grayImage;
        cvtColor(image, grayImage, CV_BGR2GRAY);

        vector<Point2f> corners;

        bool found = findChessboardCorners(image, calibPatternDim, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if (found) {
            cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            // Save corners
            imagePoints.push_back(corners);
        }
    }

    cameraMatrix = Mat::eye(3, 3, CV_64F); //!< Intrinsic camera matrix
    distCoeffs = Mat::zeros(8, 1, CV_64F); //!< Distorion coefficients
    vector<Mat> rvecs; //!< Rotation vectors
    vector<Mat> tvecs; //!< Translation vectors

    // Set aspect ratio
    cameraMatrix.at<double>(1, 1) = aspRatio;
    // Calculate cornerpoints
    vector<vector<Point3f> > objectPoints(1);
    calcBoardCornerPosition(calibPatternDim, calibPatternSize, objectPoints[0]);
    objectPoints.resize(imagePoints.size(), objectPoints[0]);

    // Calibrate camera and get reprojection error rms
    double rms = calibrateCamera(objectPoints, imagePoints, Size(image.cols, image.rows), cameraMatrix, distCoeffs, rvecs, tvecs, CV_CALIB_USE_INTRINSIC_GUESS);


    //vector<double> reprojErrs;
    //double totalAvgError = computeReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs, 1);

    //! @todo Save intrinsic calibration to XML file
}

void calibExtr (Mat image, Mat& homography, Size calibPatternDim, double calibPatternSize)
{
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    vector<Point2f> corners;
    bool found = findChessboardCorners(image, calibPatternDim, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

        Point2f objectPoints[4];
        objectPoints[0] = Point2f(0, 0);
        objectPoints[1] = Point2f((calibPatternDim.width-1)*calibPatternSize, 0);
        objectPoints[2] = Point2f(0, (calibPatternDim.height-1)*calibPatternSize);
        objectPoints[3] = Point2f((calibPatternDim.width-1)*calibPatternSize, (calibPatternDim.height-1)*calibPatternSize);
        Point2f imagePoints[4];
        imagePoints[0] = corners[0];
        imagePoints[1] = corners[calibPatternDim.width-1];
        imagePoints[2] = corners[(calibPatternDim.height-1)*calibPatternDim.width];
        imagePoints[3] = corners[(calibPatternDim.height-1)*calibPatternDim.width + calibPatternDim.width-1];


        homography = getPerspectiveTransform(objectPoints, imagePoints);

        // Shift to image center
        Mat t = Mat::eye(3, 3, CV_64F);
        t.at<double>(0, 2) = (image.cols-1)/2 * (-1) + 0.5*(calibPatternSize*(calibPatternDim.width-1)/2); // Shift width
        t.at<double>(1, 2) = (image.rows-1) * (-1) + 0.5*(calibPatternSize*(calibPatternDim.height)); // Shift height
        t.at<double>(2, 2) = 0.5;
        homography *= t;
    }
}

float euclidDist (Point2f p1, Point2f p2)
{
    Point2f diff = p1 - p2;
    return sqrt(diff.x*diff.x + diff.y*diff.y);
}

float calcPixelPerMm (Mat image, Size calibPatternDim, float calibPatternSize)
{
    float pxDist;
    float avgPxDist = 0.0;
    int distCnt = 0;
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    vector<Point2f> corners;
    bool found = findChessboardCorners(image, calibPatternDim, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, calibPatternSize, 0.1));

        for (int i = 0; i < (corners.size()-1); i++) {
            if ((i%calibPatternDim.width) < (calibPatternDim.width-1)) {
                pxDist = euclidDist(corners[i+1], corners[i]);
                avgPxDist += pxDist;
                distCnt++;
            }
            else {
                i++;
            }
        }
        avgPxDist /= distCnt;
        cout << "Avg distance in px " << avgPxDist << endl;
        cout << "Px per mm" << avgPxDist/calibPatternSize << endl;
    }
    return avgPxDist/calibPatternSize;
}

void showChessBoardCorners (Mat& image, Size calibPatternDim)
{
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);

    vector<Point2f> corners;
    bool found = findChessboardCorners(grayImage, calibPatternDim, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        drawChessboardCorners(image, calibPatternDim, corners, found);
    }
}

void adjustImagePosition (Mat image, Mat& adjustedImage, char key, Mat& homography)
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
            homography = Mat::eye(3, 3, CV_64F);
        }
        homography.at<double>(0, 2) += xOffset;
        homography.at<double>(1, 2) += yOffset;
        homography.at<double>(2, 2) += zOffset;
    }
}
