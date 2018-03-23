/**
 * @file lane_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "lane_detection.hpp"

float getEuclidDistance(cv::Point pt1, cv::Point pt2)
{
   cv::Point diff = pt1 - pt2;
   return sqrt(pow(diff.x, 2) + pow(diff.y, 2));
   // or
   //~ return norm(pt1-pt2);
}

float getRho (cv::Point pt1, cv::Point pt2)
{
   return (pt1.y * pt2.x - pt2.y * pt1.x)/getEuclidDistance(pt1, pt2);
}

float getTheta (cv::Point pt1, cv::Point pt2)
{
   return atan2((pt2.y - pt1.y), (pt2.x - pt1.x));
}

void cvtLinesToLinesPolar (std::vector<cv::Vec4i> lines, std::vector<cv::Vec2f>& linesPolar)
{
    linesPolar.clear();
    for (size_t i = 0; i < lines.size(); i++) {
        float theta = getTheta(cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3]));
        float rho = getRho(cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3]));

        linesPolar.push_back(cv::Vec2f(rho, theta));
    }
}

void sortLineDirections (std::vector<cv::Vec4i>& lines)
{
   for (size_t i = 0; i <  lines.size(); i++) {
      cv::Point pt1 = cv::Point(lines[i][0], lines[i][1]);
      cv::Point pt2 = cv::Point(lines[i][2], lines[i][3]);

      if (pt1.y > pt2.y) {
         cv::Point ptTmp = pt1;
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

void detectLines (cv::Mat grayImage, std::vector<cv::Vec4i>& lines)
{
   lines.clear();

   cv::Mat imageEdges;
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

void drawLine (cv::Mat& image, cv::Vec4i l, cv::Scalar color)
{
    line(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), color, 2);
}

void drawLines (cv::Mat& image, std::vector<cv::Vec4i> lines, cv::Scalar color)
{
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Vec4i l = lines[i];
        line(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), color, 2);
    }
}

void drawArrowedLine (cv::Mat& image, cv::Vec4i l, cv::Scalar color)
{
    arrowedLine(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), color, 2);
}

void drawArrowedLines (cv::Mat& image, std::vector<cv::Vec4i> lines, cv::Scalar color)
{
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Vec4i l = lines[i];
        arrowedLine(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), color, 2);
    }
}

void drawCenterLine (cv::Mat& image, cv::Scalar color)
{
    cv::Point pt1((image.cols/2)-1, 0);
    cv::Point pt2(pt1.x, image.rows-1);
    line(image, pt1, pt2, color, 1);
}

/**
 * @brief This function filters left and right lines. It also filters
 *          the most left line in right image half and the most right line
 *          in the left image half.
 */

void filterLines (std::vector<cv::Vec4i> lines, cv::Size imageSize, std::vector<cv::Vec4i>& leftLines, std::vector<cv::Vec4i>& rightLines, std::vector<cv::Vec4i>& lane)
{
    lane.clear();
    cv::Vec4i leftLine = cv::Vec4i(imageSize.width-1, imageSize.height-1, imageSize.width-1, 0);
    cv::Vec4i rightLine = cv::Vec4i(0, imageSize.height-1, 0, 0);

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

float distanceBetweenLines (cv::Vec4i line1, cv::Vec4i line2)
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

bool checkParallelLine (std::vector<cv::Vec4i> lines)
{
    float thetaLeft = getTheta(cv::Point(lines[0][0], lines[0][1]), cv::Point(lines[0][2],lines[0][3]));
    float thetaRight = getTheta(cv::Point(lines[1][0], lines[1][1]), cv::Point(lines[1][2], lines[1][3]));
    //~ std::cout << "Left line theta: " << thetaLeft << ", Right line theta " << thetaRight << std::endl;
    if (thetaLeft == thetaRight) {
        std::cout << "Lines are parallel!" << std::endl;
        std::cout << "Distance between lines is " << distanceBetweenLines(lines[0], lines[1])*getPxPerMm() << std::endl;
        return true;
    }
    else {
        return false;
    }
}

bool checkForStopLine (std::vector<cv::Vec4i> lines, cv::Vec4i& stopLine)
{
    for (size_t i = 0; i < lines.size(); i++) {
        float theta = getTheta(cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2],lines[i][3]));
        if ((theta < (CV_PI*0.2)) || (theta > (CV_PI*0.80))) {
            stopLine = lines[i];
            std::cout << "Stop line detected!" << std::endl;
            return true;
        }
    }
    return false;
}

