#include "fih/intake.h"
#include <math.h>

intake::intake(pros::MotorGroup &top, pros::MotorGroup &bottom, pros::Optical &colorSensor)
    : topMotors(top), bottomMotors(bottom), topColor(colorSensor)
{
    bottomMotors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    topColor.set_led_pwm(100); // Turn on LED
    topColor.set_integration_time(10);
}

void intake::setSortColor(bool sortingRed)
{
    if (sortingRed)
    {
        sortRed = 1;
    }
    else
    {
        sortRed = 0;
    }
}

void intake::setSortEnabled(bool enablingSort)
{
    if (enablingSort)
    {
        enableSort = 1;
    }
    else
    {
        enableSort = 0;
    }
}

void intake::colorSort()
{
    topMotors.move(20);
    bottomMotors.move(-127);
    pros::delay(385);
    topMotors.move(0);
    bottomMotors.move(0);
}

void intake::colorSortMid()
{
    topMotors.move(127);
    bottomMotors.move(127);
    pros::delay(385);
    topMotors.move(0);
    bottomMotors.move(0);
}

void intake::loading()
{
    if (enableSort)
    {
        if (fabs(220 - topColor.get_hue()) < 30)
        {
            colorSort();
        }
    }
    topMotors.move(127);
    bottomMotors.move(0);
}

void intake::unloading()
{
    topMotors.move(-127);
    bottomMotors.move(-127);
}

void intake::longGoal()
{
    if (enableSort)
    {
        if (fabs(220 - topColor.get_hue()) < 30)
        {
            colorSort();
        }
    }
    topMotors.move(127);
    bottomMotors.move(127);
}

void intake::midGoal()
{
    if (enableSort)
    {
        if (fabs(220 - topColor.get_hue()) < 30)
        {
            colorSortMid();
        }
    }

    topMotors.move(127);
    bottomMotors.move(-127);
}

void intake::stop(){
    topMotors.move(0);
    bottomMotors.move(0);
}
