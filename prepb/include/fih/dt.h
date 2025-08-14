#pragma once
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"
#include "fih/movementParams.h"
class drive
{
public:
    pros::MotorGroup &leftMotors;
    pros::MotorGroup &rightMotors;
    pros::IMU &inertial;
    pros::Rotation &horiz;
    double x = 0;
    double y = 0;
    double theta = 0;
    void setPose(double x, double y, double theta);
    void odom();
    std::vector<std::string> getPosition();
    void calibrate();
    void turnToAngle(double angle, double timeout, turnToHeadingParams params = {});
    drive(pros::MotorGroup &l, pros::MotorGroup &r, pros::IMU &i, pros::Rotation &s);
};