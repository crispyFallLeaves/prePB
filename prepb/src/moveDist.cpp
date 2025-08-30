#include "fih/moveDist.h"
#include "fih/conversions.h"
#include "fih/angleDistance.h"
#include "fih/tickToInch.h"

void moveDistance(std::string cart, double gearRatio, double wheelDia, pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double distance, double timeout, moveDistParams params)
{
    double maxSpeed = params.maxSpeed;
    double minSpeed = params.minSpeed;
    double async = params.async;
    double correctDir = params.correctDir;

    if (params.async)
    {
        moveDistParams taskParams = params;
        taskParams.async = false;

        pros::Task([=, &imu, &leftMotors, &rightMotors]()
                   { moveDistance(cart, gearRatio, wheelDia, imu, leftMotors, rightMotors, distance, timeout, taskParams); });
        return;
    }

    int counter = 0;

    double startTime = pros::millis();

    double leftPosStart = tickToInch(leftMotors.get_position(), cart, gearRatio, wheelDia);
    double rightPosStart = tickToInch(rightMotors.get_position(), cart, gearRatio, wheelDia);
    double avgStart = (leftPosStart + rightPosStart) / 2;

    double desiredPos = avgStart + distance;

    double leftPosCurrent = tickToInch(leftMotors.get_position(), cart, gearRatio, wheelDia);
    double rightPosCurrent = tickToInch(rightMotors.get_position(), cart, gearRatio, wheelDia);
    double currentPos = (leftPosCurrent + rightPosCurrent) / 2;

    double error = desiredPos - currentPos;
    double prevError = error;
    double initialImu = imu.get_heading();
    int inErrorRange = 0;

    while (inErrorRange < 10 && pros::millis() - startTime < timeout)
    {
        double power = linearCalc(error, prevError);
        double turn = 0;
        if (correctDir)
        {
            turn = angleDistance(imu.get_heading(), initialImu) * kPTurn;
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

        counter++;
        leftPosCurrent = tickToInch(leftMotors.get_position(), cart, gearRatio, wheelDia);
        rightPosCurrent = tickToInch(rightMotors.get_position(), cart, gearRatio, wheelDia);
        currentPos = (leftPosCurrent + rightPosCurrent) / 2;
        prevError = error;
        error = desiredPos - currentPos;

        bool print = 0;
        if (print)
        {
            if (counter % 5 == 0)
            {
                pros::lcd::set_text(1, std::to_string(error));
                pros::lcd::set_text(2, std::to_string(leftMotors.get_position()));
                pros::lcd::set_text(3, std::to_string(rightMotors.get_position()));
                pros::lcd::set_text(4, std::to_string(counter));
            }
        }

        if (abs(error) < 1)
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