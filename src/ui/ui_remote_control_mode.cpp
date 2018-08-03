/**
 * @file ui_remote_control_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_remote_control_mode.hpp"
#include "cvui.h"

void UIRemoteControlMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
        cvui::text("RC Mode", 0.6);
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
        
        cvui::text("Vehicle Control", 0.5);
        cvui::beginRow();
            cvui::beginColumn();
                cvui::text("Accelerate");
                cvui::space();
                cvui::text("Decelerate");
                cvui::space();
                cvui::text("Left");
                cvui::space();
                cvui::text("Right");
                cvui::space();
                cvui::text("Brake");
            cvui::endColumn();
            cvui::space();
            cvui::beginColumn();
                cvui::text("[W]");
                cvui::space();
                cvui::text("[S]");
                cvui::space();
                cvui::text("[A]");
                cvui::space();
                cvui::text("[D]");
                cvui::space();
                
                cvui::text("[space]");
            cvui::endColumn();
        cvui::endRow();
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
