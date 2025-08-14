#pragma once
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"
#include "fih/movementParams.h"
/**
 * @brief Turns the robot to a specific heading.
 *
 * @param imu Reference to the IMU used for heading detection.
 * @param leftMotors Reference to the left motor group.
 * @param rightMotors Reference to the right motor group.
 * @param targetHeading The desired heading in degrees. */
void turnToHeading(pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double targetHeading, double timeout, turnToHeadingParams params = {});
