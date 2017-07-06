/**
 * @file camera_calibration.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 5.3.2017
 */

#include "camera_calibration.hpp"

using namespace std;
using namespace cv;

void calibrateIntrinsic (Mat& image, Mat& homography, Size chessBoardSize)
{
    int sampleCnt = 50;
    int cornersHorizontal = 7;
    int cornersVertical = 5;
    Mat grayImage;
    cvtColor(image, grayImage, CV_BGR2GRAY);
    
    vector<Point2f> corners;
    bool found = findChessboardCorners(image, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
    
    if (found) {
        cornerSubPix(grayImage, corners, Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
    }
    
    
}

void calibrateExtrinsic (Mat& image, Mat& homography, Size chessBoardSize)
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
        
        drawChessboardCorners(image, boardSize, corners, found);
    }
    else {
        cerr << "ERROR: Could not aquire checkerboard!" << endl;
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
