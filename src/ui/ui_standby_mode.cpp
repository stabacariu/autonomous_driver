/**
 * @file ui_standby_mode.hpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_standby_mode.hpp"
#include "cvui.h"

cv::Mat quitButton (int width, int height);

void UIStandbyMode::draw (cv::Mat& image, char& selected)
{
    cvui::beginColumn(image, 10, 10, -1, -1, 5);
    cvui::text("Main Menu", 0.6);
    cvui::space(5);
    
    if (cvui::button(140, 40, "&Autonomous")) {
        selected = 'A';
    }
    if (cvui::button(140, 40, "&Development")) {
        selected = 'D';
    }
    if (cvui::button(140, 40, "&Remote Control")) {
        selected = 'R';
    }
    if (cvui::button(140, 40, "&Configuration")) {
        selected = 'C';
    }
    if (cvui::button(140, 40, "A&bout")) {
        selected = 'B';
    }
    if (cvui::button(140, 40, "&Quit")) {
        selected = 'Q';
    }
    cvui::endColumn();
}
