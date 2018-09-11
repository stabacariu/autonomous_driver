/**
 * @file ui_autonomous_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_autonomous_mode.hpp"
#include "cvui.h"

void UIAutonomousMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Auto. Mode", 0.6);
    cvui::space(5);
    if (cvui::button(140, 40, "&Back")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::space(5);
    
    cvui::text("Telemetry", 0.5);
    cvui::printf("Steering: %0.2f rad", vehicle.getSteering());
    cvui::printf("Acceleration: %0.2f %", vehicle.getAcceleration());
    cvui::space(5);
    
    cvui::text("Detection", 0.5);
    cvui::text("Lane");
    cv::Vec4i leftLine, rightLine;
    leftLine = lane.getLeftLine();
    cvui::printf("L: [%d, %d], [%d, %d]", leftLine[0], leftLine[1], leftLine[2], leftLine[3]);
    rightLine = lane.getRightLine();
    cvui::printf("R: [%d, %d], [%d, %d]", rightLine[0], rightLine[1], rightLine[2], rightLine[3]);
    cvui::space(3);
    
    double oD = obstacle.getDistance();
    if (oD > (-1)) {
        cvui::printf("Obstacle: %0.2f cm", oD);
    }
    else {
        cvui::text("Obstacle: No obstacle");
    }
    cvui::space(3);
    
    if (trafficSign.getDistance() > (-1)) {
        cv::Point stopSignCenter(getSignCenter(trafficSign.getRoi()));
        cvui::printf("Traffic Sign: [%d, %d]", stopSignCenter.x, stopSignCenter.y);
    }
    else {
        cvui::text("Traffic Sign: No traffic sign");
    }
    
    cvui::endColumn();
}
