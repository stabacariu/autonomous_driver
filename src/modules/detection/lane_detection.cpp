/**
 * @file lane_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "lane_detection.hpp"
#include "configuration.hpp"

void LaneDetector::run (ImageData& inputImage, ImageData& outputImage, LaneData& lane)
{
    std::cout << "THREAD: Lane detection started." << std::endl;
    running = true;
    
    Configurator& config = Configurator::instance();
    camCalibConfig = config.getCameraCalibrationConfig();
    
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
    
    std::vector<cv::Vec4i> leftLine;
    std::vector<cv::Vec4i> rightLine;
    
    cv::Mat homography;
    homography = camCalibConfig.homography;
    if (homography.empty()) {
        running = false;
        error = true;
    }
    
    while (running && !error) {
        cv::Mat image;
        image = inputImage.read();
        
        if (!image.empty()) {
            cv::Mat warpedImage;
            if (!homography.empty()) {
                warpPerspective(image, warpedImage, homography, image.size(), CV_WARP_INVERSE_MAP + CV_INTER_LINEAR);
            }
            else {
                image.copyTo(warpedImage);
            }
            
            cv::Mat prepImage;
            prepareImage(warpedImage, prepImage);

            // Detect lines
            std::vector<cv::Vec4i> lines;
            detectLines(prepImage, lines);

            // If no lines where found, take predicted lines
            if (lines.size() <= 0) {
                lines.insert(lines.end(), lanePredicted.begin(), lanePredicted.end());
            }

            if (lines.size() > 0) {
                // Show lines
                //~ drawArrowedLines(warpedImage, lines, cv::Scalar(0,0,255));

                // Filter lines
                std::vector<cv::Vec4i> leftLines;
                std::vector<cv::Vec4i> rightLines;
                std::vector<cv::Vec4i> actualLane;
                filterLines(lines, warpedImage.size(), leftLines, rightLines, actualLane);

                // Predict lane
                // Predict left line
                if (leftLines.size() > 0) {
                    std::vector<cv::Vec4i> leftLine;
                    leftLine.push_back(actualLane[0]);
                    predictLine(leftLine,  kfL, 4, leftLinesPredicted);
                    drawLines(warpedImage, leftLinesPredicted, cv::Scalar(255, 0, 0));
                }
                // Check if exaktly one line was predicted
                //~ if (leftLinesPredicted.size() > 0) {
                if (leftLinesPredicted.size() == 1) {
                    lanePredicted.push_back(leftLinesPredicted[0]);
                    leftLinesPredicted.clear();
                }
                else {
                    lanePredicted.push_back(cv::Vec4i(0, 0, 0, 0));
                }
                
                //Predict right line
                if (rightLines.size() > 0) {
                    std::vector<cv::Vec4i> rightLine;
                    rightLine.push_back(actualLane[1]);
                    predictLine(rightLine, kfR, 4, rightLinesPredicted);
                    drawLines(warpedImage, rightLinesPredicted, cv::Scalar(0, 0, 255));
                }
                // Check if exaktly one line was predicted
                //~ if (rightLinesPredicted.size() > 0) {
                if (rightLinesPredicted.size() == 1) {
                    lanePredicted.push_back(rightLinesPredicted[0]);
                    rightLinesPredicted.clear();
                }
                else {
                    lanePredicted.push_back(cv::Vec4i(warpedImage.cols-1, 0, warpedImage.cols-1, 0));
                }
                
                // Check lane has any line
                if (lanePredicted.size() >= 1) {
                    //~ drawLine(warpedImage, getLaneMid(lanePredicted), cv::Scalar(200,200,0));
                    //~ lane.setLeftLine(cvtVec4iToRoadMarking(lanePredicted[0]));
                    lane.setLeftLine(lanePredicted[0]);
                    //~ lane.setRightLine(cvtVec4iToRoadMarking(lanePredicted[1]));
                    lane.setRightLine(lanePredicted[1]);
                }
                lanePredicted.clear();
            }
            
            drawCenterLine(warpedImage, cv::Scalar(0, 255, 0));
            outputImage.write(warpedImage);
            outputImage.setTime(inputImage.getTime());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
    std::cout << "THREAD: Lane detection ended." << std::endl;
}

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

bool checkParallelLine (std::vector<cv::Vec4i> lines)
{
    float thetaLeft = getTheta(cv::Point(lines[0][0], lines[0][1]), cv::Point(lines[0][2],lines[0][3]));
    float thetaRight = getTheta(cv::Point(lines[1][0], lines[1][1]), cv::Point(lines[1][2], lines[1][3]));
    //~ std::cout << "Left line theta: " << thetaLeft << ", Right line theta " << thetaRight << std::endl;
    if (thetaLeft == thetaRight) {
        std::cout << "Lines are parallel!" << std::endl;
        //~ std::cout << "Distance between lines is " << distanceBetweenLines(lines[0], lines[1])*getPxPerMm() << std::endl;
        std::cout << "Distance between lines is " << distanceBetweenLines(lines[0], lines[1]) << std::endl;
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

void initLinePrediction (cv::KalmanFilter& kf, int numValues)
{
    kf.statePre = cv::Mat::zeros(numValues, 1, CV_32F);
    
    setIdentity(kf.transitionMatrix);
    setIdentity(kf.measurementMatrix);
    setIdentity(kf.processNoiseCov, cv::Scalar::all(500));
    setIdentity(kf.measurementNoiseCov, cv::Scalar::all(500));
    //~ setIdentity(kf.errorCovPre, cv::Scalar::all(1000));
    //~ setIdentity(kf.errorCovPost, cv::Scalar::all(500));
}

/**
 * @todo Measured lines unnecessary beacause measLines = lines
 */
void predictLine (std::vector<cv::Vec4i> lines, cv::KalmanFilter& kf, int numValues, std::vector<cv::Vec4i>& predLines)
{
    for (size_t i = 0; i < lines.size(); i++) {
        cv::Mat prediction = kf.predict();
        cv::Vec4i predictedPts(prediction.at<float>(0), prediction.at<float>(1), prediction.at<float>(2), prediction.at<float>(3));

        cv::Mat measurement = cv::Mat::zeros(numValues, 1, CV_32F);
        for (size_t j = 0; j < numValues; j++) {
            measurement.at<float>(j) = lines[i][j];
        }

        cv::Mat estimated = kf.correct(measurement);

        cv::Vec4i statePts(estimated.at<float>(0), estimated.at<float>(1), estimated.at<float>(2), estimated.at<float>(3));
        predLines.clear();
        predLines.push_back(statePts);
    }
}

void prepareImage (cv::Mat image, cv::Mat& prepImage)
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
    //~ GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);
    GaussianBlur(grayImage, prepImage, cv::Size(5, 5), 0);

    //~ cvtColor(grayImage, image, CV_GRAY2BGR);
}

void resetRois (cv::Size imageSize)
{
    //~ setRoiLeft(cv::Rect(cv::Point(0, 0), cv::Point(imageSize.width-1, imageSize.height-1)));
    //~ setRoiRight(cv::Rect(cv::Point(0, 0), cv::Point(imageSize.width-1, imageSize.height-1)));
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
