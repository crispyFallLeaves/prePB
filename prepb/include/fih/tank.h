#pragma once
#include "pros/motor_group.hpp"

/**
 * @brief Controls a tank drive using two motor groups and a controller.
 *
 * This function sets the velocity of the left and right motor groups based on the analog
 * stick inputs from the controller. If the curve mode is enabled, custom logic can be added.
 *
 * @param controller Reference to the controller used for input.
 * @param leftMotors Reference to the left motor group.
 * @param rightMotors Reference to the right motor group.
 * @param curve higher value means a higher curve.
 */
void tank(pros::Controller &controller, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double curve);
