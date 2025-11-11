#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
#include "config.h"
#include "lemlib/chassis/trackingWheel.hpp"
#include "lemlib/pid.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include "pros/misc.h"
#include <cstddef>


pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Default drivetrain
pros::MotorGroup DL({11, -12, 13}, pros::MotorGearset::blue);
//done
pros::MotorGroup DR({-17, 18, -19}, pros::MotorGearset::blue);
pros::Rotation horizontal_encoder(-14);
// vertical tracking wheel encoder
pros::Rotation vertical_encoder(-15);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275_HALF, 1.5, 1);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275_HALF, -.5, 1);
pros::Optical op(6);
pros::Motor Scoring_Mech(1);
pros::Motor Intake(20);
//Gear ratio is Default 1 
// Default IMU
pros::Imu imu(2);
pros::adi::Pneumatics load_mech('C', false);
pros::adi::Pneumatics score_toggle('B', false);
pros::adi::Pneumatics park_mech('D', false);
pros::adi::Pneumatics backshot_mech('E', false);
pros::adi::Potentiometer alliance_switch('F');
pros::Distance wall_distance(3);

//Drivetrain - trackWidth still needs to be set + i think rpm is 480
lemlib::Drivetrain drivetrain(&DL, // left motor group
                              &DR, // right motor group
                              11.5, // 11.5 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              600, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

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

