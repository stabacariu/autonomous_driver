/**
 * @file lane_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "lane_detection.hpp"

using namespace std;
using namespace cv;

float getEuclidDistance(Point pt1, Point pt2)
{
   Point diff = pt1 - pt2;
   return sqrt(pow(diff.x, 2) + pow(diff.y, 2));
   // or
   //~ return norm(pt1-pt2);
}

/**
 * @brief This function calculates the distance rho for the polar line form.
 *  (rho, theta)
 * @param pt point on the line
 * @param rho slope of the line
 * @return r the distance of the line to the origin for the polar form 
 */
float getRho (Point pt1, Point pt2)
{
   return (pt1.y * pt2.x - pt2.y * pt1.x)/getEuclidDistance(pt1, pt2);
}

/**
 * @brief This function calculates the angle theta for the polar line form.
 *  (rho, theta)
 * @param pt1 starting point of the line
 * @param pt2 ending point of the line
 * @return theta the angle for the polar form
 */
float getTheta (Point pt1, Point pt2)
{
   return atan2((pt2.y - pt1.y), (pt2.x - pt1.x));
}

void cvtLinesToLinesPolar (vector<Vec4i> lines, vector<Vec2f>& linesPolar)
{
    linesPolar.clear();
    for (size_t i = 0; i < lines.size(); i++) {
        float theta = getTheta(Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]));
        float rho = getRho(Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]));
        
        linesPolar.push_back(Vec2f(rho, theta));
    }
}

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

/**
 * @brief This function detects lines in an grayscale input image
 */

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

void drawLine (Mat& image, Vec4i l, Scalar color)
{
    line(image, Point(l[0], l[1]), Point(l[2], l[3]), color, 2);
}

void drawLines (Mat& image, vector<Vec4i> lines, Scalar color)
{
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(image, Point(l[0], l[1]), Point(l[2], l[3]), color, 2);
    }
}

void drawArrowedLine (Mat& image, Vec4i l, Scalar color)
{
    arrowedLine(image, Point(l[0], l[1]), Point(l[2], l[3]), color, 2);
}

void drawArrowedLines (Mat& image, vector<Vec4i> lines, Scalar color)
{
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        arrowedLine(image, Point(l[0], l[1]), Point(l[2], l[3]), color, 2);
    }
}

void drawCenterLine (Mat& image, Scalar color)
{
    Point pt1((image.cols/2)-1, 0);
    Point pt2(pt1.x, image.rows-1);
    line(image, pt1, pt2, color, 1);
}

/**
 * @brief This function filters left and right lines. It also filters 
 *          the most left line in right image half and the most right line
 *          in the left image half.
 */
 
void filterLines (vector<Vec4i> lines, Size imageSize, vector<Vec4i>& leftLines, vector<Vec4i>& rightLines, vector<Vec4i>& lane)
{
    lane.clear();
    Vec4i leftLine = Vec4i(imageSize.width-1, 0, imageSize.width-1, imageSize.height-1);
    Vec4i rightLine = Vec4i(0, 0, 0, imageSize.height-1);
    
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i][2] <= ((imageSize.width/2)-1)) {
            leftLines.push_back(lines[i]);
            if (lines[i][2] < leftLine[2]) {
                leftLine = lines[i];
            }
        }
        else {
            rightLines.push_back(lines[i]);
            if (lines[i][2] > rightLine[2]) {
                rightLine = lines[i];
            }
        }
    }
    
    lane.push_back(leftLine);
    lane.push_back(rightLine);
}

/**
 * @brief This function checks if 2 lines are parallel.
 */

int checkParallelLine (vector<Vec4i> lines)
{
    float thetaLeft = getTheta(Point(lines[0][0], lines[0][1]), Point(lines[0][2],lines[0][3]));
    float thetaRight = getTheta(Point(lines[1][0], lines[1][1]), Point(lines[1][2], lines[1][3]));
    //~ cout << "Left line theta: " << thetaLeft << ", Right line theta " << thetaRight << endl;
    if (thetaLeft == thetaRight) {
        cout << "Lines are parallel!" << endl;
        return 1;
    }
    else {
        return -1;
    }
}

Vec4i getLaneMid (vector<Vec4i> lane)
{
   Point ptl1 = Point(lane[0][0], lane[0][1]);
   Point ptl2 = Point(lane[0][2], lane[0][3]);
   Point ptr1 = Point(lane[1][0], lane[1][1]);
   Point ptr2 = Point(lane[1][2], lane[1][3]);
   
   Point ptmid1 = Point(ptl1.x + (ptr1.x - ptl1.x)/2, ptl1.y + (ptr1.y - ptl1.y)/2);
   Point ptmid2 = Point(ptl2.x + (ptr2.x - ptl2.x)/2, ptl2.y + (ptr2.y - ptl2.y)/2);
   Vec4i laneMid = Vec4i(ptmid1.x, ptmid1.y, ptmid2.x, ptmid2.y);
   
   return laneMid;
}

/**
 * @brief Thread for lane detection
 */

