/**
 * @file traffic_sign_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "traffic_sign_detection.hpp"

using namespace std;
using namespace cv;

Point getSignMid (Point tl, Point br)
{
    return Point(tl.x + (br.x - tl.x)/2, tl.y + (br.y - tl.y)/2);
}

void *trafficSignDetection (void *arg)
{
    cout << "THREAD: Traffic sign detection started." << endl;
    CascadeClassifier stopSignCascade;
    if (!stopSignCascade.load("../input/stopsign_classifier.xml")) {
        cerr << "ERROR: Couldn't load classifier data!" << endl;
    }
    
    //~ Mat prevImage;
    //~ getInputImageData(prevImage);
    
    while ((getModuleState() & MODULE_DETECT_TRAFFIC_SIGNS) == MODULE_DETECT_TRAFFIC_SIGNS) {
        Mat inputImage, outputImage, homography;
        getInputImageData(inputImage);
        getOutputImageData(outputImage);
        
        //~ bool procIm = false;
        
        //~ if ((!inputImage.empty()) && (!prevImage.empty())) {
            //~ cv::Mat grayImage, grayPrevImage;
            //~ cvtColor(inputImage, grayImage, CV_BGR2GRAY);
            //~ cvtColor(prevImage, grayPrevImage, CV_BGR2GRAY);
            //~ 
            //~ if (!compareImage(grayImage, grayPrevImage)) {
                //~ procIm = true;
            //~ }
        //~ }
        
        vector<Rect> stopSigns;
        //~ if (procIm && !inputImage.empty()) {
        if (!inputImage.empty()) {
            Mat grayImage, homography;
            cvtColor(inputImage, grayImage, CV_BGR2GRAY);
            getExtr(homography);

            stopSignCascade.detectMultiScale(grayImage, stopSigns, 1.5, 3, 0 | CASCADE_SCALE_IMAGE, Size(20, 20));

            if ((stopSigns.size() > 0) && !outputImage.empty() && !homography.empty()) {
                for (size_t i = 0; i < stopSigns.size(); i++) {
                    rectangle(outputImage, stopSigns[i], Scalar(0, 255, 0), 1);
                    //! @todo Convert sign mid to perspective to get correct distance.
                    vector<Point> signMid;
                    signMid.push_back(getSignMid(stopSigns[i].tl(), stopSigns[i].br()));
                    //~ perspectiveTransform(signMid, signMid, homography);
                    cout << "Traffic sign detection: Stop sign detected at " << signMid[0] << " approx " << getPxPerMm()*signMid[0].y << endl;
                }
            }
            //~ setOutputImageData(outputImage);
        }
    }

    cout << "THREAD: Traffic sign detection ended." << endl;
    return NULL;
}
