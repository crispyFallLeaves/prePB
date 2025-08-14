#pragma once
#include "fih/pidCalc.h"
#include "fih/sgn.h"
#include "fih/angleDistance.h"
#include "fih/movementParams.h"
#include <thread>
#include "pros/llemu.hpp"
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"

void moveDistance(double cart, double gearRatio, double wheelDia, pros::IMU &imu, pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double distance, double timeout, moveDistParams params);