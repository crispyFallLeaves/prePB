#include "fih/turnToHeading.h"
#include "fih/pidCalc.h"
#include "fih/sgn.h"
#include "fih/angleDistance.h"
#include <thread>

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

    // exit conditions
    while (error > 1.2 && (pros::millis() - timeStarted) < timeout)
    {
        error = angleDistance(imu.get_heading(), targetHeading);
        double power = angularCalc(error, prevError);
        leftMotors.move(power);
        rightMotors.move(-power);

        prevError = error;
        pros::delay(10);
    }
    leftMotors.move(0);
    rightMotors.move(0);
    return;
}