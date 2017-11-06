/**
 * @file camera_config.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 7.7.2017
 */

#include "camera_config.hpp"

using namespace std;
using namespace cv;

void CameraConfig::write (FileStorage& fs) const
{
    fs << "{"
    << "board_size_width" << boardSize.width
    << "board_size_height" << boardSize.height
    << "square_size" << squareSize
    
    << "calibration_pattern" << patternToUse
    << "calibration_nr_of_samples" << sampleCnt
    << "calibration_fix_aspect_ratio" << aspectRatio
    << "calibration_assume_zero_tangential_distorion" << calibZeroTangentDist
    << "calibration_fix_principal_point_at_the_center" << calibFixPrincipalPoint
    << "calibration_use_fisheye" << useFisheye

    << "write_detected_feature_points" << writeFeaturePoints
    << "write_extrinsic_parameters" << writeExtrinsics
    << "write_output_file_name" << outputFileName
    
    << "show_undistorted_image" << showUndistorted
    << "input_flip_around_horizontal_axis" << flipVertical
    
    << "input" << input
    << "input_delay" << inputDelay
    << "}";
}

void CameraConfig::read (const FileNode& node)
{
    node["board_size_width"] >> boardSize.width;
    node["board_size_height"] >> boardSize.height;
    node["square_size"] >> squareSize;
    
    node["calibration_pattern"] >> patternToUse;
    node["calibration_nr_of_samples"] >> sampleCnt;
    node["calibration_fix_aspect_ratio"] >> aspectRatio;
    node["calibration_assume_zero_tangential_distorion"] >> calibZeroTangentDist;
    node["calibration_fix_principal_point_at_the_center"] >> calibFixPrincipalPoint;
    node["calibration_use_fisheye"] >> useFisheye;

    node["write_detected_feature_points"] >> writeFeaturePoints;
    node["write_extrinsic_parameters"] >> writeExtrinsics;
    node["write_output_file_name"] >> outputFileName;
    
    node["show_undistorted_image"] >> showUndistorted;
    node["input_flip_around_horizontal_axis"] >> flipVertical;
    
    node["input"] >> input;
    node["input_delay"] >> inputDelay;
    
    node["fix_k1"] >> fixK1;
    node["fix_k2"] >> fixK2;
    node["fix_k3"] >> fixK3;
    node["fix_k4"] >> fixK4;
    node["fix_k5"] >> fixK5;
    
    validate();
}

void CameraConfig::validate (void)
{
    validData = true;
    
    // Check pattern config
    if ((boardSize.width <= 0) || (boardSize.height <= 0)) {
        cerr << "ERROR: Invalid board size!" << endl;
        validData = false;
    }
    if (squareSize <= 10e-6) {
        cerr << "ERROR: Invalid square size!" << endl;
        validData = false;
    }
    if (sampleCnt <= 0) {
        cerr << "ERROR: Invalid number of samples!" << endl;
        validData = false;
    }
    // Check input config
    if (input.empty()) {
        inputSource = INPUT_INVALID;
    }
    else {
        if ((input[0] >= '0') && (input[0] <= '9')) {
            stringstream inputStream(input);
            inputStream >> cameraID;
            inputSource = INPUT_CAMERA;
        }
        else {
            if (readStringList(input, imageList)) {
                inputSource = INPUT_IMAGE_LIST;
                if (sampleCnt < (int) imageList.size()) {
                    sampleCnt = (int) imageList.size();
                }
            }
        }
        
        if (inputSource == INPUT_CAMERA) {
            inputCapture.open(cameraID);
        }
        if ((inputSource != INPUT_IMAGE_LIST) && (!inputCapture.isOpened())) {
            inputSource = INPUT_INVALID;
        }
    }
    if (inputSource == INPUT_INVALID) {
        validData = false;
    }
    
    // Set calibration pattern
    calibFlags = 0;
    if (calibFixPrincipalPoint) {
        calibFlags |= CALIB_FIX_PRINCIPAL_POINT;
    }
    if (calibZeroTangentDist) {
        calibFlags |= CALIB_ZERO_TANGENT_DIST;
    }
    if (aspectRatio) {
        calibFlags |= CALIB_FIX_ASPECT_RATIO;
    }
    if (fixK1) {
        calibFlags |= CALIB_FIX_K1;
    }
    if (fixK2) {
        calibFlags |= CALIB_FIX_K2;
    }
    if (fixK3) {
        calibFlags |= CALIB_FIX_K3;
    }
    if (fixK4) {
        calibFlags |= CALIB_FIX_K4;
    }
    if (fixK5) {
        calibFlags |= CALIB_FIX_K5;
    }
    
    // Set fisheye flags
    if (useFisheye) {
        calibFlags = fisheye::CALIB_FIX_SKEW | fisheye::CALIB_RECOMPUTE_EXTRINSIC;
        if (fixK1) {
            calibFlags |= fisheye::CALIB_FIX_K1;
        }
        if (fixK2) {
            calibFlags |= fisheye::CALIB_FIX_K2;
        }
        if (fixK3) {
            calibFlags |= fisheye::CALIB_FIX_K3;
        }
        if (fixK4) {
            calibFlags |= fisheye::CALIB_FIX_K4;
        }
    }
    
    // Check calibration pattern
    calibPattern = CALIB_PATTERN_NONE;
    if (!patternToUse.compare("CALIB_PATTERN_CHESSBOARD")) {
        calibPattern = CALIB_PATTERN_CHESSBOARD;
    }
    if (!patternToUse.compare("CALIB_PATTERN_CIRCLE_GRID")) {
        calibPattern = CALIB_PATTERN_CIRCLE_GRID;
    }
    if (!patternToUse.compare("CALIB_PATTERN_ASYM_CIRCLE_GRID")) {
        calibPattern = CALIB_PATTERN_ASYM_CIRCLE_GRID;
    }
    if (!patternToUse.compare("CALIB_PATTERN_NONE")) {
        cerr << "ERROR: Calibration pattern invalid!" << endl;
        validData = false;
    }
    
    // Initialize image list counter
    imageListCnt = 0;
}

