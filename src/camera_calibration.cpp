/**
 * @file camera_calibration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.3.2017
 */

#include "camera_calibration.hpp"

using namespace std;
using namespace cv;

void calcBoardCornerPosition (Size boardSize, float squareSize, vector<Point3f>& corners)
{
    corners.clear();
    // Calculate corner position of chessboard squares
    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            corners.push_back(Point3f(j*squareSize, i*squareSize, 0));
        }
    }
}

void calibrateIntrinsics (Mat& image, Mat& homography, Size boardSize, double squareSize, int sampleCnt)
{
    //~ int sampleCnt = 50;
    //~ double squareSize = 30.0; //!< Chessboard square size is 30 mm
    double aspRatio = 1.0;
    
    vector<vector<Point2f> >imagePoints;
    
    while (imagePoints.size() < sampleCnt) {
        Mat grayImage;
        cvtColor(image, grayImage, CV_BGR2GRAY);
        
        vector<Point2f> corners;
        
        bool found = findChessboardCorners(image, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
        
        if (found) {
            cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            // Save corners
            imagePoints.push_back(corners);
        }
    }
    
    Mat intrinsics = Mat::eye(3, 3, CV_64F); //!< Intrinsic camera matrix
    Mat distCoeffs = Mat::zeros(8, 1, CV_64F); //!< Distorion coefficients
    vector<Mat> rvecs; //!< Rotation vectors
    vector<Mat> tvecs; //!< Translation vectors
    
    // Set aspect ratio
    intrinsics.at<double>(1, 1) = aspRatio;
    // Calculate cornerpoints
    vector<vector<Point3f> > objectPoints(1);
    calcBoardCornerPosition(boardSize, squareSize, objectPoints[0]);
    objectPoints.resize(imagePoints.size(), objectPoints[0]);
    
    // Calibrate camera and get reprojection error rms
    double rms = calibrateCamera(objectPoints, imagePoints, Size(image.cols, image.rows), intrinsics, distCoeffs, rvecs, tvecs, CV_CALIB_USE_INTRINSIC_GUESS);
    //vector<double> reprojErrs;
    //double totalAvgError = computeReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, intrinsics, distCoeffs, reprojErrs, 1);
    
    // TODO: Save calibration to XML file
}

void calibrateExtrinsics (Mat& image, Mat& homography, Size boardSize, double squareSize)
{
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    
    vector<Point2f> corners;
    bool found = findChessboardCorners(image, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
    
    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        
        Point2f objectPoints[4], imagePoints[4];
        objectPoints[0] = Point2f(0, 0);
        objectPoints[1] = Point2f(boardSize.width-1, 0);
        objectPoints[2] = Point2f(0, boardSize.height-1);
        objectPoints[3] = Point2f(boardSize.width-1, boardSize.height-1);
        imagePoints[0] = corners[0];
        imagePoints[1] = corners[boardSize.width-1];
        imagePoints[2] = corners[(boardSize.height-1)*boardSize.width];
        imagePoints[3] = corners[(boardSize.height-1)*boardSize.width + boardSize.width-1];
        
        homography = getPerspectiveTransform(objectPoints, imagePoints);
    }
    else {
        cerr << "ERROR: Could not aquire checkerboard!" << endl;
    }
    
    // TODO: Save calibration to XML file
}

void showChessBoardCorners (Mat& image, Size boardSize)
{
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    
    vector<Point2f> corners;
    bool found = findChessboardCorners(grayImage, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
    
    if (found) {
        cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
        drawChessboardCorners(image, boardSize, corners, found);
    }
}

void inversePerspectiveTransform(Mat image, Mat& warpedImage, Mat homography)
{
   double xOffset = image.size().width/2 * (-1) + 30;
   double yOffset = image.size().height/2 * (-1) + 30;
   double zOffset = 15;

   Mat transform = Mat::eye(3, 3, CV_64F);
   transform.at<double>(0, 2) = xOffset;
   transform.at<double>(1, 2) = yOffset;
   transform.at<double>(2, 2) = zOffset;
   transform = homography * transform;

   Size warpedImageSize(image.size().width, image.size().height);
   warpPerspective(image, warpedImage, transform, warpedImageSize, WARP_INVERSE_MAP + INTER_LINEAR);
}
