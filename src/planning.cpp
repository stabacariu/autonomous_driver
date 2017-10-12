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
    
    float theta = getTheta(Point(laneMid[0], laneMid[1]), Point(laneMid[2], laneMid[3]));
    
    if ((theta < (CV_PI*0.05)) && (theta > (CV_PI*0.95))) {
        setAcceleration(0);
    }
    else if (theta == (CV_PI/2)) {
        setAcceleration(60);
    }
    else {
        //~ setSteering((double) theta - (CV_PI/2));
        setSteering(theta);
        
        // Car is too much to the left
        if (diffX2 > 0) {
            setAcceleration(59);
        }
        else if (diffX2 == 0) {
            if (diffX1 > 0) {
                setAcceleration(59);
            }
            else if (diffX1 < 0) {
                setAcceleration(59);
            }
            else {
                setAcceleration(50);
            }
        }
        else {
            setAcceleration(59);
        }
    }
}



void *pathPlanning (void *arg)
{
    cout << "THREAD: Path planning started." << endl;
    
    initLaneData();
    
    while ((getModuleState() & MODULE_PLAN_PATH) == MODULE_PLAN_PATH) {
        //! @todo Calculate difference between middle line and lane mid.
        //      Correct driving trajectory by steering
        vector<Vec4i> actualLane;
        getActualLane(actualLane);
        Mat inputImage;
        getInputImageData(inputImage);
        if ((actualLane.size() == 2) && (!inputImage.empty())) {
            calculateAcutalPosition(actualLane, inputImage.size());
        }
    }
    
    cout << "THREAD: Path planning ended." << endl;
    return NULL;
}
