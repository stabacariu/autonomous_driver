/**
 * @file traffic_sign_detection.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 30.6.2017
 */

#include "traffic_sign_detection.hpp"

using namespace std;
using namespace cv;

/**
 * @brief Thread for traffic sign detection.
 */

void *trafficSignDetection (void *arg)
{
    cout << "THREAD: Traffic sign detection started." << endl;
    // TODO: Write code
    //~ while ((getModuleState() & MODULE_DETECT_TRAFFIC_SIGNS) == MODULE_DETECT_TRAFFIC_SIGNS) {
    //~ }
    
    cout << "THREAD: Traffic sign detection ended." << endl;
    return NULL;
}
