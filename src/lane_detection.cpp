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

float getRho (Point pt1, Point pt2)
{
   return (pt1.y * pt2.x - pt2.y * pt1.x)/getEuclidDistance(pt1, pt2);
}

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
   Canny(grayImage, imageEdges, 10, 50);
   //~ Sobel(grayImage, imageEdges, CV_16S, 1, 0, 1);
   //~ convertScaleAbs(imageEdges, imageEdges);

   /**
    * Find lines with probabilistic Hough line function.
    * @note threshold 35 seems to be optimal
    * @note minLineLength 40 seems to be optimal
    * @note maxLineGap 10 seems to be optimal
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
    Vec4i leftLine = Vec4i(imageSize.width-1, imageSize.height-1, imageSize.width-1, 0);
    Vec4i rightLine = Vec4i(0, imageSize.height-1, 0, 0);

    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i][2] <= ((imageSize.width-1)/2)) {
            leftLines.push_back(lines[i]);
            if (lines[i][2] <= leftLine[2]) {
                if (lines[i][3] >= leftLine[3]) {
                    leftLine = lines[i];
                }
            }
        }
        else {
            rightLines.push_back(lines[i]);
            if (lines[i][2] >= rightLine[2]) {
                if (lines[i][3] >= rightLine[3]) {
                    rightLine = lines[i];
                }
            }
        }
    }

    lane.push_back(leftLine);
    lane.push_back(rightLine);
}

float distanceBetweenLines (Vec4i line1, Vec4i line2)
{
    float m1, m2, b1, b2;
    
    // Check if lines parallel to x or y axis
    if ((line1[0] == line1[2]) || (line2[0] == line2[2])) {
        return 0;
    }
    else {
        m1 = (line1[3] - line1[1])/(line1[2]-line1[0]);
        m2 = (line2[3] - line2[1])/(line2[2]-line2[0]);
        b1 = (line1[2]*line1[1] - line1[0]*line1[3])/(line1[2]-line1[0]);
        b2 = (line2[2]*line2[1] - line2[0]*line2[3])/(line2[2]-line2[0]);
        
        if (m1 == m2) {
             return abs(b2-b1)/sqrt(pow(m1, 2)+1);
        }
        else {
            return 0;
        }
    }
    
}

/**
 * @brief This function checks if 2 lines are parallel.
 */

bool checkParallelLine (vector<Vec4i> lines)
{
    float thetaLeft = getTheta(Point(lines[0][0], lines[0][1]), Point(lines[0][2],lines[0][3]));
    float thetaRight = getTheta(Point(lines[1][0], lines[1][1]), Point(lines[1][2], lines[1][3]));
    //~ cout << "Left line theta: " << thetaLeft << ", Right line theta " << thetaRight << endl;
    if (thetaLeft == thetaRight) {
        cout << "Lines are parallel!" << endl;
        cout << "Distance between lines is " << distanceBetweenLines(lines[0], lines[1])*getPxPerMm() << endl;
        return true;
    }
    else {
        return false;
    }
}

bool checkForStopLine (vector<Vec4i> lines, Vec4i& stopLine)
{
    for (size_t i = 0; i < lines.size(); i++) {
        float theta = getTheta(Point(lines[i][0], lines[i][1]), Point(lines[i][2],lines[i][3]));
        if ((theta < (CV_PI*0.2)) || (theta > (CV_PI*0.80))) {
            stopLine = lines[i];
            cout << "Stop line detected!" << endl;
            return true;
        }
    }
    return false;
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

void imageProcessing (Mat& image, vector<Vec4i>& lines)
{
    autoAdjustImage(image);
    
    // Blur image
    //~ GaussianBlur(image, image, Size(5, 5), 0);

    Mat grayImage;
    whiteColorFilter(image, grayImage);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(2, 2));
    erode(grayImage, grayImage, kernel);

    //~ Mat yellowImage;
    //~ yellowColorFilter(image, yellowImage);

    // Merge images
    //~ bitwise_or(image, yellowImage, grayImage);

    // Blur image
    GaussianBlur(grayImage, grayImage, Size(5, 5), 0);

    // Detect lines
    detectLines(grayImage, lines);
    cvtColor(grayImage, image, CV_GRAY2BGR);
}

void resetRois (Size imageSize)
{
    setRoiLeft(Rect(Point(0, 0), Point(imageSize.width-1, imageSize.height-1)));
    setRoiRight(Rect(Point(0, 0), Point(imageSize.width-1, imageSize.height-1)));
}