Mat CameraConfig::nextImage (void)
{
    Mat image;
    if (inputCapture.isOpened()) {
        inputCapture >> image;
    }
    else if (imageListCnt < imageList.size()) {
        image = imread(imageList[imageListCnt]);
        imageListCnt++;
    }
    
    return image;
}

bool CameraConfig::readStringList (const string& filename, vector<string>& lst)
{
    lst.clear();
    FileStorage fs(filename, FileStorage::READ);
    if (!fs.isOpened()) {
        return false;
    }
    
    FileNode fn = fs.getFirstTopLevelNode();
    if (fn.type() != FileNode::SEQ) {
        return false;
    }
    
    FileNodeIterator i = fn.begin();
    while (i != fn.end()) {
        lst.push_back((string)* i);
        i++;
    }
    
    return true;
}


void saveCameraConfig (CameraConfig& config, Size& imageSize, Mat& cameraMatrix,
                        Mat& distCoeffs, const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                        const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
                        double totalAvgErr)
{
    FileStorage fs(config.outputFileName, FileStorage::WRITE);
    // Save time stamp
    time_t tm;
    time(&tm);
    struct tm *tLoc = localtime(&tm);
    char buf[1024];
    strftime(buf, sizeof(buf), "%c", tLoc);
    fs << "calibration_time" << buf;
    
    // Save image data
    if ((!rvecs.empty()) || (!reprojErrs.empty())) {
        fs << "calibration_nr_of_samples" << (int) max(rvecs.size(), reprojErrs.size());
    }
    fs << "image_width" << imageSize.width;
    fs << "image_height" << imageSize.height;
    fs << "board_width" << config.boardSize.width;
    fs << "board_height" << config.boardSize.height;
    fs << "square_size" << config.squareSize;
    
    // Save calibration data
    if (config.calibFlags & CALIB_FIX_ASPECT_RATIO) {
        fs << "calibration_fix_aspect_ratio" << config.aspectRatio;
    }
    /*
    if (config.calibFlags) {
        stringstream flagStringStream;
        if (config.useFisheye) {
            flagStringStream << "flags:"
            << (config.calibFlags)
            //! @todo Wirte comment with all flags
    */
    
    fs << "calibration_flags" << config.calibFlags;
    fs << "calibration_use_fisheye" << config.useFisheye;
    fs << "cameraMatrix" << cameraMatrix;
    fs << "distortion_coefficients" << distCoeffs;
    fs << "avg_projection_error" << totalAvgErr;
    
    if (config.writeExtrinsics && (!reprojErrs.empty())) {
        fs << "per_view_reprojection_errors" << Mat(reprojErrs);
    }
    
    if (config.writeFeaturePoints && (!imagePoints.empty())) {
        Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
        for (size_t i = 0; i < imagePoints.size(); i++) {
            Mat r = imagePtMat.row(int(i)).reshape(2, imagePtMat.cols);
            Mat imgpti(imagePoints[i]);
            imgpti.copyTo(r);
        }
        fs << "image_points" << imagePtMat;
    }
}

static double computeReprojectionErrors ( const vector<vector<Point3f> >& objectPoints,
                                        const vector<vector<Point2f> >& imagePoints,
                                        const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                                        const Mat& cameraMatrix , const Mat& distCoeffs,
                                        vector<float>& perViewErrors, bool fisheye)
{
    vector<Point2f> imagePoints2;
    size_t totalPoints = 0;
    double totalErr = 0, err;
    perViewErrors.resize(objectPoints.size());
    
    for (size_t i = 0; i < objectPoints.size(); i++) {
        if (fisheye) {
            fisheye::projectPoints(objectPoints[i], imagePoints2, rvecs[i], tvecs[i], cameraMatrix,
                                   distCoeffs);
        }
        else {
            projectPoints(objectPoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2);
        }
        err = norm(imagePoints[i], imagePoints2, NORM_L2);
        
        size_t n = objectPoints[i].size();
        perViewErrors[i] = (float) std::sqrt(err*err/n);
        totalErr        += err*err;
        totalPoints     += n;
    }
    
    return sqrt(totalErr/totalPoints);
}
