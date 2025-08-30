#include "fih/dt.h"
#include "fih/headingToCartesian.h"
#include "fih/turnToHeading.h"
#include "pros/imu.h"
#include "pros/rotation.h"
#include "fih/moveDist.h"
#include "fih/tickToInch.h"
#include <vector>
#include <string>
#include <cmath>

drive::drive(pros::MotorGroup &l, pros::MotorGroup &r, pros::IMU &i, pros::Rotation &s, double gearRatio, std::string cart, double wheel)
    : leftMotors(l), rightMotors(r), inertial(i), horiz(s), gearRatio(gearRatio), cartridge(cart), wheelDia(wheel) {}

void drive::setPose(double xstart, double ystart, double thetastart)
{
    x = xstart;
    y = ystart;
    horiz.reset_position();
    inertial.set_heading(thetastart);
}

void drive::odom()
{   
    double horzOffset = -1;
    double currentR;
    double currentL;
    double currentTheta;
    double prevR = rightMotors.get_position();
    double prevL = leftMotors.get_position();
    double prevTheta = inertial.get_heading();
    double prevHorz = horiz.get_position();
    pros::delay(10);
    while (1)
    {
        currentR = rightMotors.get_position();
        currentL = leftMotors.get_position();
        currentTheta = inertial.get_heading();

        double deltaR = currentR - prevR;
        double deltaL = currentL - prevL;
        double deltaTheta = angleDistance(currentTheta, prevTheta);

        double deltaDist = (deltaL + deltaR) / 2;

        int accuracy = 10;
        for (int i = 1; i <= accuracy; i++)
        {
            double distSplit = deltaDist / accuracy;
            distSplit = tickToInch(distSplit, cartridge, wheelDia, gearRatio);
            prevTheta += deltaTheta / accuracy;

            x += distSplit * cos(headingToCartesian(prevTheta));
            y += distSplit * sin(headingToCartesian(prevTheta));
        }
        theta = inertial.get_heading();

        prevR = currentR;
        prevL = currentL;
        prevTheta = currentTheta;

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

void drive::moveDist(double dist, double timeout, moveDistParams params)
{
    moveDistance(this->cartridge, this->gearRatio, this->wheelDia, this->inertial, this->leftMotors, this->rightMotors, dist, timeout, params);
}