#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-14, -12, -16}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{17, 15, 13}

  // IMU Port
  ,5

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,1.3333
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 2.
  chassis.opcontrol_curve_default_set(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("Near Quals Hang", near_quals_hang),
    Auton("Near Quals Safe", near_quals_safe),
    Auton("Near Elims", near_elims),
    Auton("Far Quals", far_quals),
    Auton("Far Ball Rush", far_ball_rush),
    Auton("Far Elims", far_elims),
    Auton("Programming Skills", programming_skills),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



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
void autonomous() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold. This helps autonomous consistency

  // score the two preloads
  chassis.drive_set(-55, -127);
  delay(500);
  chassis.drive_set(-127, -127);
  delay(250);
  brake_all();
  // adjust to matchload
  chassis.pid_turn_set(15, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(13, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-60, 110);
  chassis.pid_wait();
  // matchload
  chassis.pid_drive_set(-8, 110);
  back_wings.set_value(true);
  intake2.move(120);
  delay(22000);
  intake2.move(0);
  back_wings.set_value(false);
  // push the middle balls
  intake1.move(127);
  chassis.pid_drive_set(52, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(-130, 110);
  chassis.pid_wait();
  front_wings.set_value(true);
  chassis.pid_drive_set(75, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(-6, 110);
  front_wings.set_value(false);
  chassis.pid_wait();

  chassis.pid_turn_set(-225, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(26, 110);
  chassis.pid_wait();

  chassis.pid_turn_set(-140, 110);
  chassis.pid_wait(); 
  chassis.drive_set(127, 90);
  delay(500);
  brake_all();
  chassis.pid_turn_set(-45, 110);
  chassis.pid_wait();
  front_wings.set_value(true);
  intake2.move(120);
  chassis.pid_drive_set(76, 110);
  chassis.pid_wait();
  intake2.move(0);

  chassis.drive_set(127, 42);
  delay(700);
  brake_all();
  chassis.pid_turn_set(40, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(12, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(-12, 110);
  chassis.pid_wait();
  // chassis.pid_drive_set(13, 110);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-12, 110);
  // chassis.pid_wait();
  front_wings.set_value(false);
  intake1.move(0);

  // go to front of goal
  chassis.pid_turn_set(105, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(50, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(45, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(20, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(135, 90);

  back_wings.set_value(true);
  chassis.pid_drive_set(-28, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(135, 110);
  back_wings.set_value(false);
  chassis.pid_wait();
  chassis.pid_drive_set(36, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(45, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(20, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(-45, 90);
  chassis.pid_wait();
  front_wings.set_value(true);
  intake1.move(127);
  chassis.pid_drive_set(32, 110);
  chassis.pid_wait();

  chassis.pid_drive_set(-34, 90);
  front_wings.set_value(false);
  chassis.pid_wait();
  chassis.pid_turn_set(-135, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-20, 90);
  chassis.pid_wait();
  chassis.pid_turn_set(-280, 90);
  chassis.pid_wait();

  back_wings.set_value(true);
  chassis.pid_drive_set(-42, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(40, 110);
  back_wings.set_value(false);
  chassis.pid_wait();

  chassis.pid_turn_set(-25, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(42, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-110, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(30, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(-42, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-225, 110);
  hang.set_value(true);
  chassis.pid_wait();
  chassis.pid_drive_set(45, 110);
  chassis.pid_wait();
  hang.set_value(false);
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
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_BRAKE);
  
  bool front_set = false;
  bool front_can_toggle = true;

  bool back_set = false;
  bool back_can_toggle = true;

  bool skills = false;

  const double deadzone = 10.0;
  while (true) {
    
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) { 
      // Enable / Disable PID Tuner
      //  When enabled: 
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      // if (master.get_digital_new_press(DIGITAL_X)) 
      //   chassis.pid_tuner_toggle();
        
      // Trigger the selected autonomous routine
      // if (master.get_digital_new_press(DIGITAL_LEFT)) 
      //   autonomous();

      // chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    } 

    // . . .
    // drivetrain
    double fwd = master.get_analog(ANALOG_LEFT_Y);
    double turn = master.get_analog(ANALOG_RIGHT_X);
    if (fabs(fwd) > deadzone || fabs(turn) > deadzone) {
      LDA.move(fwd + turn);
      RDA.move(fwd - turn);
      LDB.move(fwd + turn);
      RDB.move(fwd - turn);
      LDC.move(fwd + turn);
      RDC.move(fwd - turn);
    } else {
      LDA.brake();
      RDA.brake();
      LDB.brake();
      RDB.brake();
      LDC.brake();
      RDC.brake();
    }

    if (master.get_digital(DIGITAL_L1) && front_can_toggle) {
      front_set = !front_set;
      front_wings.set_value(front_set);
      front_can_toggle = false;
    }
    if (!master.get_digital(DIGITAL_L1)) {
      front_can_toggle = true;
    }

    if (master.get_digital(DIGITAL_L2) && back_can_toggle) {
      back_set = !back_set;
      back_wings.set_value(back_set);
      back_can_toggle = false;
    }
    if (!master.get_digital(DIGITAL_L2)) {
      back_can_toggle = true;
    }

    if (master.get_digital(DIGITAL_R1)) {
      intake1.move(120);
      intake2.move(120);
    } else if (master.get_digital(DIGITAL_R2)) {
      intake1.move(-120);
      intake2.move(-120);
    } else if (master.get_digital(DIGITAL_Y)) {
      intake1.move(0);
      intake2.move(0);
    }

    if (master.get_digital(DIGITAL_X)) hang.set_value(true);
    else if (master.get_digital(DIGITAL_A)) hang.set_value(false);

    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
