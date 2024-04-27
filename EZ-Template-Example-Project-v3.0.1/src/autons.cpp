#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(14, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(1_ms, 4_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(1_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}

// . . .
// void rotate_to_angle(int32_t angle, pros::Motor motor) {
//   int initial_angle = rotational.get_angle() / 100;
//   int turn_degs = 360 - initial_angle;
//   int spin_speed = 100;
//   rotational.set_position(0);
//   while ((rotational.get_angle() / 100) < turn_degs) {
//     spin_speed = (40 * ((rotational.get_angle() / 100) / turn_degs)) + 10;
//     motor.move(spin_speed);
//   }

// }

void brake_all() {
  LDA.brake();
  RDA.brake();
  LDB.brake();
  RDB.brake();
  LDC.brake();
  RDC.brake();
}

void near_quals_hang() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold. This helps autonomous consistency

  // score the preload
  chassis.drive_set(-60, -127);
  delay(500);
  chassis.drive_set(-127, -127);
  delay(225);
  brake_all();

  // get the corner ball out
  chassis.drive_set(127, 127);
  delay(200);
  chassis.drive_set(30, 127);
  delay(250);
  back_wings.set_value(true);
  chassis.drive_set(25, 127);
  delay(600);
  brake_all();
  back_wings.set_value(false);
  delay(200);

  // rush to the middle
  chassis.pid_turn_set(-110, 110);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_drive_set(49, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-45, 110);
  chassis.pid_wait();

  // deploy front wings, spin intake, push two middle balls over
  front_wings.set_value(true);
  intake.move(127);
  chassis.pid_drive_set(24, 110);
  chassis.pid_wait();
  intake.move(0);
  front_wings.set_value(false);
  
  // turn towards colored bars, deploy back wings, drive forward to touch colored bar with back wings
  chassis.pid_drive_set(-3, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(45, 110);
  chassis.pid_wait();
  back_wings.set_value(true);
  chassis.drive_imu_reset();
  delay(1000);
  chassis.drive_set(60, 110);
}