cv::Vec4i getLaneMid (std::vector<cv::Vec4i> lane)
{
    cv::Point ptl1 = cv::Point(lane[0][0], lane[0][1]);
    cv::Point ptl2 = cv::Point(lane[0][2], lane[0][3]);
    cv::Point ptr1 = cv::Point(lane[1][0], lane[1][1]);
    cv::Point ptr2 = cv::Point(lane[1][2], lane[1][3]);
    
    cv::Point ptmid1 = cv::Point(ptl1.x + (ptr1.x - ptl1.x)/2, ptl1.y + (ptr1.y - ptl1.y)/2);
    cv::Point ptmid2 = cv::Point(ptl2.x + (ptr2.x - ptl2.x)/2, ptl2.y + (ptr2.y - ptl2.y)/2);
    cv::Vec4i laneMid = cv::Vec4i(ptmid1.x, ptmid1.y, ptmid2.x, ptmid2.y);
    
    return laneMid;
}

/**
 * @brief This function initializes the line prediction with a Kalman filter.
 */

void initLinePrediction (cv::KalmanFilter& kf, int valueCnt)
{
    kf.statePre = cv::Mat::zeros(valueCnt, 1, CV_32F);
    
    setIdentity(kf.transitionMatrix);
    setIdentity(kf.measurementMatrix);
    setIdentity(kf.processNoiseCov, cv::Scalar::all(500));
    setIdentity(kf.measurementNoiseCov, cv::Scalar::all(500));
    //~ setIdentity(kf.errorCovPre, cv::Scalar::all(1000));
    //~ setIdentity(kf.errorCovPost, cv::Scalar::all(500));
}

/**
 * @brief This function predicts the line points.
 *
 * @todo Measured lines unnecessary beacause measLines = lines
 */

void predictLine (std::vector<cv::Vec4i> lines, cv::KalmanFilter& kf, int valueCnt, std::vector<cv::Vec4i>& predLines)
{
    //~ predLines.clear();

    for (size_t i = 0; i < lines.size(); i++) {
        cv::Mat prediction = kf.predict();
        cv::Vec4i predictedPts(prediction.at<float>(0), prediction.at<float>(1), prediction.at<float>(2), prediction.at<float>(3));

        cv::Mat measurement = cv::Mat::zeros(valueCnt, 1, CV_32F);
        for (size_t j = 0; j < valueCnt; j++) {
            measurement.at<float>(j) = lines[i][j];
        }

        cv::Mat estimated = kf.correct(measurement);

        cv::Vec4i statePts(estimated.at<float>(0), estimated.at<float>(1), estimated.at<float>(2), estimated.at<float>(3));
        predLines.clear();
        predLines.push_back(statePts);
    }
}

void imageProcessing (cv::Mat& image, std::vector<cv::Vec4i>& lines)
{
    autoAdjustBrightness(image);
    
    // Blur image
    //~ GaussianBlur(image, image, cv::Size(5, 5), 0);

    cv::Mat grayImage;
    whiteColorFilter(image, grayImage);
    
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5), cv::Point(2, 2));
    erode(grayImage, grayImage, kernel);

    //~ cv::Mat yellowImage;
    //~ yellowColorFilter(image, yellowImage);

    // Merge images
    //~ bitwise_or(image, yellowImage, grayImage);

    // Blur image
    GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);

    // Detect lines
    detectLines(grayImage, lines);
    //~ cvtColor(grayImage, image, CV_GRAY2BGR);
}

