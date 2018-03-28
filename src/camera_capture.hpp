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
#include "configuration.hpp"
#include "autonomous_driver.hpp"
#include "image_data.hpp"

//! @addtogroup camera_image_acquisitor
//! @brief A module to caputure a camera image
//! @{

/**
 * @brief A camera image acquisition class
 * 
 * This class describes a camera image acquisitor
 */
class CameraAcquisitor: public ImageAcquisitor {
public:
    CameraAcquisitor();
    CameraAcquisitor(int id);
    
    /**
     * @brief Start camera image acquisition
     * 
     * This function starts a camera image acquisition thread.
     *
     * @return True ist acquisition started, else false.
     */
     bool start(void);
     
     /**
     * @brief Stop camera image acquisition
     * 
     * This function stops a camera image acquisition thread.
     *
     * @return True ist acquisition stopped, else false.
     */
     bool stop(void);
     
    
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
    void setFPS(double fps);
    
    /**
     * @brief Set camera matrix containing the focal length and principal image point
     * 
     * This function sets the camera matrix containing the focal length
     * and principal image point.
     * 
     * @param cameraMatrix A 3x3 floating-point matrix \f$A=\begin{bmatrix}f_x & 0 & c_x \\ 0 & f_y & c_y \\ 0 & 0 & 1 \end{bmatrix}\f$ 
     */
    void setCameraMatrix(cv::Mat cameraMatrix);
    
    /**
     * @brief Set distortion coefficients
     * 
     * This function sets the distortion coefficients calculated by the
     * OpenCV-Function calibrateCamera().
     * 
     * @param distCoeffs Distortion coefficients vector \f$(k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6 [, s_1, s_2, s_3, s_4[, \tau_x, \tau_y]]]])\f$ 
     */
    void setDistCoeffs(cv::Mat distCoeffs);
    
    /**
     * @brief Set homography
     * 
     * This function sets the homography calculated by the extrinsic
     * calibration routine.
     * 
     * @param homography A 3x3 floating point matrix \f$H=\begin{bmatrix}s_x & 0 & z_x \\ 0 & s_y & zy \\ 0 & 0 & z \end{bmatrix}\f$
     */
    void setHomography(cv::Mat homography);
    
    /**
     * @brief Run intrinsic camera calibration
     * 
     * This function runs the intrinsic camera calibration in a thread.
     * 
     * @return True if successfully calibrated returns true, else false.
     */
    bool runIntrinsicCalibration();
    
    /**
     * @brief Run extrinsic camera calibration
     * 
     * This function runs the extrinsic camera calibration in a thread.
     * 
     * @return Tue if successfully calibrated, else false.
     */
    bool runExtrinsicCalibration();
    
private:
    double exposure; //!< Camera exposure value
    double fps; //!< Frames per second caputred by the camera
    cv::Mat cameraMatrix; //! Camera matrix containing the focal length and principal image point
    cv::Mat distCoeffs; //! Distortion coefficients for distortion correction
    
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
     * @brief Calibrate intrinsic camera parameters
     * 
     * This function calibrates the intrinsic camera matrix \f$A\f$ and 
     * the distortion coefficients vector \f$V\f$.
     * 
     * @param numSamples Number of image samples to calibrate. A higher number results in better calibration
     * @param cameraMatrix A 3x3 matrix \f$A=\begin{bmatrix}f_x & 0 & c_x \\ 0 & f_y & c_y \\ 0 & 0 & 1 \end{bmatrix}\f$
     * @param distCoeffs Distortion coefficients vector \f$V=(k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6 [, s_1, s_2, s_3, s_4[, \tau_x, \tau_y]]]])\f$
     * @return True if calibration was successfull, else false.
     */
    bool calibrateIntrinsics(int numSamples, cv::Mat& cameraMatrix, cv::Mat& distCoeffs);
    
    /**
     * @brief Calibrate extrinsic camera parameters
     * 
     * @param image Camera image
     * @param homography Homography to correct perspective
     */
    bool calibrateExtrinsics(cv::Mat image, cv::Mat& homography);
};

/**
 * @brief Thread for capturing a camera image
 * 
 * This function implements a thread that captures an image from a webcam.
 * 
 * @param arg Input arguments
 */
void *cameraCapture (void *arg);

//! @} camera_image_acquisitor

#endif // CAMERA_CAPTURE_HPP
