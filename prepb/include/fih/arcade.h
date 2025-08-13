#pragma once
#include "pros/motor_group.hpp"

/**
 * @brief Arcade drive.
 *
 * @param controller Reference to the controller used for input.
 * @param leftMotors Reference to the left motor group.
 * @param rightMotors Reference to the right motor group.
 * @param curve higher value means a higher curve.
 */
void arcade(pros::Controller &controller, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double curve);