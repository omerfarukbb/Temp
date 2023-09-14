#pragma once

#include <cassert>
#include <include_pkg/detect.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

// namespace {
    
// /**
//  * @brief Show instructions about how to use the program 
//  */
// void help();

// /**
//  * @brief Generate an RGB colormap image.
//  *
//  * @details The size of the returned image is 256x256, where the row and column numbers represent the
//  * intensity of two channels. The intensity of the remaining channel changes with each iteration by 
//  * first increasing, then decreasing. The order of RGB channels changes every (2*256) iterations.
//  *
//  * @param t The current time step
//  * @return The generated colormap image
//  */
// cv::Mat get_color_image(size_t t);
// };