void near_quals_safe() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold. This helps autonomous consistency

  // score the preload
  chassis.drive_set(-60, -127);
  delay(500);
  chassis.drive_set(-127, -127);
  delay(225);
  brake_all();

  // get the corner ball out
  chassis.drive_set(127, 127);
  delay(200);
  chassis.drive_set(30, 127);
  delay(250);
  back_wings.set_value(true);
  chassis.drive_set(25, 127);
  delay(600);
  brake_all();
  back_wings.set_value(false);
  delay(200);

  // rush to the middle
  chassis.pid_turn_set(-110, 110);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_drive_set(49, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-45, 110);
  chassis.pid_wait();

  // deploy front wings, spin intake, push two middle balls over
  front_wings.set_value(true);
  intake.move(127);
  chassis.pid_drive_set(24, 110);
  chassis.pid_wait();
  front_wings.set_value(false);

  intake.move(0);
  chassis.pid_drive_set(-30, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(45, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(50, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-45, 110);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(26, 110);
  chassis.pid_wait();
  delay(500);
  intake.move(0);
}

void near_elims() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold. This helps autonomous consistency

  // score the preload
  chassis.drive_set(-60, -127);
  delay(500);
  chassis.drive_set(-127, -127);
  delay(225);
  brake_all();

  // get the corner ball out
  chassis.drive_set(127, 127);
  delay(200);
  chassis.drive_set(30, 127);
  delay(250);
  back_wings.set_value(true);
  chassis.drive_set(25, 127);
  delay(600);
  brake_all();
  back_wings.set_value(false);
  delay(200);

  // rush to the middle
  chassis.pid_turn_set(-120, 110);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_drive_set(49, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-45, 110);
  chassis.pid_wait();

  // deploy front wings, spin intake, push two middle balls over
  front_wings.set_value(true);
  intake.move(127);
  chassis.pid_drive_set(24, 110);
  chassis.pid_wait();
  front_wings.set_value(false);

  intake.move(0);
  chassis.pid_drive_set(-30, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(45, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(50, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(-45, 110);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(26.5, 110);
  chassis.pid_wait();

  chassis.pid_drive_set(-36, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(0, 110);
  back_wings.set_value(true);
}

void far_quals() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold. This helps autonomous consistency

  chassis.pid_drive_set(7, 110);
  intake.move(-127);
  chassis.pid_wait();
  delay(500);

  chassis.pid_drive_set(-30, 110);
  chassis.pid_wait();
  chassis.drive_set(-127, -45);
  delay(250);
  back_wings.set_value(true);
  chassis.drive_set(-127, -45);
  delay(350);
  back_wings.set_value(false);
  delay(350);
  brake_all();
  chassis.pid_turn_set(-90, 110);
  chassis.pid_wait();

  chassis.drive_set(-127, -127);
  delay(800);

  chassis.pid_drive_set(12, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(90, 110);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(14, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(-12.5, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(17.5, 110);
  chassis.pid_wait();

  // middle
  intake.move(-127);
  chassis.pid_drive_set(48, 110);
  chassis.pid_wait();
  intake.move(0);
  chassis.pid_turn_set(165, 110);
  chassis.pid_wait();
  intake.move(127);
  delay(400);
  chassis.pid_turn_set(80, 110);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_drive_set(21, 40);
  chassis.pid_wait();
  intake.move(0);
  chassis.pid_turn_set(170, 110);
  chassis.pid_wait();
  front_wings.set_value(true);
  chassis.drive_set(127, 127);
  delay(900);
  brake_all();
  
  // touch pole
  chassis.pid_drive_set(-40, 110);
  front_wings.set_value(false);
  chassis.pid_wait();
  chassis.pid_turn_set(105, 110);
  chassis.pid_wait();
  back_wings.set_value(true);
  chassis.pid_drive_set(-29, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(62.5, 110);
  chassis.pid_wait();
}

void far_ball_rush() {
  front_wings.set_value(true);
  chassis.pid_drive_set(58, 110);
  delay(200);
  front_wings.set_value(false);
  delay(400);
  intake.move(-127);
  chassis.pid_wait();
  delay(650);
  intake.move(0);

  chassis.pid_turn_set(120, 110);
  chassis.pid_wait();
  front_wings.set_value(true);
  intake.move(127);
  chassis.pid_drive_set(30, 110);
  chassis.pid_wait();
  intake.move(0);

  chassis.pid_drive_set(-16, 110);
  chassis.pid_wait();
  front_wings.set_value(false);
  chassis.pid_turn_set(260, 110);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_drive_set(22, 110);
  chassis.pid_wait();
  intake.move(0);
  chassis.pid_turn_set(140, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(33, 110);
  chassis.pid_wait();
  intake.move(127);
  delay(500);
  intake.move(0);
  chassis.pid_turn_set(225, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(24, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(300, 110);
  chassis.pid_wait();
  
  // start of regular 6-ball
  chassis.pid_targets_reset();
  chassis.drive_imu_reset();
  chassis.drive_sensor_reset();

  chassis.pid_drive_set(25, 110);
  intake.move(-127);
  chassis.pid_wait();

  chassis.pid_drive_set(-30, 110);
  chassis.pid_wait();
  chassis.drive_set(-127, -45);
  delay(250);
  back_wings.set_value(true);
  chassis.drive_set(-127, -45);
  delay(350);
  back_wings.set_value(false);
  delay(350);
  brake_all();
  chassis.pid_turn_set(-90, 110);
  chassis.pid_wait();

  chassis.drive_set(-127, -127);
  delay(800);

  chassis.pid_drive_set(12, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(90, 110);
  chassis.pid_wait();
  intake.move(127);
  chassis.drive_set(127, 127);
  delay(800);
  intake.move(0);
  chassis.drive_set(-127, -127);
  delay(300);
  chassis.pid_turn_set(0, 110);
  chassis.pid_wait();
}

void far_elims() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold. This helps autonomous consistency

  chassis.pid_drive_set(7, 110);
  intake.move(-127);
  chassis.pid_wait();
  delay(500);

  chassis.pid_drive_set(-30, 110);
  chassis.pid_wait();
  chassis.drive_set(-127, -45);
  delay(250);
  back_wings.set_value(true);
  chassis.drive_set(-127, -45);
  delay(350);
  back_wings.set_value(false);
  delay(350);
  brake_all();
  chassis.pid_turn_set(-90, 110);
  chassis.pid_wait();

  chassis.drive_set(-127, -127);
  delay(800);

  chassis.pid_drive_set(12, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(90, 110);
  chassis.pid_wait();
  intake.move(127);
  chassis.pid_drive_set(14, 110);
  chassis.pid_wait();
  chassis.pid_drive_set(-12.5, 110);
  chassis.pid_wait();
  chassis.pid_turn_set(17.5, 110);
  chassis.pid_wait();

  // middle
  intake.move(-127);
  chassis.pid_drive_set(48, 110);
  chassis.pid_wait();
  intake.move(0);
  chassis.pid_turn_set(165, 110);
  chassis.pid_wait();
  intake.move(127);
  delay(400);
  chassis.pid_turn_set(80, 110);
  chassis.pid_wait();
  intake.move(-127);
  chassis.pid_drive_set(21, 40);
  chassis.pid_wait();
  intake.move(0);
  chassis.pid_turn_set(170, 110);
  chassis.pid_wait();
  front_wings.set_value(true);
  chassis.drive_set(127, 127);
  delay(900);
  brake_all();
  
  // face barrier
  chassis.pid_drive_set(-36, 110);
  front_wings.set_value(false);
  chassis.pid_wait();
  chassis.pid_turn_set(0, 110);
  chassis.pid_wait();
}

void programming_skills() {
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
  chassis.pid_turn_set(-65, 110);
  chassis.pid_wait();
  // matchload
  chassis.pid_drive_set(-8, 110);
  back_wings.set_value(true);
  intake2.move(120);
  delay(27000);
  intake2.move(0);
  back_wings.set_value(false);
  // // push the middle balls
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
  chassis.pid_drive_set(27, 110);
  chassis.pid_wait();

  chassis.pid_turn_set(-135, 110);
  chassis.pid_wait(); 
  chassis.drive_set(127, 80);
  delay(550);
  brake_all();
  chassis.pid_turn_set(-45, 110);
  chassis.pid_wait();
  front_wings.set_value(true);
  intake2.move(120);
  chassis.pid_drive_set(78, 110);
  chassis.pid_wait();
  intake2.move(0);

  chassis.drive_set(127, 45);
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
  chassis.pid_drive_set(-30, 110);
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
  chassis.pid_drive_set(34, 110);
  chassis.pid_wait();

  chassis.pid_drive_set(-36, 90);
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
// . . .