void *laneDetection (void *arg)
{
    cout << "THREAD: Lane detection started." << endl;
    
    // Initialize line prediction
    KalmanFilter kfL(4, 4, 0);
    KalmanFilter kfR(4, 4, 0);
    initLinePrediction(kfL, 4);
    initLinePrediction(kfR, 4);
    vector<Vec4i> measuredLines;
    vector<Vec4i> predictedLines;
    vector<Vec4i> measuredLeftLines;
    vector<Vec4i> measuredRightLines;
    vector<Vec4i> predictedLeftLines;
    vector<Vec4i> predictedRightLines;
    
    while ((getModuleState() & MODULE_DETECT_LANES) == MODULE_DETECT_LANES) {
        Mat image, homography;
        getInputImageData(image);
        getHomography(homography);
        
        if (!image.empty()) {
            Mat warpedImage;
            if (!homography.empty()) {
                inversePerspectiveTransform(image, warpedImage, homography);
            }
            else {
                image.copyTo(warpedImage);
            }
            
            autoAdjustImage(warpedImage);
            
            Mat grayImage;
            whiteColorFilter(warpedImage, grayImage);
            
            Mat yellowImage;
            yellowColorFilter(warpedImage, yellowImage);
            
            // Merge images
            //~ bitwise_or(grayImage, yellowImage, grayImage);
            
            // Blur image
            GaussianBlur(grayImage, grayImage, Size(5, 5), 0);
            
            // Detect lines
            vector<Vec4i> lines;
            detectLines(grayImage, lines);
            // Show lines
            //~ drawArrowedLines(warpedImage, lines, Scalar(0,0,255));
            vector<Vec4i> leftLines;
            vector<Vec4i> rightLines;
            vector<Vec4i> lane;
            filterLines(lines, grayImage.size(), leftLines, rightLines, lane);
            
            // Predict lane
            vector<Vec4i> predictedLane;
            if (leftLines.size() > 0) {
                
                predictLine(leftLines,  kfL, 4, measuredLeftLines, predictedLeftLines);
                drawArrowedLines(warpedImage, predictedLeftLines, Scalar(255, 0, 0));
            }
            if (predictedLeftLines.size() > 0) {
                predictedLane.push_back(predictedLeftLines[0]);
                Rect leftLineRoi = Rect(Point(predictedLeftLines[0][0], predictedLeftLines[0][1]), Point(predictedLeftLines[0][2], predictedLeftLines[0][3]));
                setRoiLeft(leftLineRoi);
            }
            
            if (rightLines.size() > 0) {
                predictLine(rightLines, kfR, 4, measuredRightLines, predictedRightLines);
                drawArrowedLines(warpedImage, predictedRightLines, Scalar(0, 0, 255));
            }
            if (predictedRightLines.size() > 0) {
                predictedLane.push_back(predictedRightLines[0]);
                Rect rightLineRoi = Rect(Point(predictedRightLines[0][0], predictedRightLines[0][1]), Point(predictedRightLines[0][2], predictedRightLines[0][3]));
                setRoiRight(rightLineRoi);
            }
            
            // Check if lines are parallel
            if (predictedLane.size() == 2) {
                checkParallelLine(predictedLane);
                drawArrowedLine(warpedImage, getLaneMid(predictedLane), Scalar(200,200,0));
                // Save detected lane
                setActualLane(predictedLane);
            }
            predictedLane.clear();
            
            drawCenterLine(warpedImage, Scalar(0,255,0));
            
            rectangle(warpedImage, getRoiLeft(), Scalar(255, 0, 0), 1);
            rectangle(warpedImage, getRoiRight(), Scalar(0, 0, 255), 1);
            
            setOutputImageData(warpedImage);
        }
    }
    
    cout << "THREAD: Lane detection ended." << endl;
    
    return NULL;
}

/**
 * @brief This function initializes the line prediction with a Kalman filter.
 */

void initLinePrediction (KalmanFilter& kf, int valueCnt)
{
    kf.statePre = Mat::zeros(valueCnt, 1, CV_32F);
    setIdentity(kf.transitionMatrix);
    setIdentity(kf.measurementMatrix);
    setIdentity(kf.processNoiseCov);
    setIdentity(kf.measurementNoiseCov, Scalar::all(200));
    setIdentity(kf.errorCovPost, Scalar::all(100));
}

/**
 * @brief This function predicts the line points.
 */

void predictLine (vector<Vec4i> lines, KalmanFilter& kf, int valueCnt, vector<Vec4i>& measuredLines, vector<Vec4i>& predictedLines)
{
    measuredLines.clear();
    predictedLines.clear();
    
    for (size_t i = 0; i < lines.size(); i++) {
        Mat prediction = kf.predict();
        Vec4i predictedPts(prediction.at<float>(0), prediction.at<float>(1), prediction.at<float>(2), prediction.at<float>(3));
        
        Mat measurement = Mat::zeros(valueCnt, 1, CV_32F);
        for (size_t j = 0; j < valueCnt; j++) {
            measurement.at<float>(j) = lines[i][j];
        }
        
        Mat estimated = kf.correct(measurement);
        
        Vec4i statePts(estimated.at<float>(0), estimated.at<float>(1), estimated.at<float>(2), estimated.at<float>(3));
        Vec4i measuredPts(measurement.at<float>(0), measurement.at<float>(1), measurement.at<float>(2), measurement.at<float>(3));
        
        measuredLines.clear();
        predictedLines.clear();
        
        measuredLines.push_back(measuredPts);
        predictedLines.push_back(statePts);
    }
}
