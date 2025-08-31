#include "fih/dt.h"
#include "fih/headingToCartesian.h"
#include "fih/turnToHeading.h"
#include "pros/imu.h"
#include "pros/rotation.h"
#include "fih/moveDist.h"
#include "fih/tickToInch.h"
#include "fih/centidegreeToInch.h"
#include "fih/cartesianToHeading.h"
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
    double horzOffset = -1.2;
    double currentR;
    double currentL;
    double currentTheta;
    double currentHorz;
    double prevR = rightMotors.get_position();
    double prevL = leftMotors.get_position();
    double prevTheta = inertial.get_heading();
    double prevHorz = centidegreeToInch(horiz.get_position(), wheelDia);
    pros::delay(10);
    while (1)
    {
        currentR = rightMotors.get_position();
        currentL = leftMotors.get_position();
        currentTheta = inertial.get_heading();
        currentHorz = centidegreeToInch(horiz.get_position(), wheelDia);

        double deltaR = currentR - prevR;
        double deltaL = currentL - prevL;
        double deltaTheta = angleDistance(currentTheta, prevTheta);
        double deltaDist = (deltaL + deltaR) / 2;
        double deltaHorz = prevHorz - currentHorz;

        double deltaShift = deltaHorz - (horzOffset * deltaTheta * (M_PI) / 180);

        int accuracy = 10;
        for (int i = 1; i <= accuracy; i++)
        {
            double distSplit = deltaDist / accuracy;
            distSplit = tickToInch(distSplit, cartridge, wheelDia, gearRatio);
            prevTheta += deltaTheta / accuracy;

            x += distSplit * cos(headingToCartesian(prevTheta));
            y += distSplit * sin(headingToCartesian(prevTheta));
        }

        x += deltaShift * cos(headingToCartesian(prevTheta) - (M_PI / 2));
        y += deltaShift * sin(headingToCartesian(prevTheta) - (M_PI / 2));
        theta = inertial.get_heading();

        prevR = currentR;
        prevL = currentL;
        prevTheta = currentTheta;
        prevHorz = currentHorz;

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

void drive::moveToPoint(double targetX, double targetY, double timeout, int front, double curve)
{
    double startTime = pros::millis();
    double deltaX = targetX - x;
    double deltaY = targetY - y;
    double targetAngle = atan2(deltaY, deltaX);
    double targetHeading = cartesianToHeading(targetAngle * 180 / M_PI);
    double inErrorRange = 0;
    bool disableTurning = false;
    curve *= 0.1;

    if (front == 0)
    {
        front = fabs(angleDistance(targetHeading, inertial.get_heading())) > 90 ? -1 : 1;
    }
    if (front == -1)
    {
        targetHeading += 180;
    }

    double angularError = angleDistance(targetHeading, inertial.get_heading());
    double linearError = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

    if (front == -1)
    {
        linearError *= -1;
    }

    while (inErrorRange < 20 && timeout > pros::millis() - startTime)
    {
        double linearPower = linearCalc(linearError, linearError);
        double angularPower = angularCalc(angularError, angularError);

        if (fabs(linearError) < 3)
        {
            disableTurning = true;
        }

        double curve = 1;
        if (curve == 1)
        {
            if ((fabs(angularError) * M_PI / 180) / curve > M_PI / 2)
            {
                linearPower = 0;
            }
            else
            {
                linearPower *= cos(((fabs(angularError) * M_PI / 180) / curve));
            }
        }
        else if (curve == 2)
        {
            if ((fabs(angularError) * M_PI / 180) / curve > M_PI)
            {
                linearPower = 0;
            }
            else
            {
                linearPower *= cos((fabs(angularError)*M_PI/180)/curve-=[[[p;;oo8]]])
            }
        }

        if (disableTurning)
        {
            leftMotors.move(linearPower);
            rightMotors.move(linearPower);
        }
        else
        {
            leftMotors.move(linearPower + angularPower);
            rightMotors.move(linearPower - angularPower);
        }

        pros::delay(5);

        deltaX = targetX - x;
        deltaY = targetY - y;
        targetAngle = atan2(deltaY, deltaX);
        targetHeading = cartesianToHeading(targetAngle * 180 / M_PI);
        linearError = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
        if (front == -1)
        {
            targetHeading += 180;
            linearError *= -1;
        }
        angularError = angleDistance(targetHeading, inertial.get_heading());

        if (fabs(linearError) < 2)
        {
            inErrorRange++;
        }
        else
        {
            inErrorRange = 0;
        }
    }
    leftMotors.move(0);
    rightMotors.move(0);
}