void resetRois (cv::Size imageSize)
{
    setRoiLeft(cv::Rect(cv::Point(0, 0), cv::Point(imageSize.width-1, imageSize.height-1)));
    setRoiRight(cv::Rect(cv::Point(0, 0), cv::Point(imageSize.width-1, imageSize.height-1)));
}

void roiOfLine (cv::Vec4i line, cv::Rect& roi, cv::Size imageSize)
{
    if (line[0] <= line[2]) {
        roi = cv::Rect(cv::Point(line[0]-10, line[1]-10), cv::Point(line[2]+10, line[3]+10));
    }
    else {
        roi = cv::Rect(cv::Point(line[0]+10, line[1]-10), cv::Point(line[2]-10, line[3]+10));
    }
    
    // Check if ROI in bound
    if (roi.tl().x < 0) {
        roi = cv::Rect(cv::Point(0, roi.tl().y), roi.br());
    }
    else if (roi.tl().x > (imageSize.width-1)) {
        roi = cv::Rect(cv::Point((imageSize.width-1), roi.tl().y), roi.br());
    }
    
    if (roi.tl().y < 0) {
        roi = cv::Rect(cv::Point(roi.tl().x, 0), roi.br());
    }
    else if (roi.tl().y > (imageSize.height-1)) {
        roi = cv::Rect(cv::Point(roi.tl().x, (imageSize.height-1)), roi.br());
    }
    
    if (roi.br().x < 0) {
        roi = cv::Rect(roi.tl(), cv::Point(0, roi.br().y));
    }
    else if (roi.br().x > (imageSize.width-1)) {
        roi = cv::Rect(roi.tl(), cv::Point((imageSize.width-1), roi.br().y));
    }
    
    if (roi.br().y < 0) {
        roi = cv::Rect(roi.tl(), cv::Point(roi.br().x, 0));
    }
    else if (roi.br().y > (imageSize.height-1)) {
        roi = cv::Rect(roi.tl(), cv::Point(roi.br().x, (imageSize.height-1)));
    }
}

