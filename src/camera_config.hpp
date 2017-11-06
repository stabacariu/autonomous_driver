/**
 * @file camera_config.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 7.7.2017
 */

#ifndef CAMERA_CONFIG_HPP
#define CAMERA_CONFIG_HPP

#include <iostream>
#include <ctime>
#include <opencv2/opencv.hpp>

class CameraConfig {
    public:
        CameraConfig() : validData(false) {}
        
        enum InputSource {
            INPUT_INVALID,
            INPUT_CAMERA,
            INPUT_IMAGE_LIST
        };
        
        enum CalibPattern {
            CALIB_PATTERN_NONE,
            CALIB_PATTERN_CHESSBOARD,
            CALIB_PATTERN_CIRCLE_GRID,
            CALIB_PATTERN_ASYM_CIRCLE_GRID
        };
        
        void write (cv::FileStorage& fs) const;
        void read (const cv::FileNode& node);
        void validate (void);
        cv::Mat nextImage (void);
        bool readStringList (const std::string& filename, std::vector<std::string>& lst);
        
    public:
        cv::Size boardSize; //!< Number of chessboard squares
        double squareSize; //! Size of a chessboard square in mm
        
        CalibPattern calibPattern; //!< Calibration pattern
        int sampleCnt; //! Number of samplese to use for calibration
        double aspectRatio; //! Aspect ratio of input image
        bool calibZeroTangentDist; //!< Assume zero tangential distortion
        bool calibFixPrincipalPoint; //!< Fix principal point at the center
        bool useFisheye; //!< Use fisheye camera calibration
        int calibFlags; //!< Calibration flags
        
        std::string outputFileName; //!< File name of config file
        
        bool writeFeaturePoints; //!< Write detected feature points
        bool writeExtrinsics; //!< Write extrinsic camera parameters
        
        bool showUndistorted; //!< Show undistorted image after calibration
        bool flipVertical; //1< Flip input image around the horizonal axis
        
        InputSource inputSource; //!< Input source
        std::string input; //!< Input file
        int cameraID; //!< Camera identification
        cv::VideoCapture inputCapture; //!< Camera or video capturing
        std::vector<std::string> imageList; //!< Image list for calibration
        size_t imageListCnt; //!< Image list counter
        int inputDelay; //!< Video input delay
        bool validData; //!< Valid input flag
        
        bool fixK1; //!< Fix K1 distortion coefficient
        bool fixK2; //!< Fix K2 distortion coefficient
        bool fixK3; //!< Fix K3 distortion coefficient
        bool fixK4; //!< Fix K4 distortion coefficient
        bool fixK5; //!< Fix K5 distortion coefficient
        
    private:
        std::string patternToUse; //!< Calibration pattern to use
};

static inline void read (const cv::FileNode& node, CameraConfig& config, const CameraConfig& defaultConfig = CameraConfig())
{
    if (node.empty()) {
        config = defaultConfig;
    }
    else {
        config.read(node);
    }
}

static inline void write (cv::FileStorage& fs, const std::string&, const CameraConfig& config)
{
    config.write(fs);
}

#endif // CAMERA_CONFIG_HPP
