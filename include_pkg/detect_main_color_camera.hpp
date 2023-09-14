#pragma once

#include <cassert>
#include <cstdlib>
#include <include_pkg/detect.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

namespace MouseCallback {

/**
 * @brief Mouse callback function
 * 
 * @param event Mouse event (e.g., cv::EVENT_RBUTTONDOWN)
 * @param x X-coordinate of the clicked position
 * @param y Y-coordinate of the clicked position
 * @param flags Flags 
 * @param userdata Pointer to the image
 */
void mouseCallback(int event, int x, int y, int flags, void* userdata);

};