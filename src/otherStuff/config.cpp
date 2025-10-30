#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
#include "config.h"
#include "lemlib/chassis/trackingWheel.hpp"
#include "lemlib/pid.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include "pros/misc.h"
#include <cstddef>


pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Default drivetrain
pros::MotorGroup DL({11, -12, 13}, pros::MotorGearset::blue); 
//done
pros::MotorGroup DR({-17, 18, -19}, pros::MotorGearset::blue);
pros::Rotation horizontal_encoder(14);
// vertical tracking wheel encoder
pros::Rotation vertical_encoder(-15);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, .75, 1);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -1, 1);
pros::Optical op(6);
pros::Motor Scoring_Mech(1);
pros::Motor Intake(20);
//Gear ratio is Default 1 
// Default IMU
pros::Imu imu(2);
pros::adi::Pneumatics load_mech2('C', false);
pros::adi::Pneumatics load_mech('A', false);
pros::adi::Pneumatics score_toggle('B', false);
pros::adi::Pneumatics park_mech('D', false);
pros::adi::Pneumatics backshot_mech('E', false);

//Drivetrain - trackWidth still needs to be set + i think rpm is 480
lemlib::Drivetrain drivetrain(&DL, // left motor group
                              &DR, // right motor group
                              11.5, // 11.5 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              600, // drivetrain rpm is 450
                              10 // horizontal drift is 2 (for now)
);


//2 in

//2.5in

// lemlib::ControllerSettings lateral_controller(8, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               22.35, // derivative gain (kD)
//                                               3, // anti windup
//                                               1, // small error range, in inches
//                                               100, // small error range timeout, in milliseconds
//                                               3, // large error range, in inches
//                                               1000, // large error range timeout, in milliseconds
//                                               15// maximum acceleration (slew)
// );

// lemlib::ControllerSettings angular_controller(3.9, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               16.7, // derivative gain (kD)
//                                               3, // anti windup
//                                               1, // small error range, in degrees
//                                               100, // small error range timeout, in milliseconds
//                                               3, // large error range, in degrees
//                                               500, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );

// Need to tune 
lemlib::ControllerSettings lateral_controller(6, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              22, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              1000, // large error range timeout, in milliseconds
                                              20// maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(2.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              27, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in degrees
                                              1000, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0// maximum acceleration (slew)
);


//89.69
//89.16
//88.03

//93.7
//89.8
//94.18
//90.01
//92.98

//88.72
//89.81
//88.63
//92.13
//92.01
//89.73

//359.33
//2.87
//2.20

//3.3
//359.8
//4.21
//6.06

//2.31
//0.17

//1.95
//4.98
//4.1
// lemlib::ControllerSettings lateral_controller(8, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               22.35, // derivative gain (kD)
//                                               3, // anti windup
//                                               1, // small error range, in inches
//                                               100, // small error range timeout, in milliseconds
//                                               3, // large error range, in inches
//                                               1000, // large error range timeout, in milliseconds
//                                               15// maximum acceleration (slew)
// );

// lemlib::ControllerSettings angular_controller(3.9, // proportional gain (kP)
//                                               0, // integral gain (kI)
//                                               16.7, // derivative gain (kD)
//                                               3, // anti windup
//                                               1, // small error range, in degrees
//                                               100, // small error range timeout, in milliseconds
//                                               3, // large error range, in degrees
//                                               500, // large error range timeout, in milliseconds
//                                               0 // maximum acceleration (slew)
// );

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal_tracking_wheel, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller,
						sensors // angular PID settings
                        
);