void *laneDetection (void *arg)
{
    std::cout << "THREAD: Lane detection started." << std::endl;
    
    initOutputImageData();
    //~ initInterImageData();
    
    // Initialize line prediction
    cv::KalmanFilter kfL(4, 4, 0);
    cv::KalmanFilter kfR(4, 4, 0);
    cv::KalmanFilter kfM(4, 4, 0);
    initLinePrediction(kfL, 4);
    initLinePrediction(kfR, 4);
    initLinePrediction(kfM, 4);
    std::vector<cv::Vec4i> leftLinesPredicted;
    std::vector<cv::Vec4i> rightLinesPredicted;
    std::vector<cv::Vec4i> lanePredicted;
    std::vector<cv::Vec4i> predictedTrajectory;
    
    std::vector<cv::Vec4i> leftLine;
    std::vector<cv::Vec4i> rightLine;
    time_t prevTs = 0;
    
    while ((getModuleState() & MODULE_DETECT_LANES) == MODULE_DETECT_LANES) {
        cv::Mat image, homography;
        time_t ts = getInputImageData(image);
        getExtr(homography);

        if (!image.empty()) {
            cv::Mat warpedImage;
            if (!homography.empty()) {
                warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            }
            else {
                image.copyTo(warpedImage);
            }

            std::vector<cv::Vec4i> lines, someLines;
            //~ cv::Rect leftLineRoi = getRoiLeft();
            //~ cv::Rect rightLineRoi = getRoiRight();

            imageProcessing(warpedImage, lines);
            //~ // Detect stop lines
            //~ cv::Vec4i stopLine;
            //~ if (checkForStopLine(lines, stopLine)) {
                //~ drawLine(warpedImage, stopLine, cv::Scalar(0,0,255));
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
                //~ lines.insert(lines.end(), leftLinesPredicted.begin(), leftLinesPredicted.end());
                //~ lines.insert(lines.end(), rightLinesPredicted.begin(), rightLinesPredicted.end());
                lines.insert(lines.end(), lanePredicted.begin(), lanePredicted.end());
            }

            if (lines.size() > 0) {
                // Show lines
                //~ drawArrowedLines(warpedImage, lines, cv::Scalar(0,0,255));

                // Filter lines
                std::vector<cv::Vec4i> leftLines;
                std::vector<cv::Vec4i> rightLines;
                std::vector<cv::Vec4i> lane;
                filterLines(lines, warpedImage.size(), leftLines, rightLines, lane);

                // Predict lane
                //~ if (lane.size() == 2) {
                    //~ //~ std::vector<cv::Vec4i> leftLine;
                    //~ leftLine.push_back(lane[0]);
                    //~ predictLine(leftLine, kfL, 4, leftLinesPredicted);
                    //~ drawArrowedLines(warpedImage, leftLinesPredicted, cv::Scalar(255, 0, 0));
                    //~ //~ std::vector<cv::Vec4i> rightLine;
                    //~ rightLine.push_back(lane[1]);
                    //~ predictLine(rightLine, kfR, 4, rightLinesPredicted);
                    //~ drawArrowedLines(warpedImage, rightLinesPredicted, cv::Scalar(0, 0, 255));
                //~ }
                // Predict left line
                if (leftLines.size() > 0) {
                    std::vector<cv::Vec4i> leftLine;
                    leftLine.push_back(lane[0]);
                    predictLine(leftLine,  kfL, 4, leftLinesPredicted);
                    drawArrowedLines(warpedImage, leftLinesPredicted, cv::Scalar(255, 0, 0));
                }
                //~ if (leftLinesPredicted.size() > 0) {
                if (leftLinesPredicted.size() == 1) {
                    lanePredicted.push_back(leftLinesPredicted[0]);
                    leftLinesPredicted.clear();
                    // Set left ROI with offset
                    //~ roiOfLine(leftLinesPredicted[0], leftLineRoi, warpedImage.size());
                    //~ setRoiLeft(leftLineRoi);
                    //~ rectangle(warpedImage, leftLineRoi, cv::Scalar(255, 0, 0), 1);
                }
                else {
                    lanePredicted.push_back(cv::Vec4i(0, 0, 0, 0));
                }
                
                //Predict right line
                if (rightLines.size() > 0) {
                    std::vector<cv::Vec4i> rightLine;
                    rightLine.push_back(lane[1]);
                    predictLine(rightLine, kfR, 4, rightLinesPredicted);
                    drawArrowedLines(warpedImage, rightLinesPredicted, cv::Scalar(0, 0, 255));
                }
                //~ if (rightLinesPredicted.size() > 0) {
                if (rightLinesPredicted.size() == 1) {
                    lanePredicted.push_back(rightLinesPredicted[0]);
                    rightLinesPredicted.clear();
                    // Set right ROI with offset
                    //~ roiOfLine(rightLinesPredicted[0], rightLineRoi, warpedImage.size());
                    //~ setRoiRight(rightLineRoi);
                    //~ rectangle(warpedImage, rightLineRoi, cv::Scalar(0, 0, 255), 1);
                }
                else {
                    lanePredicted.push_back(cv::Vec4i(warpedImage.cols-1, 0, warpedImage.cols-1, 0));
                }
                
                // Check if lines are parallel
                if (lanePredicted.size() > 0) {
                    //~ drawArrowedLine(warpedImage, getLaneMid(lanePredicted), cv::Scalar(200,200,0));
                    setActualLane(lanePredicted);
                    
                    //~ setActualLane(lane);
                    
                    //~ predictLine(lanePredicted, kfM, 4, predictedTrajectory);
                    //~ drawArrowedLines(warpedImage, predictedTrajectory, cv::Scalar(200,200,0));
                    
                    //~ if (checkParallelLine(lanePredicted)) {
                        //~ // Save detected lane
                        //~ setActualLane(lanePredicted);
                    //~ }
                    lanePredicted.clear();
                }
                else {
                    //~ setActualLane();
                }
            }
            else {
                std::cout << "Lane detection: No lines found..." << std::endl;
                setActualLane(lanePredicted);
                //~ resetRois(warpedImage.size());
            }
            drawCenterLine(warpedImage, cv::Scalar(0, 255, 0));
            setOutputImageData(warpedImage, ts);
            //~ setInterImageData(warpedImage, ts);
            prevTs = ts;
        }
    }
    
    std::cout << "THREAD: Lane detection ended." << std::endl;
    
    return NULL;
}


