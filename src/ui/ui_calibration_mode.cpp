/**
 * @file ui_calibration_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_calibration_mode.hpp"
#include "cvui.h"

void UIIntrinsicsCalibrationMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Intr. Calib. Mode", 0.6);
    cvui::space(5);
    if (cvui::button(140, 40, "&Back")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::space(5);
    
    if (cvui::button(140, 40, "&Reset")) {
        selected = 'R';
    }
    if (cvui::button(140, 40, "&Save")) {
        selected = 'S';
    }
    cvui::endColumn();
}

void UIExtrinsicsCalibrationMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Extr. Calib. Mode", 0.6);
    cvui::space(5);
    if (cvui::button(140, 40, "&Back")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::space(5);
    
    if (cvui::button(140, 40, "&Reset")) {
        selected = 'R';
    }
    if (cvui::button(140, 40, "&Save")) {
        selected = 'S';
    }
    cvui::endColumn();
}

void UIImageAdjustmentMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Image Adjust. Mode", 0.6);
    cvui::space(5);
    if (cvui::button(140, 40, "&Back")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::space(5);
    
    if (cvui::button(140, 40, "&Reset")) {
        selected = 'R';
    }
    if (cvui::button(140, 40, "&Save")) {
        selected = 'S';
    }
    cvui::endColumn();
}
