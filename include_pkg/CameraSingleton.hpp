#ifndef CAMERASINGLETON_HPP
#define CAMERASINGLETON_HPP

#include <iostream>
#include <memory>
#include <thread>

#include <opencv2/videoio.hpp>

/**
 * @brief The CameraSingleton class
 * 
 * @details This class is used to wrap a camera object with a singleton
 */
class CameraSingleton {
    static std::shared_ptr<const CameraSingleton> instance;
    /**
     * @brief Camera capture object
     */
    cv::VideoCapture _cap;

    /**
     * @brief Last image taken
     */
    cv::Mat _img;

    std::thread _t;

    /**
     * @brief Private constructor to prevent object creation.
     * 
     * @details It initializes the camera instance and takes the first image.
     */
    CameraSingleton();

    // read image to _img forever
    // used by constructer in a different thread
    /**
     * @brief Read images continously
     * 
     * @details This function is used to read images from the camera by the constructor.
     */
    void readImgForever();

public:
    /**
     * @brief Get the singleton instance of the CameraSingleton class.
     * 
     * @return std::shared_ptr<const CameraSingleton> CameraSingleton instance
     */
    static std::shared_ptr<const CameraSingleton> getInstance();

    /**
     * @brief Destroy the Camera Singleton object
     * 
     * @details This function releases the camera instance and stops the running image capture thread 
     */
    ~CameraSingleton();

    /**
     * @brief Get the latest image from the camera
     * 
     * @return const cv::Mat& The last image taken
     */
    const cv::Mat& img() const;
    
    CameraSingleton(const CameraSingleton&) = delete;
    CameraSingleton& operator=(const CameraSingleton&) = delete;
    CameraSingleton(CameraSingleton&&) = delete;
    CameraSingleton& operator=(CameraSingleton&&) = delete;
};

#endif // CAMERASINGLETON_HPP