void roiOfLine (Vec4i line, Rect& roi, Size imageSize)
{
    if (line[0] <= line[2]) {
        roi = Rect(Point(line[0]-10, line[1]-10), Point(line[2]+10, line[3]+10));
    }
    else {
        roi = Rect(Point(line[0]+10, line[1]-10), Point(line[2]-10, line[3]+10));
    }
    
    // Check if ROI in bound
    if (roi.tl().x < 0) {
        roi = Rect(Point(0, roi.tl().y), roi.br());
    }
    else if (roi.tl().x > (imageSize.width-1)) {
        roi = Rect(Point((imageSize.width-1), roi.tl().y), roi.br());
    }
    
    if (roi.tl().y < 0) {
        roi = Rect(Point(roi.tl().x, 0), roi.br());
    }
    else if (roi.tl().y > (imageSize.height-1)) {
        roi = Rect(Point(roi.tl().x, (imageSize.height-1)), roi.br());
    }
    
    if (roi.br().x < 0) {
        roi = Rect(roi.tl(), Point(0, roi.br().y));
    }
    else if (roi.br().x > (imageSize.width-1)) {
        roi = Rect(roi.tl(), Point((imageSize.width-1), roi.br().y));
    }
    
    if (roi.br().y < 0) {
        roi = Rect(roi.tl(), Point(roi.br().x, 0));
    }
    else if (roi.br().y > (imageSize.height-1)) {
        roi = Rect(roi.tl(), Point(roi.br().x, (imageSize.height-1)));
    }
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
    vector<Vec4i> predLLines;
    vector<Vec4i> predRLines;
    vector<Vec4i> predictedLane;
    
    vector<Vec4i> ll;
    vector<Vec4i> rl;
    //~ Mat prevImage;
    //~ getInputImageData(prevImage);
    
    while ((getModuleState() & MODULE_DETECT_LANES) == MODULE_DETECT_LANES) {
        Mat image, homography;
        getInputImageData(image);
        getExtr(homography);
        
        //~ bool procIm = false;
        //~ if ((!image.empty()) && (!prevImage.empty())) {
            //~ cv::Mat grayImage, grayPrevImage;
            //~ cvtColor(image, grayImage, CV_BGR2GRAY);
            //~ cvtColor(prevImage, grayPrevImage, CV_BGR2GRAY);
            //~ 
            //~ if (!compareImage(grayImage, grayPrevImage)) {
                //~ procIm = true;
            //~ }
        //~ }
        //~ if (procIm && !image.empty()) {

        if (!image.empty()) {
            Mat warpedImage;
            if (!homography.empty()) {
                warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            }
            else {
                image.copyTo(warpedImage);
            }

            vector<Vec4i> lines, someLines;
            //~ Rect leftLineRoi = getRoiLeft();
            //~ Rect rightLineRoi = getRoiRight();

            imageProcessing(warpedImage, lines);
            //~ // Detect stop lines
            //~ Vec4i stopLine;
            //~ if (checkForStopLine(lines, stopLine)) {
                //~ drawLine(warpedImage, stopLine, Scalar(0,0,255));
                //~ setSteering(CV_PI/2);
                //~ setAcceleration(50);
            //~ }

            //~ if ((leftLineRoi.width == image.cols) || (rightLineRoi.width == image.cols)) {
                //~ imageProcessing(warpedImage, lines);
            //~ }
            //~ else 
            //~ if ((leftLineRoi.area() > 0) && (rightLineRoi.area() > 0)){
                //~ imageProcessing(warpedImage(leftLineRoi), someLines);
                //~ lines.insert(lines.end(), someLines.begin(), someLines.end());
                //~ imageProcessing(warpedImage(rightLineRoi), someLines);
                //~ lines.insert(lines.end(), someLines.begin(), someLines.end());
            //~ }
            //~ else {
                //~ imageProcessing(warpedImage, lines);
                //~ resetRois(warpedImage.size());
            //~ }

            // If no lines where found, take predicted lines
            if (lines.size() <= 0) {
                //~ lines.insert(lines.end(), predLLines.begin(), predLLines.end());
                //~ lines.insert(lines.end(), predRLines.begin(), predRLines.end());
                lines.insert(lines.end(), predictedLane.begin(), predictedLane.end());
            }

            if (lines.size() > 0) {
                // Show lines
                //~ drawArrowedLines(warpedImage, lines, Scalar(0,0,255));

                // Filter lines
                vector<Vec4i> leftLines;
                vector<Vec4i> rightLines;
                vector<Vec4i> lane;
                filterLines(lines, warpedImage.size(), leftLines, rightLines, lane);

                // Predict lane
                if (lane.size() == 2) {
                    //~ vector<Vec4i> ll;
                    ll.push_back(lane[0]);
                    predictLine(ll, kfL, 4, predLLines);
                    drawArrowedLines(warpedImage, predLLines, Scalar(255, 0, 0));
                    //~ vector<Vec4i> rl;
                    rl.push_back(lane[1]);
                    predictLine(rl, kfR, 4, predRLines);
                    drawArrowedLines(warpedImage, predRLines, Scalar(0, 0, 255));
                }
                //~ if (leftLines.size() > 0) {
                    //~ //~ predictLine(leftLines,  kfL, 4, predLLines);
                    //~ vector<Vec4i> ll;
                    //~ ll.push_back(lane[0]);
                    //~ predictLine(ll,  kfL, 4, predLLines);
                    //~ drawArrowedLines(warpedImage, predLLines, Scalar(255, 0, 0));
                //~ }
                //~ if (predLLines.size() > 0) {
                if (predLLines.size() == 1) {
                    predictedLane.push_back(predLLines[0]);
                    predLLines.clear();
                    // Set left ROI with offset
                    //~ roiOfLine(predLLines[0], leftLineRoi, warpedImage.size());
                    //~ setRoiLeft(leftLineRoi);
                    //~ rectangle(warpedImage, leftLineRoi, Scalar(255, 0, 0), 1);
                }
                
                //~ if (rightLines.size() > 0) {
                    //~ //~ predictLine(rightLines, kfR, 4, predRLines);
                    //~ vector<Vec4i> rl;
                    //~ rl.push_back(lane[1]);
                    //~ predictLine(rl, kfR, 4, predRLines);
                    //~ drawArrowedLines(warpedImage, predRLines, Scalar(0, 0, 255));
                //~ }
                //~ if (predRLines.size() > 0) {
                if (predRLines.size() == 1) {
                    predictedLane.push_back(predRLines[0]);
                    predRLines.clear();
                    // Set right ROI with offset
                    //~ roiOfLine(predRLines[0], rightLineRoi, warpedImage.size());
                    //~ setRoiRight(rightLineRoi);
                    //~ rectangle(warpedImage, rightLineRoi, Scalar(0, 0, 255), 1);
                }
                
                // Check if lines are parallel
                if (predictedLane.size() > 1) {
                    drawArrowedLine(warpedImage, getLaneMid(predictedLane), Scalar(200,200,0));
                    setActualLane(predictedLane);
                    //~ setActualLane(lane);
                    
                    //~ if (checkParallelLine(predictedLane)) {
                        //~ // Save detected lane
                        //~ setActualLane(predictedLane);
                    //~ }
                    predictedLane.clear();
                }
                else {
                    //~ setActualLane();
                }
            }
            else {
                cout << "No lines found..." << endl;
                //~ setActualLane(predictedLane);
                //~ resetRois(warpedImage.size());
            }
            drawCenterLine(warpedImage, Scalar(0, 255, 0));
            setOutputImageData(warpedImage);
        }
    }
    
    cout << "THREAD: Lane detection ended." << endl;
    
    return NULL;
}

