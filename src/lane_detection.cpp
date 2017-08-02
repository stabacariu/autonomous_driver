/**
 * @file lane_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "lane_detection.hpp"

using namespace std;
using namespace cv;

// TODO: Move to camera extrinsic calibration
//~ int laneCalibration(Mat& image, Mat& homography, Size boardSize)
//~ {
   //~ Mat grayImage;
   //~ cvtColor(image, grayImage, CV_BGR2GRAY);
//~ 
   //~ vector<Point2f> corners;
   //~ bool found = findChessboardCorners(image, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
   //~ if (!found) {
      //~ cerr << "ERROR: Could not aquire checkerboard!" << endl;
      //~ return -1;
   //~ }
   //~ cornerSubPix(grayImage, corners, Size(11,11), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
//~ 
   //~ Point2f objectPoints[4], imagePoints[4];
   //~ objectPoints[0] = Point2f(0, 0);
   //~ objectPoints[1] = Point2f(boardSize.width-1, 0);
   //~ objectPoints[2] = Point2f(0, boardSize.height-1);
   //~ objectPoints[3] = Point2f(boardSize.width-1, boardSize.height-1);
   //~ imagePoints[0] = corners[0];
   //~ imagePoints[1] = corners[boardSize.width-1];
   //~ imagePoints[2] = corners[(boardSize.height-1)*boardSize.width];
   //~ imagePoints[3] = corners[(boardSize.height-1)*boardSize.width + boardSize.width-1];
//~ 
   //~ homography = getPerspectiveTransform(objectPoints, imagePoints);
   //~ 
   //~ //drawChessboardCorners(image, boardSize, corners, found);
//~ 
   //~ return 0;
//~ }
// TODO: Move to camera extrinsic calibration
//~ void inversePerspectiveTransform(Mat image, Mat& warpedImage, Mat homography)
//~ {
   //~ double xOffset = image.size().width/2 * (-1) + 30;
   //~ double yOffset = image.size().height/2 * (-1) + 30;
   //~ double zOffset = 15;
//~ 
   //~ Mat transform = Mat::eye(3, 3, CV_64F);
   //~ transform.at<double>(0, 2) = xOffset;
   //~ transform.at<double>(1, 2) = yOffset;
   //~ transform.at<double>(2, 2) = zOffset;
   //~ transform = homography * transform;
//~ 
   //~ Size warpedImageSize(image.size().width, image.size().height);
   //~ warpPerspective(image, warpedImage, transform, warpedImageSize, WARP_INVERSE_MAP + INTER_LINEAR);
//~ }

void sortLineDirections (vector<Vec4i>& lines)
{
   for (size_t i = 0; i <  lines.size(); i++) {
      Point pt1 = Point(lines[i][0], lines[i][1]);
      Point pt2 = Point(lines[i][2], lines[i][3]);
      
      if (pt1.y > pt2.y) {
         Point ptTmp = pt1;
         pt1 = pt2;
         pt2 = ptTmp;
      }
      lines[i][0] = pt1.x;
      lines[i][1] = pt1.y;
      lines[i][2] = pt2.x;
      lines[i][3] = pt2.y;
   }
}

void detectLines (Mat grayImage, vector<Vec4i>& lines)
{
   lines.clear();

   Mat imageEdges;
   Canny(grayImage, imageEdges, 10, 30);

   /**
    * Find lines with probabilistic Hough line function.
    * Note: threshold 35 seems to be optimal
    * Note: minLineLength 40 seems to be optimal
    * Note: maxLineGap 10 seems to be optimal
    */
   HoughLinesP(imageEdges, lines, 1, CV_PI/180, 35, 40, 10);
   
   sortLineDirections(lines);
}

void *laneDetection (void *arg)
{
    cout << "Thread lane detection started." << endl;
    
    while (getSystemState() != SYS_MODE_CLOSING) {
        Mat image, homography;
        getInputImageData(image);
        
        if (!image.empty()) {
            // TODO: Homography check
            Mat warpedImage;
            if (!homography.empty()) {
                inversePerspectiveTransform(image, warpedImage, homography);
            }
            else {
                image.copyTo(warpedImage);
            }
            
            Mat grayImage;
            whiteColorFilter(warpedImage, grayImage);
            
            Mat yellowImage;
            yellowColorFilter(warpedImage, yellowImage);
            
            // Merge images
            bitwise_or(grayImage, yellowImage, grayImage);
            
            // Blur image
            GaussianBlur(grayImage, grayImage, Size(5, 5), 0);
            
            vector<Vec4i> lines;
            detectLines(grayImage, lines);
            
            setOutputImageData(grayImage);
        }
    }
    
    cout << "Thread lane detection ended." << endl;
    
    return NULL;
}
