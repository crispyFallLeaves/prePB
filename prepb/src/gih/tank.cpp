#include "fih/tank.h"
#include "fih/curveFunction.h";
#include "pros/motor_group.hpp"
#include <cmath>




void tank(pros::Controller &controller, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double curve)
{
    int leftStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    leftMotors.move(curveFunction(leftStick, curve));
    rightMotors.move(curveFunction(rightStick, curve));
}