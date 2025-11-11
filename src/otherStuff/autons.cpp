#include "autons.h"
#include "config.h"
#include "functions.h"
#include "lemlib/api.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/core/lv_obj_scroll.h"
#include <random>

void prog_skills(){
    alliance = true;
    chassis.setPose(-46.5, 5, 0);
    // pick up cluster 1
    chassis.moveToPose(-24, 24, 90, 2000, {.maxSpeed = 100});
    score_toggle.extend();
    Intake.move(127);
    Scoring_Mech.move(127);
    // clear loader 1
    chassis.moveToPoint(-46, 46, 1000, {.forwards = false});
    chassis. turnToHeading(270, 750);
    load_mech.extend();
    chassis.moveToPoint(-58, 46, 1000);
    chassis.waitUntilDone();
    pros::delay(500);
    // score long goal 1 side 1
    chassis.moveToPoint(-30, 46, 1000, {.forwards = false});
    pros::delay(250);
    Scoring_Mech.brake();
    pros::delay(250);
    score_toggle.retract();
    chassis.waitUntilDone();
    Scoring_Mech.move(127);
    load_mech.retract();
    pros::delay(2000);
    Scoring_Mech.brake();
    // pick up cluster 2
    chassis.swingToPoint(-24, 24, lemlib::DriveSide::LEFT, 750);
    chassis.moveToPoint(-24, 24, 1000);
    score_toggle.extend();
    chassis.turnToPoint(24, 24, 500);
    chassis.moveToPoint(24, 24, 1000);
    Scoring_Mech.move(80);
    chassis.waitUntilDone();
    // score low mid goal
    chassis.turnToPoint(12, 12, 750);
    chassis.moveToPoint(12, 12, 1000);
    chassis.waitUntilDone();
    Intake.move(-127);
    pros::delay(2000);
    // clear loader 2
    chassis.moveToPoint(46, 46, 1500, {.forwards = false});
    chassis.turnToHeading(90, 750);
    Intake.move(127);
    load_mech.extend();
    chassis.moveToPoint(58, 46, 1000);
    chassis.waitUntilDone();
    pros::delay(500);
    // score long goal 1 side 2
    chassis.moveToPoint(30, 46, 1000, {.forwards = false});
    pros::delay(250);
    Scoring_Mech.brake();
    pros::delay(250);
    score_toggle.retract();
    chassis.waitUntilDone();
    Scoring_Mech.move(127);
    pros::delay(2000);
    // pick up cluster 3
    Scoring_Mech.brake();
    chassis.swingToPoint(24, -24, lemlib::DriveSide::RIGHT, 750);
    chassis.moveToPoint(24, -24, 2000);
    score_toggle.extend();
    chassis.waitUntilDone();
    // score high mid goal
    chassis.turnToPoint(12, -12, 500, {.forwards = false});
    chassis.moveToPoint(12, -12, 1000, {.forwards = false});
    chassis.waitUntilDone();
    Scoring_Mech.move(-127);
    pros::delay(2000);
    // clear loader 3
    Scoring_Mech.move(127);
    chassis.moveToPoint(46, -46, 1000);
    chassis.turnToHeading(90, 500);
    load_mech.extend();
    chassis.moveToPoint(58, -46, 1000);
    chassis.waitUntilDone();
    pros::delay(500);
    // score long goal 2 side 1
    chassis.moveToPoint(30, -46, 1000, {.forwards = false});
    pros::delay(250);
    Scoring_Mech.brake();
    pros::delay(250);
    score_toggle.retract();
    chassis.waitUntilDone();
    Scoring_Mech.move(127);
    pros::delay(2000);
    // pick up cluster 4
    Scoring_Mech.brake();
    chassis.swingToPoint(24, -24, lemlib::DriveSide::LEFT, 750);
    chassis.moveToPoint(24, -24, 1000);
    score_toggle.extend();
    chassis.turnToPoint(-24, -24, 500);
    chassis.moveToPoint(-24, -24, 2000);
    // clear loader 4
    chassis.moveToPoint(-46, -46, 1000);
    chassis.turnToHeading(270, 500);
    load_mech.extend();
    chassis.moveToPoint(-58, -46, 1000);
    chassis.waitUntilDone();
    pros::delay(500);
    // score long goal 2 side 2
    chassis.moveToPoint(-30, -46, 1000, {.forwards = false});
    pros::delay(250);
    Scoring_Mech.brake();
    pros::delay(250);
    score_toggle.retract();
    chassis.waitUntilDone();
    Scoring_Mech.move(127);
    pros::delay(2000);
    // park
    chassis.moveToPoint(-62, -18, 1000);
    chassis.turnToHeading(0, 500);
    chassis.moveToPoint(-62, 0, 2000);
}

