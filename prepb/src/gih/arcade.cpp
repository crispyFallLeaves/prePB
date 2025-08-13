#include "fih/arcade.h"
#include "fih/curveFunction.h"
#include "pros/motor_group.hpp"

void arcade(pros::Controller &controller, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double curve)
{
    int linear = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int angular = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    int linearPower = curveFunction(linear, curve);
    int angularPower = curveFunction(angular, curve);

    leftMotors.move(linearPower + angularPower);
    rightMotors.move(linearPower - angularPower);
}