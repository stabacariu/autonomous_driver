/**
 * @file lane_detection.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef LANE_DETECTION_HPP
#define LANE_DETECTION_HPP

#include <iostream>
#include <fstream>
#include <atomic>
#include <opencv2/opencv.hpp>
#include "image_data.hpp"
#include "image_filter.hpp"
#include "lane_data.hpp"

//! @addtogroup lane_detection
//! @{

/**
 * @brief A lane detection class
 * 
 * This class describes a lane detector 
 */
class LaneDetector {
public:
    ~LaneDetector() = default;
    
    /**
     * @brief Start lane detection
     * 
     * This function starts the lane detection thread.
     * 
     * @param inputImage Input image captured by image acquisitor
     * @param outputImage Output image with result for showing on user interface
     * @param actualLane Actual detected lane
     */
    void start(ImageData& inputImage, ImageData& outputImage, LaneData& actualLane);
    
    /**
     * @brief Stop lane detection
     * 
     * This function stops the lane detection thread.
     */
    void stop(void);
    
    /**
     * @brief Check if lane detection is running
     * 
     * This function checks if the lane detection is running…
     * 
     * @return True if lane detection is running, else false.
     */
    bool isRunning(void);
    
private:
    std::atomic_bool running{false}; //!< Thread running flag
};

/**
 * @brief Get euclidian distance between two points
 * 
 * This function calculates the euclidian distance between two points.
 * 
 * @param pt1 First point
 * @param pt2 Second point
 */
float getEuclidDistance(cv::Point pt1, cv::Point pt2);

/**
 * @brief Get distance &rho; of a line to the origin
 * 
 * This function calculates the distance &rho; of a line to the origin in
 * polar form (&rho;, &theta;).
 * 
 * @param pt1 Starting point of line
 * @param pt2 Ending point of line
 * @return The distance &rho; of the line to the origin in polar form
 */
float getRho (cv::Point pt1, cv::Point pt2);

/**
 * @brief Get the orthogonal angle &theta; of the slope of a line to the origin
 * 
 * This function calculates the orthogonal angle &theta; of the slope 
 * of a line in in relation to the origin for the polar form
 * (&rho;, &theta;).
 * 
 * @param pt1 Starting point of the line
 * @param pt2 Ending point of the line
 * @return The orthogonal angle &theta; of the line to the origin for the polar form
 */
float getTheta (cv::Point pt1, cv::Point pt2);

/**
 * @brief Get the middle line of a lane
 * 
 * This function gets the middle line of a lane as starting and ending
 * point.
 * 
 * @param lane Lane as vector of zwo lines with starting and ending point
 * @return Middle line as starting and ending point
 */
cv::Vec4i getLaneMid (std::vector<cv::Point> lane);

/**
 * @brief Convert lines as Vec4i to polar coordinates (&rho;, &theta;)
 * 
 * This function converts a line vector containing lines as Vec4i to polar
 * coordinates (&rho;, &theta;).
 * 
 * @param lines Lines to convert
 * @param linesPolar Result as (&rho;, &theta;)
 */
void cvtLinesToLinesPolar (std::vector<cv::Vec4i> lines, std::vector<cv::Vec2f>& linesPolar);

/**
 * @brief Sort line direction
 * 
 * This function sorts a vector of lines and changes their direction so
 * that all lines have the same direction.
 * 
 * @param lines Lines to sort 
 */
void sortLineDirections (std::vector<cv::Vec4i>& lines);

/**
 * @brief Detect lines in a gray scale image
 * 
 * This function detects lines in a gray scale image with a Canny filter.
 * 
 * @param grayImage Gray scale input image
 * @param lines Detected lines
 */
void detectLines (cv::Mat grayImage, std::vector<cv::Vec4i>& lines);

/**
 * @brief Draw line
 * 
 * This function draws a line on to an image.
 * 
 * @param image Image to draw on
 * @param l Line to draw
 * @param color Color of line to draw
 */
void drawLine (cv::Mat& image, cv::Vec4i l, cv::Scalar color);

/**
 * @brief Draw lines
 * 
 * This function draws lines on to an image.
 * 
 * @param image Image to draw on
 * @param lines Lines to draw
 * @param color Color of lines to draw
 */
void drawLines (cv::Mat& image, std::vector<cv::Vec4i> lines, cv::Scalar color);

