/**
 * @file camera_capture.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#ifndef CAMERA_CAPTURE_HPP
#define CAMERA_CAPTURE_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include "image_acquisitor.hpp"
#include "image_data.hpp"
#include "user_interface_state.hpp"

//! @addtogroup camera_image_acquisitor
//! @brief A module to caputure a camera image
//! @{

/**
 * @brief Camera configuration data structure
 */
struct CameraConfig {
    int id {0}; //!< Camera ID initialized with 0
    cv::Size imageSize {640, 360}; //!< Camera image size
    double fps {15.}; //!< Frames per second caputred by the camera
    double exposure {0.}; //!< Camera exposure value
};

/**
 * @brief Camera calibration configuration data structure
 */
struct CameraCalibrationConfig {
    // Calibration configuration
    std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds> timeStamp; //!< Calibration time stamp
    cv::Size imageSize {640, 360}; //!< Calibration image size
    std::string pattern {"CHESSBOARD"}; //!< Calibration pattern
    cv::Size patternSize {7, 5}; //!< Calibration pattern size
    double patternMm {30.}; //! Size of one pattern element in mm
    int numSamples {50}; //! Number of samples to use for calibration
    // Calibration data
    cv::Mat cameraMatrix; //! Camera matrix containing the focal length and principal image point
    cv::Mat distCoeffs; //! Distortion coefficients for distortion correction
    bool intrCalibDone {false}; //! Calibration done flag
    cv::Mat homography; //!< Homography for perspective transform
    bool extrCalibDone {false}; //! Calibration done flag
    cv::Mat transformation; //!< Transformation matrix for image position
    float pixelPerMm {0.f}; //!< Average mm per pixel
};

/**
 * @brief A camera image acquisition class
 * 
 * This class describes a camera image acquisitor
 */
class CameraImageAcquisitor : public ImageAcquisitor {
public:
    ~CameraImageAcquisitor () = default;
    
    /**
     * @brief Write image to camera image acquisitor
     * 
     * This function writes an image to the camera image acquisitor
     * 
     * @param image Image matrix
     */
    void write (cv::Mat image) override;
    
    /**
     * @brief Read captured camera frame
     * 
     * This function reads the actual image frame captured by the camera
     * image acquisitor
     * 
     * @return Image frame
     */
    cv::Mat read (void) override;
           
    /**
     * @brief Set camera exposure
     * 
     * This function sets the camera exposure value.
     * 
     * @param exposure Camera exposure value
     */
    void setExposure(double exposure);
    
    /**
     * @brief Set frames per second to capture
     * 
     * This function sets the frames per second to capture by the camera.
     * 
     * @param fps Frames per second
     */
    void setFPS (double fps);
    
    /**
     * @brief Set camera matrix containing the focal length and principal image point
     * 
     * This function sets the camera matrix containing the focal length
     * and principal image point.
     * 
     * @param cameraMatrix A 3x3 floating-point matrix \f$A=\begin{bmatrix}f_x & 0 & c_x \\ 0 & f_y & c_y \\ 0 & 0 & 1 \end{bmatrix}\f$ 
     */
    void setCameraMatrix (cv::Mat cameraMatrix);
    
    /**
     * @brief Set distortion coefficients
     * 
     * This function sets the distortion coefficients calculated by the
     * OpenCV-Function calibrateCamera().
     * 
     * @param distCoeffs Distortion coefficients vector \f$(k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6 [, s_1, s_2, s_3, s_4[, \tau_x, \tau_y]]]])\f$ 
     */
    void setDistCoeffs (cv::Mat distCoeffs);
    
    /**
     * @brief Set homography
     * 
     * This function sets the homography calculated by the extrinsic
     * calibration routine.
     * 
     * @param homography A 3x3 floating point matrix \f$H=\begin{bmatrix}s_x & 0 & z_x \\ 0 & s_y & zy \\ 0 & 0 & z \end{bmatrix}\f$
     */
    void setHomography (cv::Mat homography);
    
    /**
     * @brief Run camera image acquisition
     * 
     * This function runs a camera image acquisition thread.
     *
     * @param imageData A image data reference where to store captured image
     */
     void run (ImageData& imageData) override;
    
    /**
     * @brief Run intrinsic camera calibration
     * 
     * @param inputImage Input image data
     * @param outputImage Output image data
     * @param uiState User interface state
     */
    void runIntrinsicCalibration (ImageData& inputImage, ImageData& outputImage, UserInterfaceState& uiState);
    
