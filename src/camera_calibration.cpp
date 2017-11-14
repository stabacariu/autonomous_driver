/**
 * @file camera_calibration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.3.2017
 */

#include "camera_calibration.hpp"

using namespace std;
using namespace cv;

void calcBoardCornerPosition (Size calibrationPatternDimension, float calibrationPatternSize, vector<Point3f>& corners)
{
    corners.clear();
    // Calculate corner position of chessboard squares
    for (int i = 0; i < calibrationPatternDimension.height; i++) {
        for (int j = 0; j < calibrationPatternDimension.width; j++) {
            corners.push_back(Point3f(j*calibrationPatternSize, i*calibrationPatternSize, 0));
        }
    }
}

void calibIntr (Mat image, Mat& cameraMatrix, Mat& distCoeffs, Size calibrationPatternDimension, double calibrationPatternSize, int sampleCnt)
{
    double aspRatio = 1.0;
    
    vector<vector<Point2f> >imagePoints;
    
    while (imagePoints.size() < sampleCnt) {
        Mat grayImage;
        cvtColor(image, grayImage, CV_BGR2GRAY);
        
        vector<Point2f> corners;
        
        bool found = findChessboardCorners(image, calibrationPatternDimension, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
        
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
    calcBoardCornerPosition(calibrationPatternDimension, calibrationPatternSize, objectPoints[0]);
    objectPoints.resize(imagePoints.size(), objectPoints[0]);
    
    // Calibrate camera and get reprojection error rms
    double rms = calibrateCamera(objectPoints, imagePoints, Size(image.cols, image.rows), cameraMatrix, distCoeffs, rvecs, tvecs, CV_CALIB_USE_INTRINSIC_GUESS);
    
    
    //vector<double> reprojErrs;
    //double totalAvgError = computeReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs, 1);
    
    //! @todo Save intrinsic calibration to XML file
}

void calibExtr (Mat image, Mat& homography, Size calibrationPatternDimension, double calibrationPatternSize)
{
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    
    vector<Point2f> corners;
    bool found = findChessboardCorners(image, calibrationPatternDimension, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
    
    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        
        Point2f objectPoints[4];
        objectPoints[0] = Point2f(0, 0);
        objectPoints[1] = Point2f((calibrationPatternDimension.width-1)*calibrationPatternSize, 0);
        objectPoints[2] = Point2f(0, (calibrationPatternDimension.height-1)*calibrationPatternSize);
        objectPoints[3] = Point2f((calibrationPatternDimension.width-1)*calibrationPatternSize, (calibrationPatternDimension.height-1)*calibrationPatternSize);
        Point2f imagePoints[4];
        imagePoints[0] = corners[0];
        imagePoints[1] = corners[calibrationPatternDimension.width-1];
        imagePoints[2] = corners[(calibrationPatternDimension.height-1)*calibrationPatternDimension.width];
        imagePoints[3] = corners[(calibrationPatternDimension.height-1)*calibrationPatternDimension.width + calibrationPatternDimension.width-1];
        
        
        homography = getPerspectiveTransform(objectPoints, imagePoints);
        
        // Shift to image center
        //~ Mat t = Mat::eye(3, 3, CV_64F);
        //~ t.at<double>(0, 2) = image.cols/2 * (-1) + 3*15; // Shift width
        //~ t.at<double>(1, 2) = image.rows * (-1) + 2*3*15; // Shift height
        //~ t.at<double>(2, 2) = 15;
        //~ homography *= t;
        Mat t = Mat::eye(3, 3, CV_64F);
        t.at<double>(0, 2) = (image.cols-1)/2 * (-1) + 0.5*(calibrationPatternSize*(calibrationPatternDimension.width-1)/2); // Shift width
        t.at<double>(1, 2) = (image.rows-1) * (-1) + 0.5*(calibrationPatternSize*(calibrationPatternDimension.height)); // Shift height
        t.at<double>(2, 2) = 0.5 + 0.5;
        homography *= t;
    }
    
    //! @todo Save calibration to XML file
}

float euclidDist (Point2f p1, Point2f p2)
{
    Point2f diff = p1 - p2;
    return sqrt(diff.x*diff.x + diff.y*diff.y);
}

float calcPixelPerMm (Mat image, Size calibrationPatternDimension, float calibrationPatternSize)
{
    float pixelPerMm;
    float avgPxPerMm = 0.0;
    int distCnt = 0;
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    
    vector<Point2f> corners;
    bool found = findChessboardCorners(image, calibrationPatternDimension, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
    
    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, calibrationPatternSize, 0.1));
        
        for (int i = 0; i < (corners.size()-1); i++) {
            if ((i%calibrationPatternDimension.width) < (calibrationPatternDimension.width-1)) {
                pixelPerMm = euclidDist(corners[i+1], corners[i]);
                avgPxPerMm += pixelPerMm;
                distCnt++;
            }
            else {
                i++;
            }
        }
        avgPxPerMm /= distCnt;
        cout << "Avg distance " << avgPxPerMm << " mm per px " << avgPxPerMm/calibrationPatternSize << endl;
    }
    return avgPxPerMm/calibrationPatternSize;
}

void showChessBoardCorners (Mat& image, Size calibrationPatternDimension)
{
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    
    vector<Point2f> corners;
    bool found = findChessboardCorners(grayImage, calibrationPatternDimension, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
    
    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        drawChessboardCorners(image, calibrationPatternDimension, corners, found);
    }
}

//! @todo Delete this function
void inversePerspectiveTransform (Mat image, Mat& warpedImage, Mat homography)
{
   Size warpedImageSize(image.cols, image.rows);
   warpPerspective(image, warpedImage, homography, warpedImageSize, CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
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
