/**
 * @file traffic_sign_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "traffic_sign_detection.hpp"

using namespace std;
using namespace cv;

void *trafficSignDetection (void *arg)
{
    cout << "THREAD: Traffic sign detection started." << endl;
    CascadeClassifier stopSignCascade;
    if (!stopSignCascade.load("../input/stopsign_classifier.xml")) {
        cerr << "ERROR: Couldn't load classifier data!" << endl;
    }

    //! @todo Write code
    while ((getModuleState() & MODULE_DETECT_TRAFFIC_SIGNS) == MODULE_DETECT_TRAFFIC_SIGNS) {
        Mat image;
        getInputImageData(image);

        vector<Rect> stopSigns;
        if (!image.empty()) {
            Mat grayImage;
            cvtColor(image, grayImage, CV_BGR2GRAY);

            stopSignCascade.detectMultiScale(grayImage, stopSigns, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

            if (stopSigns.size() > 0) {
                for (size_t i = 0; i < stopSigns.size(); i++) {
                    rectangle(image, stopSigns[i], Scalar(0, 255, 0), 1);
                }
            }
            setOutputImageData(image);
        }
    }

    cout << "THREAD: Traffic sign detection ended." << endl;
    return NULL;
}
