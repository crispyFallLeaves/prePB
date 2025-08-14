#include "fih/dt.h"
#include "fih/turnToHeading.h"
#include "pros/imu.h"
#include "pros/rotation.h"
#include <vector>
#include <string>

drive::drive(pros::MotorGroup &l, pros::MotorGroup &r, pros::IMU &i, pros::Rotation &s)
    : leftMotors(l), rightMotors(r), inertial(i), horiz(s) {}

void drive::setPose(double xstart, double ystart, double thetastart)
{
    x = xstart;
    y = ystart;
    horiz.reset_position();
    inertial.set_heading(thetastart);
}

void drive::odom()
{
    while (1)
    {
        theta = inertial.get_heading();
        pros::delay(10);
    }
}

std::vector<std::string> drive::getPosition()
{
    std::vector<std::string> v;
    v.push_back(std::to_string(x));
    v.push_back(std::to_string(y));
    v.push_back(std::to_string(theta));
    return v;
}

void drive::turnToAngle(double angle, double timeout, turnToHeadingParams params)
{
    turnToHeading(inertial, leftMotors, rightMotors, angle, timeout, params);
}