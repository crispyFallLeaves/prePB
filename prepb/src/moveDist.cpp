#include "fih/moveDist.h"
#include "fih/conversions.h"
#include "fih/angleDistance.h"

void moveDistance(double cart, double gearRatio, double wheelDia, pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double distance, double timeout, moveDistParams params)
{
    double maxSpeed = params.maxSpeed;
    double minSpeed = params.minSpeed;
    double async = params.async;
    double correctDir = params.correctDir;

    if (async)
    {
        params.async = false;
        pros::Task task([&]()
                        { moveDistance(cart, gearRatio, wheelDia, imu, leftMotors, rightMotors, distance, timeout, params); });
        return;
    }

    double startTime = pros::millis();

    double leftPosStart = degToInch(leftMotors.get_position(), cart, gearRatio, wheelDia);
    double rightPosStart = degToInch(rightMotors.get_position(), cart, gearRatio, wheelDia);
    double avgStart = (leftPosStart + rightPosStart) / 2;

    double desiredPos = avgStart + distance;

    double leftPosCurrent = degToInch(leftMotors.get_position(), cart, gearRatio, wheelDia);
    double rightPosCurrent = degToInch(rightMotors.get_position(), cart, gearRatio, wheelDia);
    double currentPos = (leftPosStart + rightPosStart) / 2;

    double error = desiredPos - currentPos;
    double prevError = error;
    double initialImu = imu.get_heading();
    int inErrorRange = 0;

    while (inErrorRange > 5 && pros::millis() - startTime > timeout)
    {
        prevError = error;
        double power = linearCalc(error, prevError);
        double turn;
        if (correctDir)
        {
            turn = angularCalc(angleDistance(imu.get_heading(), initialImu), 0);
        }
        else
        {
            turn = 0;
        }

        if (abs(power) < minSpeed)
        {
            power = minSpeed * sgn(power);
        }

        if (abs(power) > maxSpeed)
        {
            power = maxSpeed * sgn(power);
        }

        leftMotors.move(power - turn);
        rightMotors.move(power + turn);

        pros::delay(10);
        double leftPosCurrent = degToInch(leftMotors.get_position(), cart, gearRatio, wheelDia);
        double rightPosCurrent = degToInch(rightMotors.get_position(), cart, gearRatio, wheelDia);
        double currentPos = (leftPosStart + rightPosStart) / 2;
        error = desiredPos - currentPos;
    }
}