void imageProcessing2 (cv::Mat& image, std::vector<cv::Vec4i>& lines)
{
    autoAdjustBrightness(image);

    cv::Mat grayImage;
    whiteColorFilter(image, grayImage);
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5), cv::Point(2, 2));
    erode(grayImage, grayImage, kernel);
    
    //~ cv::Mat yellowImage;
    //~ yellowColorFilter(image, yellowImage);

    // Merge images
    //~ bitwise_or(image, yellowImage, grayImage);

    // Blur image
    GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);
    
    // Detect lines
    detectLines(grayImage, lines);
    cvtColor(grayImage, image, CV_GRAY2BGR);
}

void *laneDetection2 (void *arg)
{
    std::cout << "THREAD: Lane detection started." << std::endl;
    
    //~ initOutputImageData();
    initInterImageData();

    // Initialize line prediction
    cv::KalmanFilter kfLT(4, 4, 0);
    cv::KalmanFilter kfLM(4, 4, 0);
    cv::KalmanFilter kfLB(4, 4, 0);
    cv::KalmanFilter kfRT(4, 4, 0);
    cv::KalmanFilter kfRM(4, 4, 0);
    cv::KalmanFilter kfRB(4, 4, 0);
    initLinePrediction(kfLT, 4);
    initLinePrediction(kfLM, 4);
    initLinePrediction(kfLB, 4);
    initLinePrediction(kfRT, 4);
    initLinePrediction(kfRM, 4);
    initLinePrediction(kfRB, 4);
    std::vector<cv::KalmanFilter> kf;
    kf.push_back(kfLT);
    kf.push_back(kfLM);
    kf.push_back(kfLB);
    kf.push_back(kfRT);
    kf.push_back(kfRM);
    kf.push_back(kfRB);
    
    std::vector<cv::Vec4i> leftLine;
    std::vector<cv::Vec4i> rightLine;
    
    std::vector<cv::Vec4i> lanePredicted;
    
    time_t prevTs = 0;
    
    while ((getModuleState() & MODULE_DETECT_LANES) == MODULE_DETECT_LANES) {
        cv::Mat image, homography;
        time_t ts = getInputImageData(image);
        getExtr(homography);

        if (!image.empty()) {
            cv::Mat warpedImage;
            if (!homography.empty()) {
                warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            }
            else {
                image.copyTo(warpedImage);
            }
            
            int kfIt = 0;
            for (size_t i = 0; i < warpedImage.rows; i = i + warpedImage.rows/3 - 1) {
                std::vector<cv::Vec4i> lines;
                std::vector<cv::Vec4i> leftLinesPredicted;
                std::vector<cv::Vec4i> rightLinesPredicted;
                // Set ROI
                cv::Rect rOI = cv::Rect(cv::Point(0, i), cv::Point(warpedImage.cols-1, i + warpedImage.rows/3));
                
                cv::Mat windowedImage;
                warpedImage(rOI).copyTo(windowedImage);
                imageProcessing2(windowedImage, lines);
                rectangle(warpedImage, rOI, cv::Scalar(0, 255, 0), 1);
                windowedImage.copyTo(warpedImage(rOI));
                
                // If no lines where found, take predicted lines
                //~ if (lines.size() <= 0) {
                    //~ lines.insert(lines.end(), lanePredicted.begin(), lanePredicted.end());
                //~ }
        
                if (lines.size() > 0) {
                    // Filter lines
                    std::vector<cv::Vec4i> leftLinesFiltered;
                    std::vector<cv::Vec4i> rightLinesFiltered;
                    std::vector<cv::Vec4i> laneSuggestion;
                    filterLines(lines, warpedImage.size(), leftLinesFiltered, rightLinesFiltered, laneSuggestion);
                    
                    // Check lane suggestion
                    // Check orientation
                    if (laneSuggestion[0][1] > laneSuggestion[0][3]) {
                        std::cout << "Lane detection: Wrong left line orientation" << std::endl;
                    }
                    else if (laneSuggestion[1][1] > laneSuggestion[1][3]) {
                        std::cout << "Lane detection: Wrong right line orientation!" << std::endl;
                    }
                    else {
                        // Predict left line
                        if (leftLinesFiltered.size() > 0) {
                            //~ std::vector<cv::Vec4i> leftLine;
                            leftLine.push_back(laneSuggestion[0]);
                            predictLine(leftLine, kf[kfIt], 4, leftLinesPredicted);
                            leftLinesPredicted[0][1] = leftLinesPredicted[0][1]+i;
                            leftLinesPredicted[0][3] = leftLinesPredicted[0][3]+i;
                            drawArrowedLines(warpedImage, leftLinesPredicted, cv::Scalar(255, 0, 0));
                        }
                        if (leftLinesPredicted.size() == 1) {
                            lanePredicted.push_back(leftLinesPredicted[0]);
                        }
                        else {
                            lanePredicted.push_back(cv::Vec4i(0, 0, 0, 0));
                        }
                        
                        // Predict right line
                        if (rightLinesFiltered.size() > 0) {
                            //~ std::vector<cv::Vec4i> rightLine;
                            rightLine.push_back(laneSuggestion[1]);
                            predictLine(rightLine, kf[kfIt+3], 4, rightLinesPredicted);
                            rightLinesPredicted[0][1] = rightLinesPredicted[0][1]+i;
                            rightLinesPredicted[0][3] = rightLinesPredicted[0][3]+i;
                            drawArrowedLines(warpedImage, rightLinesPredicted, cv::Scalar(0, 0, 255));
                        }
                        if (rightLinesPredicted.size() == 1) {
                            lanePredicted.push_back(rightLinesPredicted[0]);
                        }
                        else {
                            lanePredicted.push_back(cv::Vec4i(warpedImage.cols-1, 0, warpedImage.cols-1, 0));
                        }
                    }
                    
                }
                else {
                    std::cout << "Lane detection: No lines found..." << std::endl;
                }
                
                // Set actual lane only if all three segments have lines
                if ((lanePredicted.size() == 6) && (2 == i%(warpedImage.rows/3 - 1))) {
                    setActualLane(lanePredicted);
                    lanePredicted.clear();
                }
                 
                i++; //< Iterate for next window
                kfIt++; //< Iterate for next Kalman filter
            }
            
            //! @todo Move this part to planning thread
            // Calculate trajectory
            std::vector<cv::Vec4i> foundLane;
            std::vector<cv::Point> leftLinePts, rightLinePts, midLinePts;
            getActualLane(foundLane);
            if (foundLane.size() != 6) {
                std::cout << "Lane detection: Only part of lane detected. foundLane size " << foundLane.size() << std::endl;
            }
            for (size_t n = 0; n < foundLane.size(); n += 2) {
                std::vector<cv::Vec4i> lanePart;
                lanePart.push_back(foundLane[n]);
                lanePart.push_back(foundLane[n+1]);
                cv::Vec4i laneMid = getLaneMid(lanePart);
                //~ drawArrowedLine(warpedImage, laneMid, cv::Scalar(200,200,0));
                midLinePts.push_back(cv::Point(laneMid[0], laneMid[1]));
                midLinePts.push_back(cv::Point(laneMid[2], laneMid[3]));
            }
            // Draw trajectory
            polylines(warpedImage, midLinePts, false, cv::Scalar(200,200,0), 2);
            // Draw center line
            drawCenterLine(warpedImage, cv::Scalar(0, 255, 0));
            //~ setOutputImageData(warpedImage);
            setInterImageData(warpedImage, ts);
            prevTs = ts;
        }
    }
    
    std::cout << "THREAD: Lane detection ended." << std::endl;
    
    return NULL;
}
