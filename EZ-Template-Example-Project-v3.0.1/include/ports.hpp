#include "api.h"
using namespace pros;
typedef bool mode;
typedef int motorDirection;
extern Motor LDA;
extern Motor LDB;
extern Motor LDC;

extern Motor RDA;
extern Motor RDB;
extern Motor RDC;

extern ADIDigitalOut front_wings;
extern ADIDigitalOut back_wings;
extern ADIDigitalOut hang;

extern IMU inertial;

extern bool stratType;

extern Motor intake1;
extern Motor intake2;
extern Motor_Group intake;

extern Motor cata;

extern Motor toggled;

// extern Rotation rotational;

extern void togglableMotorSpin(int voltage);

extern void togglableMotorSetBrake(motor_brake_mode_e_t brakeMode);

extern void togglableMotorStop();

extern void updateRelativeIMUheading(double* relStorage, double* prevHeading);