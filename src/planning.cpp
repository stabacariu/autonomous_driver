/**
 * @file planning.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 25.8.2017
 */

#include "planning.hpp"

void *pathPlanning (void *arg)
{
    while (getModuleState() == MODULE_PLAN_PATH) {
        //@TODO Calculate difference between middle line and lane mid.
        //      Correct driving trajectory by steering
    }
    return NULL;
}
