/**
 * @file ui_development_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_development_mode.hpp"
#include "cvui.h"

void UIDevelopmentMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Dev. Mode", 0.6);
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
    
    if (obstacle.getDistance() > (-1)) {
        cvui::printf("Obstacle: %0.2f cm", obstacle.getDistance());
    }
    else {
        cvui::text("Obstacle: No obstacle.");
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
    
    // Draw vehicle control buttons
    cvui::beginRow(image, (image.cols - 100), (image.rows - 150), -1, -1, 10);
    if (cvui::button(40, 40, "&W")) {
        selected = 'w';
    }
    cvui::endRow();
    
    cvui::beginRow(image, (image.cols - 150), (image.rows - 100), -1, -1, 10);
    if (cvui::button(40, 40, "&A")) {
        selected = 'a';
    }
    if (cvui::button(40, 40, "&S")) {
        selected = 's';
    }
    if (cvui::button(40, 40, "&D")) {
        selected = 'd';
    }
    cvui::endRow();
    
    cvui::beginRow(image, (image.cols - 150), (image.rows - 50), -1, -1, 10);
    if (cvui::button(140, 40, "& space")) {
        selected = ' ';
    }
    cvui::endRow();
}
