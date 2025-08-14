#pragma once

/**
 * @brief Parameters for the turnToHeading function.
 *
 * turnDir: -1 = counterclockwise, 0 = default, 1 = clockwise
 * minSpeed: minimum speed the robot can go
 * maxSpeed: maximum speed the robot can go
 * async: is the movement called asyncronously
 * 
 */
struct turnToHeadingParams {
    int turnDir = 0;
    int minSpeed = 0;
    int maxSpeed = 127;
    bool async = false;
};