void imageProcessing2 (Mat& image, vector<Vec4i>& lines)
{
    autoAdjustImage(image);

    Mat grayImage;
    whiteColorFilter(image, grayImage);

    //~ Mat yellowImage;
    //~ yellowColorFilter(image, yellowImage);

    // Merge images
    //~ bitwise_or(image, yellowImage, grayImage);

    // Blur image
    GaussianBlur(grayImage, grayImage, Size(5, 5), 0);
    
    // Detect lines
    detectLines(grayImage, lines);
    //~ cvtColor(grayImage, image, CV_GRAY2BGR);
}

void *laneDetection2 (void *arg)
{
    cout << "THREAD: Lane detection started." << endl;

    // Initialize line prediction
    KalmanFilter kfL(4, 4, 0);
    KalmanFilter kfR(4, 4, 0);
    initLinePrediction(kfL, 4);
    initLinePrediction(kfR, 4);
    vector<Vec4i> predLLines;
    vector<Vec4i> predRLines;
    vector<Vec4i> predictedLane;
    
    vector<Vec4i> ll;
    vector<Vec4i> rl;
    
    while ((getModuleState() & MODULE_DETECT_LANES) == MODULE_DETECT_LANES) {
        Mat image, homography;
        getInputImageData(image);
        getExtr(homography);

        if (!image.empty()) {
            Mat warpedImage;
            if (!homography.empty()) {
                warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            }
            else {
                image.copyTo(warpedImage);
            }
                
            for (size_t i = 0; i < warpedImage.rows; i = i + warpedImage.rows/3 - 1) {
                vector<Vec4i> lines, someLines;
                Rect rOI = Rect(Point(0, i), Point(warpedImage.cols-1, i + warpedImage.rows/3 - 1));
                i++;
                Mat windowedImage;
                warpedImage(rOI).copyTo(windowedImage);
                imageProcessing(windowedImage, lines);
                
                // If no lines where found, take predicted lines
                if (lines.size() <= 0) {
                    lines.insert(lines.end(), predictedLane.begin(), predictedLane.end());
                }
        
                if (lines.size() > 0) {
                    // Show lines
                    //~ drawArrowedLines(warpedImage, lines, Scalar(0,0,255));
    
                    // Filter lines
                    vector<Vec4i> leftLines;
                    vector<Vec4i> rightLines;
                    vector<Vec4i> lane;
                    filterLines(lines, warpedImage.size(), leftLines, rightLines, lane);
    
                    // Predict lane
                    if (lane.size() == 2) {
                        //~ vector<Vec4i> ll;
                        ll.push_back(lane[0]);
                        predictLine(ll, kfL, 4, predLLines);
                        vector<Vec4i> lls;
                        lls.push_back(Vec4i(predLLines[0][0], predLLines[0][1]+i, predLLines[0][2], predLLines[0][3]+i));
                        drawArrowedLines(warpedImage, lls, Scalar(255, 0, 0));
                        //~ vector<Vec4i> rl;
                        rl.push_back(lane[1]);
                        predictLine(rl, kfR, 4, predRLines);
                        vector<Vec4i> rls;
                        rls.push_back(Vec4i(predRLines[0][0], predRLines[0][1]+i, predRLines[0][2], predRLines[0][3]+i));
                        drawArrowedLines(warpedImage, rls, Scalar(0, 0, 255));
                    }
                    if (predLLines.size() == 1) {
                        predictedLane.push_back(predLLines[0]);
                        predLLines.clear();
                    }
                    
                    if (predRLines.size() == 1) {
                        predictedLane.push_back(predRLines[0]);
                        predRLines.clear();
                    }
                    
                    // Check if lines are parallel
                    if (predictedLane.size() > 1) {
                        Vec4i laneMid = getLaneMid(predictedLane);
                        laneMid[1] += i;
                        laneMid[3] += i;
                        drawArrowedLine(warpedImage, laneMid, Scalar(200,200,0));
                        setActualLane(predictedLane);
                        predictedLane.clear();
                    }
                }
                else {
                    cout << "No lines found..." << endl;
                }
            }
                
            drawCenterLine(warpedImage, Scalar(0, 255, 0));
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
    
    //~ kf.transitionMatrix.at<double>(0, 0) = 1;
    //~ kf.transitionMatrix.at<double>(0, 1) = 0;
    //~ kf.transitionMatrix.at<double>(0, 2) = 0;
    //~ kf.transitionMatrix.at<double>(0, 3) = 0;
    //~ 
    //~ kf.transitionMatrix.at<double>(1, 0) = 0;
    //~ kf.transitionMatrix.at<double>(1, 1) = 1;
    //~ kf.transitionMatrix.at<double>(1, 2) = 0;
    //~ kf.transitionMatrix.at<double>(1, 3) = 0;
    //~ 
    //~ kf.transitionMatrix.at<double>(2, 0) = 0;
    //~ kf.transitionMatrix.at<double>(2, 1) = 0;
    //~ kf.transitionMatrix.at<double>(2, 2) = 1;
    //~ kf.transitionMatrix.at<double>(2, 3) = 0;
    //~ 
    //~ kf.transitionMatrix.at<double>(3, 0) = 0;
    //~ kf.transitionMatrix.at<double>(3, 1) = 0;
    //~ kf.transitionMatrix.at<double>(3, 2) = 0;
    //~ kf.transitionMatrix.at<double>(3, 3) = 1;
    
    setIdentity(kf.transitionMatrix);
    setIdentity(kf.measurementMatrix);
    setIdentity(kf.processNoiseCov, Scalar::all(500));
    setIdentity(kf.measurementNoiseCov, Scalar::all(500));
    //~ setIdentity(kf.errorCovPre, Scalar::all(1000));
    //~ setIdentity(kf.errorCovPost, Scalar::all(500));
}

/**
 * @brief This function predicts the line points.
 *
 * @todo Measured lines unnecessary beacause measLines = lines
 */

void predictLine (vector<Vec4i> lines, KalmanFilter& kf, int valueCnt, vector<Vec4i>& predLines)
{
    predLines.clear();

    for (size_t i = 0; i < lines.size(); i++) {
        Mat prediction = kf.predict();
        Vec4i predictedPts(prediction.at<float>(0), prediction.at<float>(1), prediction.at<float>(2), prediction.at<float>(3));

        Mat measurement = Mat::zeros(valueCnt, 1, CV_32F);
        for (size_t j = 0; j < valueCnt; j++) {
            measurement.at<float>(j) = lines[i][j];
        }

        Mat estimated = kf.correct(measurement);

        Vec4i statePts(estimated.at<float>(0), estimated.at<float>(1), estimated.at<float>(2), estimated.at<float>(3));
        predLines.clear();
        predLines.push_back(statePts);
    }
}
