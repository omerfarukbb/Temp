#ifndef MOUSECONTROLLER_HPP
#define MOUSECONTROLLER_HPP

#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <tuple>

#include <opencv2/highgui.hpp>

#if WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif

/**
 * @brief 
 * 
 * @note We cannot control multiple windows because OpenCV does not let us get the active window
 * and *cv::waitKey* applies all windows therefore, only one instance of this class should be 
 * used at once TODO: this problem may be solved by using QT
 */
class MouseController {
    /**
     * @brief Stores the count of 
     */
    static int _count;

    /**
     * @brief Name of the OpenCV window
     */
    const std::string _winname;

    /**
     * @brief Target pitch attitude in radians 
     */
    double _pitch;

    /**
     * @brief Target roll attitude in radians 
     */
    double _roll;

    /**
     * @brief Pitch attitude change rate
     */
    double _pitch_coeff;

    /**
     * @brief Roll attitude change rate
     */
    double _roll_coeff;

    /**
     * @brief Attitude change multiplier (sensitivity)
     */
    int _mult;

    /**
     * @brief The origin point  while holding LMB 
     */
    cv::Point _anchor;

protected:
    /**
     * @brief The change in attitude when the multiplier is changed by x1 (in radians)
     */
    static constexpr double _att_mult_dflt = 0.0001;

    /**
     * @brief Configure attitude rate by changing the multiplier
     * 
     * @param diff The difference value used to adjust the coefficients.
     * @param mult A pointer to the multiplication factor.
     * @param pitch_coeff A pointer to the pitch coefficient.
     * @param roll_coeff A pointer to the roll coefficient.
     */
    static void _change_coeff(int diff, int* mult, double* pitch_coeff,
        double* roll_coeff);

    /**
     * @brief Mouse Callback function
     *
     * @details This function is a callback for mouse events, such as mouse button clicks. 
     * It allows the user to change attitude values (pitch and roll) based on mouse input.
     *
     * @param event The given mouse event (e.g., EVENT_LBUTTONDOWN)
     * @param x The x-coordinate of the mouse cursor
     * @param y The y-coordinate of the mouse cursor
     * @param flags Additional flags associated with the event
     * @param userdata A pointer to user-defined data passed to the callback
     */
    static void MouseController::_mouse_cb(int event, int x, int y, int flags, void* userdata);

    // OpenCV mouse callback userdata
    typedef std::tuple<double&, double&, double&, double&, int&, cv::Point&>
        tup_t;

private:
    // OpenCV mouse callback userdata
    tup_t _tup;

public:
    /**
     * @brief The amount of change in throttle when the corresponding key is pressed.
     *
     * @details The 'thr_coeff' member represents the amount of change that occurs when the
     * corresponding key is pressed.
     */
    const int thr_coeff;

    /**
     * @brief The amount of change in yaw when the corresponding key is pressed.
     *
     * @details The 'yaw_coeff' member represents the amount of change that occurs when the
     * corresponding key is pressed.
     */
    const int yaw_coeff;

    /**
     * @brief Hold SPACE to converge to a stable stance.
     *
     * @details The 'speedup', 'throttle_stable', 'pitch_stable', and 'roll_stable' members
     * are used for achieving a stable stance when the SPACE key is held down.
     */
    const int speedup;

    /**
     * @brief Throttle value for a stable stance.
     *
     * @details The 'throttle_stable' member represents the throttle value when trying to
     * achieve a stable stance.
     */
    const int throttle_stable;

    /**
     * @brief Pitch value for a stable stance.
     *
     * @details The 'pitch_stable' member represents the pitch value when trying to
     * achieve a stable stance.
     */
    const double pitch_stable;

    /**
     * @brief Roll value for a stable stance.
     *
     * @details The 'roll_stable' member represents the roll value when trying to achieve
     * a stable stance.
     */
    const double roll_stable;


private:
    /**
     * @brief Throttle value in the range 0-100
     */
    int _throttle;

    /**
     * @brief Heading value in degrees in the range 0-360
     * 
     * @note North:0, East:90
     */
    int _heading;

public:
    /**
     * @brief Get a single key and adjust throttle, heading, and attitude values accordingly.
     *
     * @details This function waits for a single key input and adjusts the throttle,
     * heading, and attitude based on the pressed key. The followings are used:
     * - 'W' to throttle up
     * - 'S' to throttle down
     * - 'A' to steer left
     * - 'D' to steer right
     * - SPACE to hold the vehicle still
     *
     * @return The pressed key
     */
    char get_keystroke_once();

    /**
     * @brief Print help message
     */
    static void help();

    /**
     * @brief Get the default image with 640x480 dimension and blue color screen
     * 
     * @return cv::Mat The resulting image 
     */
    static cv::Mat get_default_image();

    struct Options {
        /**
         * @brief Roll-pitch sensivity (default 10)
         */
        int multiplier = 10;

        /**
         * @brief The amount of change in throttle for each key press
         */
        int thr_coeff = 5;
        
        /**
         * @brief The amount of change in heading for each key press
         */
        int yaw_coeff = 10;

        /**
         * @brief The amount of increase while SPACE is pressed
         */
        int speedup = 25;

        /**
         * @brief Throttle value for a stable stance (0-100)
         */
        int throttle_stable = 50;

        /**
         * @brief Pitch value for a stable stance (in radians)
         */
        double pitch_stable = 0;

        /**
         * @brief Roll value for a stable stance (in radians)
         */
        double roll_stable = 0;
        // https://stackoverflow.com/q/53408962/12447766
        
        /**
         * @brief Construct a new Options object
         */
        Options() { }

        /**
         * @brief Check whether the parameters in Options struct is valid
         * 
         * @return true if all the parameters are valid
         *         otherwise false 
         */
        bool check() const;
    };

    /**
     * @brief Construct a MouseController object.
     *
     * This constructor initializes a MouseController object with the given parameters.
     * It creates a named window for displaying an image and sets up mouse callbacks.
     *
     * @param winname The name of the window to display.
     * @param img The initial image to be shown.
     * @param opt The options for configuring the MouseController object.
     * 
     * @note Please do not use this class with another OpenCV window open. You must call 
     * get_keystroke_once in a loop
     */
    MouseController(std::string winname, cv::Mat img = cv::Mat(),
        const Options opt = Options());

    /**
     * @brief Display the provided image
     * 
     * @return true if the img object is not empty,
     *         otherwise false
     */
    bool set_image(const cv::Mat& img);

    /**
     * @brief Get the value of '_mult' object, representing attitude change multiplier (sensitivity)
     * 
     * @return int 
     */
    int get_multiplier() const;

    /**
     * @brief Get the  value of '_pitch' object, representing target pitch attitude in radians
     * 
     * @return double 
     */
    double get_pitch() const;

    /**
     * @brief Get the  value of '_roll' object, representing target roll attitude in radians
     * 
     * @return double 
     */
    double get_roll() const;

    /**
     * @brief Get the  value of '_throttle' object
     * 
     * @return int
     */
    int get_throttle() const;

    /**
     * @brief Get the  value of '_heading' object 
     * 
     * @return int
     */
    int get_heading() const;
};

#endif // MOUSECONTROLLER_HPP
