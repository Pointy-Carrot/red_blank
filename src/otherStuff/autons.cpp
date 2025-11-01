#include "autons.h"
#include "config.h"
#include "functions.h"
#include "lemlib/api.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include <random>


void red_left_qual(){
    
};
void red_right_qual(){
    alliance = true;
};
void red_left_elim(){
    
};
void red_right_elim(){
    alliance = true;
    chassis.setPose(-45, -5, 123);
    //score_toggle.set_value(true);
    Intake.move(127);
    chassis.moveToPoint(-13, -24, 400, {.maxSpeed = 100});
    chassis.moveToPoint(-6, -40, 1000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    pros::delay(205);
    chassis.moveToPoint(-24, -24, 1000, {.forwards = false});
    score_toggle.set_value(true);
    Scoring_Mech.move(105);
    chassis.turnToPoint(-40, -46, 500);
    chassis.moveToPoint(-40, -46, 1000);
    load_mech.set_value(true);
    load_mech2.set_value(true);
    chassis.waitUntilDone();
    pros::delay(250);
    chassis.turnToPoint(-60, chassis.getPose().y, 500);
    chassis.moveToPoint(-58, chassis.getPose().y, 1000);
    chassis.waitUntilDone();
    pros::delay(75);
    chassis.moveToPoint(-30, chassis.getPose().y-1, 500, {.forwards = false});
    Scoring_Mech.brake();
    chassis.moveToPoint(-24, chassis.getPose().y+2, 500, {.forwards = false});
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    score_toggle.set_value(false);
    Scoring_Mech.move(127);
    load_mech.retract();
    load_mech2.retract();
};
void red_sawp(){
    alliance = true;
    chassis.setPose(-46.5, -6, 180);
    
    chassis.moveToPoint(-46.5, -46, 1000);
    load_mech.extend();
    load_mech2.extend();
    chassis.turnToHeading(270, 500);
    chassis.moveToPoint(-60, chassis.getPose().y, 800);
    score_toggle.extend();
    Intake.move(127);
    Scoring_Mech.move(127);
    chassis.waitUntilDone();
    pros::delay(50);
    chassis.moveToPoint(-20, chassis.getPose().y+2, 1250, {.forwards = false});
    Scoring_Mech.brake();
    chassis.turnToHeading(275, 250);
    chassis.waitUntilDone();
    score_toggle.set_value(false);
    Scoring_Mech.move(127);
    load_mech.retract();
    load_mech2.retract();
    pros::delay(1500);
    Scoring_Mech.brake();
    score_toggle.extend();
    chassis.moveToPoint(-40, chassis.getPose().y, 1000);
    chassis.turnToPoint(-24, -26, 750);
    chassis.moveToPoint(-24, -26, 2000, {.maxSpeed = 60});
    Scoring_Mech.move(80);
    chassis.moveToPoint(-12, -15, 1000);
    chassis.turnToHeading(45, 500);
    chassis.waitUntilDone();
    Intake.move(-100);
    pros::delay(3000);
    chassis.moveToPoint(-34, -34, 1000, {.forwards = false});
    chassis.turnToHeading(90, 500);
    score_toggle.retract();
    chassis.moveToPoint(-12, -34, 1000);
};
void blue_left_qual(){
    alliance_blue();
};
void blue_right_qual(){
    alliance_blue();
};
void blue_left_elim(){
    alliance_blue();
};
void blue_right_elim(){
    alliance = false;
    chassis.setPose(-45, -5, 123);
    //score_toggle.set_value(true);
    Intake.move(127);
    chassis.moveToPoint(-13, -24, 400, {.maxSpeed = 100});
    chassis.moveToPoint(-6, -40, 1000, {.maxSpeed = 100});
    chassis.waitUntilDone();
    pros::delay(205);
    chassis.moveToPoint(-24, -24, 1000, {.forwards = false});
    score_toggle.set_value(true);
    Scoring_Mech.move(105);
    chassis.turnToPoint(-40, -46, 500);
    chassis.moveToPoint(-40, -46, 1000);
    load_mech.set_value(true);
    load_mech2.set_value(true);
    chassis.waitUntilDone();
    pros::delay(250);
    chassis.turnToPoint(-60, chassis.getPose().y, 500);
    chassis.moveToPoint(-58, chassis.getPose().y, 1000);
    chassis.waitUntilDone();
    pros::delay(75);
    chassis.moveToPoint(-30, chassis.getPose().y-1, 500, {.forwards = false});
    Scoring_Mech.brake();
    chassis.moveToPoint(-24, chassis.getPose().y+2, 500, {.forwards = false});
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    score_toggle.set_value(false);
    Scoring_Mech.move(127);
    load_mech.retract();
    load_mech2.retract();
};
void blue_sawp(){
    alliance = false;
    chassis.setPose(-46.5, -6, 180);
    
    chassis.moveToPoint(-46.5, -46, 1000);
    load_mech.extend();
    load_mech2.extend();
    chassis.turnToHeading(270, 500);
    chassis.moveToPoint(-60, chassis.getPose().y, 800);
    score_toggle.extend();
    Intake.move(127);
    Scoring_Mech.move(127);
    chassis.waitUntilDone();
    pros::delay(50);
    chassis.moveToPoint(-20, chassis.getPose().y+2, 1250, {.forwards = false});
    Scoring_Mech.brake();
    chassis.turnToHeading(275, 250);
    chassis.waitUntilDone();
    score_toggle.set_value(false);
    Scoring_Mech.move(127);
    load_mech.retract();
    load_mech2.retract();
    pros::delay(1500);
    Scoring_Mech.brake();
    score_toggle.extend();
    chassis.moveToPoint(-40, chassis.getPose().y, 1000);
    chassis.turnToPoint(-24, -26, 750);
    chassis.moveToPoint(-24, -26, 2000, {.maxSpeed = 60});
    Scoring_Mech.move(80);
    chassis.moveToPoint(-12, -15, 1000);
    chassis.turnToHeading(45, 500);
    chassis.waitUntilDone();
    Intake.move(-100);
    pros::delay(3000);
    chassis.moveToPoint(-34, -34, 1000, {.forwards = false});
    chassis.turnToHeading(90, 500);
    score_toggle.retract();
    chassis.moveToPoint(-12, -34, 1000);
};