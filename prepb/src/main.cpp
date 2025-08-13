#include "main.h"
#include <string>
#include "pros/optical.hpp"
#include "pros/motors.h"
#include "pros/motor_group.hpp"
#include "fih/tank.h"
#include "fih/arcade.h"
#include "fih/turnToHeading.h"
#include "fih/pidCalc.h"
#include <string>
#include <vector>

// PORTS ///////////////////////////////
pros::MotorGroup leftMotors({-6, 4, -18}, pros::v5::MotorGears::blue);
pros::MotorGroup rightMotors({1, -2, 17}, pros::v5::MotorGears::blue);

pros::IMU imu(20);
pros::Rotation horz(-19);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

int auton = 0;
std::vector<std::string> v = {"auton1", "auton2", "auton3"};

void on_center_button()
{
	auton++;
	auton %= v.size();
}

void telemetry()
{
	pros::Task([=]
			   {
		while (1)
		{
			pros::lcd::set_text(1, "IMU Heading:" + std::to_string(imu.get_heading()));
			pros::lcd::set_text(2, "AUTON:" + v.at(auton));
			pros::delay(50); 
		} });
	pros::delay(100);
	return;
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	setkPTurn(0.9);
	setkDTurn(2);
	setFFTurn(6);
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);
	imu.reset();
	while (imu.is_calibrating())
	{
		pros::lcd::print(1, "Calibrating IMU...");
		pros::delay(20);
	}
	pros::delay(100);
	// telemetry();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	turnToHeading(imu, leftMotors, rightMotors, 180, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 45, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 270, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 30, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 0, 5000, false);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol()
{
	turnToHeading(imu, leftMotors, rightMotors, 270, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 180, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 45, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 270, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 30, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 0, 5000, false);
	pros::delay(1000);
	turnToHeading(imu, leftMotors, rightMotors, 0, 5000, false);
	telemetry();
	bool isArcade = true;
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	while (true)
	{

		if (isArcade)
		{
			arcade(master, leftMotors, rightMotors, 1);
		}
		else
		{
			tank(master, leftMotors, rightMotors, 1);
		}

		pros::delay(20); // Run for 20 ms then update
	}
}