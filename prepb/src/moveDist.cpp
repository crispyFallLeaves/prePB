#include "fih/moveDist.h"

void moveDist(double cart, double gearRatio, double wheelDia, pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double distance, moveDistParams params){
    double leftPos = leftMotors.get_position();
}