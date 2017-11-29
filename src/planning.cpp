/**
 * @file planning.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#include "planning.hpp"

using namespace std;
using namespace cv;

void calculateAcutalPosition (vector<Vec4i> actualLane, Size imageSize)
{
    Vec4i laneMid = getLaneMid(actualLane);
    Vec4i viewMid(imageSize.width/2-1, 0, imageSize.width/2-1, imageSize.height-1);
    int diffX1 = laneMid[0]-viewMid[0]; // If result positive then lane is to much to the right. Car must steer to the right.
    int diffX2 = laneMid[2]-viewMid[2];
    cout << "Difference " << diffX1 << ", " << diffX2 << endl;

    float theta = getTheta(Point(laneMid[0], laneMid[1]), Point(laneMid[2], laneMid[3]));
    float thetaL = getTheta(Point(actualLane[0][0], actualLane[0][1]), Point(actualLane[0][2], actualLane[0][3]));
    float thetaR = getTheta(Point(actualLane[1][0], actualLane[1][1]), Point(actualLane[1][2], actualLane[1][3]));
    
    cout << "Theta " << theta << " Diff L R " << abs(thetaR-thetaL) << endl;
    
    setSteering(theta);
    
    if ((theta < (CV_PI*0.2)) || (theta > (CV_PI*0.80))) {
        setAcceleration(50);
    }
    else if (abs(thetaR-thetaL) > CV_PI/4) {
        setAcceleration(50);
    }
    else {
        if (theta < CV_PI/2*0.9) {
            setDirection(RIGHT);
        }
        else if (theta > CV_PI/2*1.1) {
            setDirection(LEFT);
        }
        else {
            setDirection(STRAIGHT);
        }
        
        // Vehicle is too much to the left
        // Counter steer to the right
        if (diffX2 > 10) {
            setSteering(3*CV_PI/4);
            setAcceleration(59);
        }
        // Vehicle is too much to the right
        // Counter steer to the left
        else if (diffX2 < -10 ){
            setSteering(CV_PI/4);
            setAcceleration(59);
        }
        else {
            if (diffX1 > 10) {
                setAcceleration(59);
            }
            else if (diffX1 < -10) {
                setAcceleration(59);
            }
            else {
                setAcceleration(59);
            }
        }
    }
}

bool compareLanes (vector<Vec4i> lane1, vector<Vec4i>lane2)
{
    if ((lane1.size() != 2) && (lane2.size() != 2)) {
        return false;
    }
    for (size_t j = 0; j < lane1.size(); j++) {
        for (size_t i = 0; i < lane1.size(); i++) {
            if (lane1[j][i] != lane2[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void *pathPlanning (void *arg)
{
    cout << "THREAD: Path planning started." << endl;
    initLaneData();
    
    vector<Vec4i> actualLane;
    
    while ((getModuleState() & MODULE_PLAN_PATH) == MODULE_PLAN_PATH) {
        //! @todo Calculate difference between middle line and lane mid.
        //      Correct driving trajectory by steering
        
        vector<Vec4i> prevLane = actualLane;
        getActualLane(actualLane);

        Mat inputImage;
        getInputImageData(inputImage);
        if ((actualLane.size() == 2) && (!inputImage.empty())) {
            calculateAcutalPosition(actualLane, inputImage.size());
        }
        else {
            setSteering(CV_PI/2);
            setAcceleration(50);
        }
    }

    cout << "THREAD: Path planning ended." << endl;
    return NULL;
}
