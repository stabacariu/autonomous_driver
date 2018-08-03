/**
 * @file ui_configuration_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_configuration_mode.hpp"
#include "cvui.h"

void UIConfigurationMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Config. Mode", 0.6);
    cvui::space(5);
    if (cvui::button(140, 40, "&Back")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::space(5);
        
    if (cvui::button(140, 40, "&Intrinsics")) {
        selected = 'I';
    }
    if (cvui::button(140, 40, "&Extrinsics")) {
        selected = 'E';
    }
    cvui::endColumn();
}
