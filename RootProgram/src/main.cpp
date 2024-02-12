#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	liftMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
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

void offenseAuto() {
	PIDTranslate(-2250,0,70,1500);
	PIDTranslate(0,90);
	spinIntake(127);
	PIDTranslate(1650,0,127,1500);
	PIDTranslate(-900,0,80);
	spinIntake(0);
	PIDTranslate(0,135);
	spinIntake(-127);
	PIDTranslate(700,0);
	PIDTranslate(-900,0);
	PIDTranslate(0,-45,80);
	spinIntake(127);
	PIDTranslate(1800,0,80);
	pros::delay(100);
	spinIntake(-90);
	PIDTranslate(0,90);
	PIDTranslate(600,0);
	PIDTranslate(-600,0);
	PIDTranslate(0,-180,80);
	spinIntake(127);
	PIDTranslate(900,0,127,750);
	pros::delay(200);
	PIDTranslate(0,180);
	PIDTranslate(300,0);
	inverseWing();
	spinIntake(-127);
	spinMotors(127,127,127,127,127,127);
	pros::delay(1000);
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(500);
	spinMotors(127,127,127,127,127,127);
	pros::delay(1000);
	inverseWing();
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(200);
	PIDTranslate(100,0);
	spinMotors(0,0,0,0,0,0);
}

void defenseAuto() {
	PIDTranslate(600,0);
	inverseWing();
	PIDTranslate(100,0);
	PIDTranslate(-600,0);
	inverseWing();
	PIDTranslate(-100,0);
	pros::delay(200);
	PIDTranslate(0,45);
	PIDTranslate(-200,0);
	spinMotors(-60,-60,-60,-60,-60,-60);
	pros::delay(500);
	PIDTranslate(1800,0);
	PIDTranslate(0,45,80);
	PIDTranslate(1350,0);
	PIDTranslate(0,-45,80);
	spinIntake(127);
	PIDTranslate(1400,0,50);
	PIDTranslate(100,0);
	PIDTranslate(-1250,0);
	PIDTranslate(0,-135);
	spinIntake(0);
	PIDTranslate(1600,0);
	PIDTranslate(0,-90, 60);
	PIDTranslate(200,0);
	pros::delay(200);
	PIDTranslate(800,0);
	spinIntake(-127);
	PIDTranslate(0,-55,60);
	PIDTranslate(1750,0,90);
}

void skills() {
	PIDTranslate(-150,0);
	puncherToggle(); 
	pros::delay(35000);
	puncherToggle();
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(300);
	PIDTranslate(2500,0);
	PIDTranslate(0,-45);
	spinIntake(127);
	PIDTranslate(1800,0);
	PIDTranslate(0,90);
	spinIntake(0);
	PIDTranslate(200,0);
	inverseWing();
	spinMotors(127,127,127,127,127,127);
	pros::delay(600);
	PIDTranslate(-2500,0);
	inverseWing();
	spinIntake(-127);
	spinMotors(127,127,127,127,127,127);
	pros::delay(1000);
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(600);
	spinMotors(127,127,127,127,127,127);
	pros::delay(2000);
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(1000);
	spinMotors(127,127,127,127,127,127);
	pros::delay(2000);
	inverseWing();
	spinMotors(127,127,127,127,127,127);
	pros::delay(2000);
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(800);
	PIDTranslate(0,-20);
	spinMotors(127,127,127,127,127,127);
	pros::delay(2000);
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(800);
}

void skillsTwo() {
	puncherToggle(); 
	pros::delay(30000);
	puncherToggle();
	PIDTranslate(0,60);
	PIDTranslate(-100,0);
	spinMotors(-127,-127,-127,0,-127,0);
	pros::delay(1000);
	PIDTranslate(400,0);
	PIDTranslate(0,-45);
	PIDTranslate(2700,0);
	PIDTranslate(0,-45);
	PIDTranslate(5400,0);
	PIDTranslate(0,-180);
	PIDTranslate(-300, 0);
	spinMotors(0,-100,0,-127,-127,-127);
	pros::delay(1500);
	PIDTranslate(500,0);
	spinMotors(-127,-127,-127,-127,-127,-127);
	pros::delay(500);
	PIDTranslate(500,0);
	PIDTranslate(0,90,80);
	PIDTranslate(2700,0);
	inverseLeft();
	PIDTranslate(0,90);
	PIDTranslate(900,0);	
	PIDTranslate(0,50);
	inverseRight();
	PIDTranslate(1900,0, 127, 2000);
	inverseRight();
	PIDTranslate(0,40);
	PIDTranslate(-700,0);
	inverseRight();
	PIDTranslate(1200,0, 127, 1500);
	inverseWing();
	PIDTranslate(-1400,0);
	PIDTranslate(0,-92);
	inverseLeft();
	PIDTranslate(2400,0,127,2000);
	PIDTranslate(0,125);
	inverseRight();
	PIDTranslate(3200,0, 127, 2000);
	inverseLeft();
	PIDTranslate(0,-50);
	PIDTranslate(-2000,0,1500);
	spinMotors(-127, -127, -127, -127, -127, -127);
	pros::delay(300);
	inverseLeft();
	PIDTranslate(2200,0, 127, 1500);
	inverseWing();
	PIDTranslate(-350,0);
	PIDTranslate(0,-95);
	PIDTranslate(4700,0,3000);
	PIDTranslate(0,-90);
	PIDTranslate(-100,0);
	spinMotors(-127,-127,-127,0,-127,0);
	pros::delay(2000);
	PIDTranslate(500,0);
	// spinMotors(-127,-127,-127,-127,-127,-127);
	// pros::delay(1000);
}

void turnTest() {
	execCurveTurn(90, 6, 1, 80);
	puncherToggle();
}

void autonomous() {
	// skillsTwo();
	// defenseAuto();
	offenseAuto();
	//turnTest();
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
float target = 45;
void opcontrol() {
	while (true) { 
		float vertTar = master.get_analog(ANALOG_LEFT_Y);
		float latTar = master.get_analog(ANALOG_RIGHT_X);
		if (fabs(vertTar) < 10) {
			vertTar = 0;
		}
		if (fabs(latTar) < 10) {
			latTar = 0;
		}
		PIDMotorSet(vertTar, latTar);
		std::cout << "wow";	//TODO test cout to see if I can check variables with console rather than brain

		if (master.get_digital_new_press(DIGITAL_L1)) {
			puncherToggle();
		}
		int32_t shouldSpin = master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2);
		setIntake(shouldSpin);
		int32_t shouldSpinLift = master.get_digital(DIGITAL_UP) - master.get_digital(DIGITAL_DOWN);
		setLift(shouldSpinLift);
		if(master.get_digital_new_press(DIGITAL_A)) {
			inverseWing();
		}
		if(master.get_digital_new_press(DIGITAL_X)) {
			inverseClip();
		}
		pros::delay(20);

	}
}
