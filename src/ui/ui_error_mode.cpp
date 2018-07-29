/**
 * @file ui_error_mode.cpp
 * @author Sergiu-Petru Tabacariu
 * @date 1.5.2018
 */

#include "ui_error_mode.hpp"
#include "cvui.h"

void UIErrorMode::draw (cv::Mat& image, char& selected)
{
    cvui::text(image, image.cols/2, image.rows/2, message);
}
