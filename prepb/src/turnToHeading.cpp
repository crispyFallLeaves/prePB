#include "fih/turnToHeading.h"
#include "fih/pidCalc.h"
#include "fih/sgn.h"
#include "fih/angleDistance.h"
#include <thread>
#include "pros/llemu.hpp"

void turnToHeadingDir(pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double targetHeading, double timeout, turnToHeadingParams params)
{
    int maxSpeed = params.maxSpeed;
    int minSpeed = params.minSpeed;
    int dir = params.turnDir;
    int async = params.async;

    if (async)
    {
        params.async = false;
        pros::Task task([&]()
                        { turnToHeadingDir(imu, leftMotors, rightMotors, targetHeading, timeout, params); });
        return;
    }

    double angleDifference = angleDistance(imu.get_heading(), targetHeading);
    if (dir == 1 && angleDifference > 0)
    {
        angleDifference -= 360;
    }
    if (dir == -1 && angleDifference < 0)
    {
        angleDifference += 360;
    }

    double desiredRotation = imu.get_rotation() + angleDifference;
    double error = imu.get_rotation() - desiredRotation;

    double timeStarted = pros::millis();

    double prevError = error;

    int inErrorRange = 0;
    // exit conditions
    while (inErrorRange < 10 && (pros::millis() - timeStarted) < timeout)
    {
        double power = angularCalc(error, prevError);
        if (abs(power) < minSpeed)
        {
            power = minSpeed * sgn(power);
        }

        if (abs(power) > maxSpeed)
        {
            power = maxSpeed * sgn(power);
        }

        leftMotors.move(-power);
        rightMotors.move(power);

        prevError = error;
        std::string errorText = "Error: " + std::to_string(error);
        pros::lcd::set_text(1, errorText.c_str());
        pros::delay(10);

        double error = imu.get_rotation() - desiredRotation;

        if (abs(error) < 2)
        {
            inErrorRange++;
        }
        else
        {
            inErrorRange = 0;
        }
        pros::delay(10);
    }
    leftMotors.move(0);
    rightMotors.move(0);
    return;
}
void turnToHeading(pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double targetHeading, double timeout, turnToHeadingParams params)
{
    int maxSpeed = params.maxSpeed;
    int minSpeed = params.minSpeed;
    int dir = params.turnDir;
    int async = params.async;

    if (async)
    {
        params.async = false;
        pros::Task task([&]()
                        { turnToHeading(imu, leftMotors, rightMotors, targetHeading, timeout, params); });
        return;
    }

    if (dir != 0)
    {
        turnToHeadingDir(imu, leftMotors, rightMotors, targetHeading, timeout, params);
        return;
    }

    double timeStarted = pros::millis();
    double error = angleDistance(imu.get_heading(), targetHeading);
    double prevError = error;
    int inErrorRange = 0;
    // exit conditions
    while (inErrorRange < 10 && (pros::millis() - timeStarted) < timeout)
    {
        double power = angularCalc(error, prevError);
        if (abs(power) < minSpeed)
        {
            power = minSpeed * sgn(power);
        }

        if (abs(power) > maxSpeed)
        {
            power = maxSpeed * sgn(power);
        }

        leftMotors.move(-power);
        rightMotors.move(power);

        prevError = error;
        std::string errorText = "Error: " + std::to_string(error);
        pros::lcd::set_text(1, errorText.c_str());
        pros::delay(10);

        error = angleDistance(imu.get_heading(), targetHeading);

        if (abs(error) < 3)
        {
            inErrorRange++;
        }
        else
        {
            inErrorRange = 0;
        }
        pros::delay(10);
    }
    leftMotors.move(0);
    rightMotors.move(0);
    return;
}