    /**
     * @brief Run extrinsic camera calibration
     * 
     * This function runs the extrinsic camera calibration in a thread.
     * 
     * @param inputImage Input image data
     * @param outputImage Output image data
     * @param uiState User interface state
     */
    void runExtrinsicCalibration (ImageData& inputImage, ImageData& outputImage, UserInterfaceState& uiState);
    
    /**
     * @brief Run image position adjustment in frame
     * 
     * This function runs the image position adjustment in a
     * frame.
     * 
     * @param inputImage Input image data
     * @param outputImage Output image data
     * @param uiState User interface state
     */
    void runImagePositionAdjustment (ImageData& inputImage, ImageData& outputData, UserInterfaceState& uiState);
    
    /**
     * @brief Run chess board show
     * 
     * This function runs a chess board showing thread.
     * 
     * @param inputImage Input image data
     * @param outputImage Output image data
     */
    void runChessBoardShow (ImageData& inputImage, ImageData& outputImage);
          
private:
    cv::Mat capturedImage; //!< Captured image
    CameraConfig camConfig; //!< Camera configuration data
    CameraCalibrationConfig camCalibConfig; //!< Calibration configuration data
};

/**
 * @brief Calculate camera exposure for a given exposure step
 * 
 * This function calculates the camera exposure for a given exposure step.
 * A step \f$i\f$ is converted to \f$2^i\f$.
 * 
 * @param exposureStep
 * @return Calculated camera exposure
 */
double calcExposure(int exposureStep);

/**
 * @brief A function calibrate intrinsic camera parameters
 * 
 * This function calibrates intrinsic camera parameters by searching for
 * chessboard pattern. This parameters are stored in a matrix \f$A\f$ and
 * the distortion coefficients vector \f$V\f$.
 * 
 * @param image Image captured by the camera
 * @param cameraMatrix A 3x3 matrix \f$A=\begin{bmatrix}f_x & 0 & c_x \\ 0 & f_y & c_y \\ 0 & 0 & 1 \end{bmatrix}\f$
 * @param distCoeffs Distortion coefficients vector \f$V=(k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6 [, s_1, s_2, s_3, s_4[, \tau_x, \tau_y]]]])\f$
 * @param imagePoints Detected calibration pattern corners
 * @param patternSize Calibration pattern dimensions
 * @param patternMm Calibration pattern size in mm
 */
bool calibrateIntrinsics (cv::Mat& image, cv::Mat& cameraMatrix, cv::Mat& distCoeffs, std::vector<std::vector<cv::Point2f> > imagePoints, cv::Size patternSize, double patternMm);

/**
 * @brief A function calibrate extrinsic camera parameters
 * 
 * This function calibrates extrinsic camera parameters by searching for a chessboard pattern
 * 
 * @param image Image captured by the camera
 * @param homography Perspective transform homography matrix
 * @param patternSize Calibration pattern dimensions
 * @param patternMm Calibration pattern size in mm
 */
void calibrateExtrinsics (cv::Mat& image, cv::Mat& homography, cv::Size patternSize, double patternMm);

/**
 * @brief A function to calculate how many pixels are in 1 mm.
 * 
 * This function calculates how many pixels are in 1 millimeter.
 * It finds the corners of a captured chessboard image and calculates the
 * average distance between each chessboard field.
 * 
 * @param image Input and output image
 * @param patternSize Calibration pattern dimensions
 * @param patternMm Calibration pattern size in mm
 */
float calcPixelPerMm (cv::Mat image, cv::Size patternSize, float patternMm);

/**
 * @brief A function to draw chessboard on an image.
 * 
 * This function draws a chessboard on an image.
 * 
 * @param image Input and output image
 * @param patternSize Calibration pattern dimensions
 */
void drawChessBoard (cv::Mat& image, cv::Size patternSize);

/**
 * @brief A function to adjust image position in frame.
 * 
 * This function adjusts an image position inside an image frame.
 * 
 * @param image Input image
 * @param adjustedImage Adjusted output image
 * @param key User input key
 * @param homography Perspective transform homography matrix
 */
void adjustImagePosition (cv::Mat image, cv::Mat& adjustedImage, char key, cv::Mat& homography);

//! @} camera_image_acquisitor

#endif // CAMERA_CAPTURE_HPP