/**
 * @brief Draw an arrowed line
 * 
 * This function draws an arrowed line on an input image with a color.
 * 
 * @param image Image matrix
 * @param line Line
 * @param color Line color as RGB scalar value
 */
void drawArrowedLine (cv::Mat& image, cv::Vec4i line, cv::Scalar color);

/**
 * @brief Draw an arrowed line
 * 
 * This function draws an arrowed line on an input image with a color.
 * 
 * @param image Image matrix
 * @param lines Line vector
 * @param color Line color as RGB scalar value
 */
void drawArrowedLines (cv::Mat& image, std::vector<cv::Vec4i> lines, cv::Scalar color);

/**
 * @brief Draw image center line
 * 
 * This function draws a centered line in an input image.
 * 
 * @param image Image matrix
 * @param color Color of center line
 */
void drawCenterLine (cv::Mat& image, cv::Scalar color);

/**
 * @brief Filter detected lines in left and right image part
 * 
 * This function filters left and right lines. It also filters the most
 * left line in right image half and the most right line in the left
 * image half.
 * 
 * @param lines Lines to filter
 * @param imageSize Image size of input image
 * @param leftLines All filtered left lines
 * @param rightLines All filtered right lines
 * @param lane Lane composed of one left and one right line
 */
void filterLines (std::vector<cv::Vec4i> lines, cv::Size imageSize, std::vector<cv::Vec4i>& leftLines, std::vector<cv::Vec4i>& rightLines, std::vector<cv::Vec4i>& lane);

/**
 * @brief Calculate distance between two lines
 * 
 * This function calculates the distance between two lines.
 * 
 * @param line1 First line
 * @param line2 Second line
 * @param Distance between lines
 */
float distanceBetweenLines (cv::Vec4i line1, cv::Vec4i line2);

/**
 * @brief Check if lines are parallel
 * 
 * This function checks if two lines are parallel.
 * 
 * @param lines Lines to check
 * @return True if lines are parallel, else false
 */
bool checkParallelLine (std::vector<cv::Vec4i> lines);

/**
 * @brief Check one of the detected lines is a stop road marking line
 * 
 * This function checks if one of the detected lines is a stop road
 * marking line.
 * 
 * @param lines Lines to check
 * @param stopLine Detected stop line
 * @return True if stop line detected, else false
 */
bool checkForStopLine (std::vector<cv::Vec4i> lines, cv::Vec4i& stopLine);

/**
 * @brief Get lane middle line
 * 
 * This function gets the middle line of a lane. It calculates the half
 * of the distance between the two starting and ending points. These are
 * the starting and ending points of the middle line.
 * 
 * @param lane
 * @return Middle line
 */
cv::Vec4i getLaneMid (std::vector<cv::Vec4i> lane);

/**
 * @brief Initialize a Kalman filter for line prediction
 * 
 * This function initializes a Kalman filter to predict lines found in
 * an input image.
 * 
 * @param kf Kalman filter
 * @param numValues Values to predict
 */
void initLinePrediction (cv::KalmanFilter& kf, int numValues);

/**
 * @brief Predict position of line
 * 
 * This function predicts the line positions found in an input image.
 * It corrects the prediction by considering vector of found/measured
 * lines.
 * 
 * @param lines Vector of lines describet by starting and and ending point
 * @param kf Kalman filter
 * @param numValues Values to predict
 * @param predLines Vector of predicted lines
 */
void predictLine (std::vector<cv::Vec4i> lines, cv::KalmanFilter& kf, int numValues, std::vector<cv::Vec4i>& predLines);

/**
 * @brief Process image
 * 
 * This function process a image. It applies the necessare filters for
 * line detection.
 * 
 * @param image Image matrix
 * @param lines Detected lines
 */
void imageProcessing (cv::Mat& image, std::vector<cv::Vec4i>& lines);

/**
 * @brief Rest ROI
 * 
 * This function resets the region of interest of the detected lines
 * 
 * @param imageSize
 */
void resetRois (cv::Size imageSize);

/**
 * @brief Get ROI of a line
 * 
 * This function gets the region of interest of a line.
 * 
 * @param line
 * @param roi
 * @param imageSize
 */
void roiOfLine (cv::Vec4i line, cv::Rect& roi, cv::Size imageSize);

//! @} lane_detection

#endif // LANE_DETECTION_HPP