void full_sawp(){
    alliance = get_alliance();
    Intake.move(127);
    chassis.setPose(52, -17.4, 270);
    // picking up cluster 1
    chassis.moveToPoint(15, -23, 1250);
    pros::delay(500);
    load_mech.extend();
    pros::delay(400);
    load_mech.retract();
    chassis.swingToHeading(135, lemlib::DriveSide::RIGHT, 600, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    // score mid goal
    chassis.moveToPoint(0, 0, 1500, {.forwards = false, .maxSpeed = 20});
    Scoring_Mech.move(-110);
    pros::delay(1500);
    chassis.cancelMotion();
    chassis.waitUntilDone();
    pros::delay(250);
    Scoring_Mech.brake();
    chassis.setPose(14, -15, chassis.getPose().theta);
    // clear loader 1
    chassis.moveToPoint(48, -50, 1500, {.maxSpeed = 80});
    load_mech.extend();
    pros::delay(500);
    score_toggle.extend();
    chassis.turnToHeading(90, 500);
    score_toggle.retract();
    chassis.moveToPoint(90, chassis.getPose().y, 800, {.maxSpeed = 60});
    Scoring_Mech.move(50);
    // score long goal 1
    chassis.moveToPoint(0, chassis.getPose().y, 1000, {.forwards = false, .maxSpeed = 80});
    pros::delay(1000);
    chassis.moveToPoint(0, chassis.getPose().y, 1000, {.forwards = false, .maxSpeed = 20});
    Scoring_Mech.move(127);
    pros::delay(500);
    chassis.cancelMotion();
    pros::delay(750);
    Scoring_Mech.brake();
    load_mech.retract();
    // picking up cluster 2
    chassis.setPose(29.5, -48, chassis.getPose().theta);
    chassis.swingToPoint(20, 20, lemlib::DriveSide::LEFT, 750);
    chassis.moveToPoint(20, 20, 1250);
    Scoring_Mech.move(50);
    pros::delay(1100);
    load_mech.extend();
    // scoring long goal 2
    chassis.turnToHeading(90, 500);
    pros::delay(250);
    load_mech.retract();
    chassis.moveToPoint(44, 42, 1000);
    chassis.turnToHeading(90, 500);
    chassis.waitUntilDone();
    pros::delay(50);
    chassis.moveToPoint(20, chassis.getPose().y+get_distance_difference(), 1000, {.forwards = false, .maxSpeed = 80});
    pros::delay(1000);
    chassis.cancelMotion();
    chassis.moveToPoint(20, chassis.getPose().y, 1500, {.forwards = false, .maxSpeed = 20});
    Scoring_Mech.move(127);
    chassis.turnToHeading(90, 500);
    load_mech.retract();
}

void left_long_nopush(){
    alliance = get_alliance();
    chassis.setPose(-45, 5, 57);
    // pick up cluster
    chassis.moveToPoint(-22, 22, 1000);
    Intake.move(127);
    // pick up rush blocks
    chassis.moveToPoint(-8, 45, 1000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    pros::delay(250);
    // clear loader
    chassis.moveToPoint(-27, 30, 1000, {.forwards = false});
    score_toggle.extend();
    Scoring_Mech.move(127);
    chassis.turnToPoint(-46, 46, 1000);
    chassis.turnToHeading(270, 500);
    load_mech.extend();
    chassis.moveToPoint(-58, 46, 1000);
    // score long goal
    chassis.moveToPoint(-30, 46, 1000, {.forwards = false});
    pros::delay(250);
    Scoring_Mech.brake();
    pros::delay(250);
    score_toggle.retract();
    chassis.waitUntilDone();
    Scoring_Mech.move(127);
    load_mech.retract();
}

void left_split_push(){
    alliance = get_alliance();
    Intake.move(127);
    chassis.setPose(52, -17.4, 270);
    // picking up cluster 1
    chassis.moveToPoint(15, -23, 1250);
    pros::delay(500);
    load_mech.extend();
    pros::delay(400);
    load_mech.retract();
    chassis.swingToHeading(135, lemlib::DriveSide::RIGHT, 600, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE});
    // score mid goal
    chassis.moveToPoint(0, 0, 1500, {.forwards = false, .maxSpeed = 20});
    Scoring_Mech.move(-110);
    pros::delay(1500);
    chassis.cancelMotion();
    chassis.waitUntilDone();
    pros::delay(250);
    Scoring_Mech.brake();
    chassis.setPose(14, -15, chassis.getPose().theta);
    // clear loader 1
    chassis.moveToPoint(48, -50, 1500, {.maxSpeed = 80});
    load_mech.extend();
    pros::delay(500);
    score_toggle.extend();
    chassis.turnToHeading(90, 500);
    score_toggle.retract();
    chassis.moveToPoint(90, chassis.getPose().y, 800, {.maxSpeed = 60});
    Scoring_Mech.move(50);
    // score long goal 1
    chassis.moveToPoint(0, chassis.getPose().y, 1000, {.forwards = false, .maxSpeed = 80});
    pros::delay(1000);
    chassis.moveToPoint(0, chassis.getPose().y, 1000, {.forwards = false, .maxSpeed = 20});
    Scoring_Mech.move(110);
    pros::delay(500);
    chassis.cancelMotion();
    pros::delay(1000);
    Scoring_Mech.brake();
    load_mech.retract();
    // goal push
    chassis.setPose(29.5, -48, chassis.getPose().theta);
    chassis.moveToPoint(40, -36, 1000);
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(8, chassis.getPose().y, 1500, {.forwards = false});
    // chassis.turnToHeading(120, 500);
    // chassis.turnToHeading(90, 500);
    chassis.moveToPoint(40, chassis.getPose().y, 1000);
}

void right_long_rush(){

}