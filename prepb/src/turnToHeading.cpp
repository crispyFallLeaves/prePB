#include "fih/turnToHeading.h"
#include "fih/pidCalc.h"
#include "fih/sgn.h"
#include "fih/angleDistance.h"
#include <thread>
#include "pros/llemu.hpp"

void turnToHeading(pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double targetHeading, double timeout, bool async)
{
    if (async)
    {
        pros::Task task([&]()
                        { turnToHeading(imu, leftMotors, rightMotors, targetHeading, timeout, false); });
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
        leftMotors.move(-power);
        rightMotors.move(power);
        prevError = error;

        std::string errorText = "Error: " + std::to_string(error);
        pros::lcd::set_text(1, errorText.c_str());
        pros::delay(10);

        error = angleDistance(imu.get_heading(), targetHeading);
        if (error < 2)
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