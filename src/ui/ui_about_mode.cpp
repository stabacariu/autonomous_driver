/**
 * @file ui_about_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_about_mode.hpp"
#include "cvui.h"

void UIAboutMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("About", 0.6);
    cvui::space(5);
    
    if (cvui::button(140, 40, "&Back")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::endColumn();
    
    cvui::beginColumn(image, 200, 30, -1, -1, 3);
    cvui::text("Master Thesis Project");
    cvui::text("Autonomous Driver", 0.6);
    cvui::text("An Autonomous Driving Development Platform");
    cvui::text("by Sergiu-Petru Tabacariu");
    cvui::text("<sergiu-petru.tabacariu@stud.fh-campuswien.ac.at>");
    cvui::text("Date 1.5.2018");
    cvui::text("Version 1.0.0");
    cvui::space(5);
    cvui::text("Get latest version at:");
    cvui::text("https://github.com/stabacariu/autonomous_driver");
    cvui::endColumn();
}
