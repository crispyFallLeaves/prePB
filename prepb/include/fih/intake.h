#pragma once
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.hpp"
#include "pros/optical.hpp"

class intake
{
public:
    pros::MotorGroup &topMotors;
    pros::MotorGroup &bottomMotors;
    pros::Optical &topColor;
    bool sortRed;
    bool enableSort;
    void setSortColor(bool sortingRed);
    void setSortEnabled(bool enablingSort);
    void colorSort();
    void colorSortMid();
    void loading();
    void unloading();
    void longGoal();
    void midGoal();
    void stop();

    intake(pros::MotorGroup &top, pros::MotorGroup &bottom, pros::Optical &colorSensor);
};