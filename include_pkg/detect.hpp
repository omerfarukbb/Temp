#ifndef DETECT_HPP
#define DETECT_HPP

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <stack>
#include <vector>

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>


// namespace {
// /**
//  * @brief Struct to represent a group of pixels.
//  *
//  * @details This struct holds information about a group of pixels, including
//  * the sum of their x and y coordinates and the count of pixels.
//  */
// struct Group {
//     /**
//      * @brief Sum of X-coordinates of pixels
//      */
//     int totX = 0;
//  
//     /**
//      * @brief Sum of Y-coordinates of pixels
//      */
//     int totY = 0;
//    
//     /**
//      * @brief Count of pixels
//      */
//     int cnt = 0;
//
//     /**
//      * @brief Construct a new Group object
//      * 
//      * @param _totX Sum of X-coordinates of pixels
//      * @param _totY Sum of Y-coordinates of pixels
//      * @param _cnt Count of pixels
//      */
//     Group(int _totX, int _totY, int _cnt)
//         : totX(_totX)
//         , totY(_totY)
//         , cnt(_cnt)
//     {
//     }
// };
// /**
//  * @brief Depth First Search algorithm for circle detection.
//  *
//  * @details This function uses DFS to detect connected components representing circles
//  * in the given image.
//  *
//  * @param image Grayscale image
//  * @param x X-coordinate of the pixel
//  * @param y Y-coordinate of the pixel
//  * @param s Stack for DFS
//  * @param belongsto Vector to show which group each pixel belongs to
//  * @param groups Vector of groups
//  * @param largestGroupIndex Index of the largest detected group
//  */
// void myCircleDetector_dfs(const cv::Mat& image, int x, int y,
//     std::vector<std::pair<int, int>>& s,
//     std::vector<int>& belongsto,
//     std::vector<Group>& groups, int& largestGroupIndex);
//
// void myCircleDetector(const cv::Mat& image, std::vector<cv::Vec3f>& output);
// }

/**
 * @brief Finds the mask that contains the acceptable colors.
 * 
 * @details The color range is formed in HSV color space.
 *  In OpenCV, hue is between [0, 180), saturation & value are between [0, 255]
 * 
 * @param image RGB image that the accepted color mask will be found.
 * @param color Desired RGB color. HSV convertion is done inside the function.
 * @param hue_range Hue range
 * @param saturation_range Saturation range
 * @param value_range Value range 
*/
cv::Mat color_mask(const cv::Mat& image, cv::Scalar color, int hue_range,
    int saturation_range, int value_range);

/**
 * @brief Read integers from specified file
 * 
 * @details This function takes parameters from the given filename. The format of the file should be 
 * in the form of red green blue hue_range saturation_range value_range
 * 
 * @param filename The input filename
 * @return std::tuple<cv::Scalar, int, int, int> (B,G,R), (H), (S), (V)
 */
std::tuple<cv::Scalar, int, int, int> read_params(std::string filename);

/**
 * @brief Finds the biggest group of specified color
 * 
 * @details This function detects the biggest group of a specified color in the input image. 
 * The color to be detected is determined by the parameters read from a file.
 * 
 * @param image The input image
 * @param hue_image The output hue image where the detected color is masked
 * @param path The path to the file containing the color detection parameters
 * @return A pair containing the center and radius of the detected group
 */
std::pair<cv::Point, int> detect_color(const cv::Mat& image,
    cv::Mat& hue_image = const_cast<cv::Mat&>(static_cast<const cv::Mat&>(cv::Mat())),
    std::string path = std::string());

/**
 * @brief Detects circles in the given image.
 * 
 * @details This function detects circles in the input image using the Hough Circle detection algorithm.
 * 
 * @param img The input image
 * @param minR The minimum radius of the circles to be detected
 * @param maxR The maximum radius of the circles to be detected
 * @param param1 The first parameter of the Hough Circle algorithm
 * @param param2 The second parameter of the Hough Circle algorithm
 * @return A pair containing the center point and radius of the circle (if any)
 */
std::pair<cv::Point, int> detect_circle(const cv::Mat& img, int minR = 0,
    int maxR = 0, int param1 = 100,
    int param2 = 100);

#endif // DETECT_HPP
