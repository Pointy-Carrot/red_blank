#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/device.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include "pros/apix.h"

extern pros::Controller controller;
extern pros::MotorGroup DL;
extern pros::MotorGroup DR;
extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;
extern pros::Optical op;
extern pros::Motor Scoring_Mech;
extern pros::Motor Intake;
extern pros::Imu imu;
extern pros::adi::Pneumatics load_mech2;
extern pros::adi::Pneumatics load_mech;
extern pros::adi::Pneumatics score_toggle;
extern pros::adi::Pneumatics park_mech;
extern pros::adi::Pneumatics backshot_mech;

// lemlib constructors

extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::Chassis chassis;
