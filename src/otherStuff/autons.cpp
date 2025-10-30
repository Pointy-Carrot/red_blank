#include "autons.h"
#include "config.h"
#include "functions.h"
#include "lemlib/api.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include <random>


void red_left_qual(){
    alliance_red();
    chassis.setPose(-45, -5, 107);
    //score_toggle.set_value(true);
    Intake.move(127);
    chassis.moveToPoint(-5, -16, 400, {.maxSpeed = 100});
        Intake.move(127);

    chassis.moveToPoint(3.5, -30, 1000, {.maxSpeed = 100});
       chassis.moveToPoint(-17, -20, 400, {.forwards = false});
       score_toggle.set_value(true);
       cycle_intake(127);
    chassis.turnToPoint(-30, -48, 500);
    chassis.moveToPoint(-30, -48, 1000);
    load_mech.set_value(true);
    load_mech2.set_value(true);
        chassis.turnToHeading(270, 500);
        chassis.moveToPoint(-48, chassis.getPose().y, 1000);
        chassis.waitUntilDone();
    pros::delay(500);

};
void red_right_qual(){
    alliance_red();
};
void red_left_elim(){
    alliance_red();
};
void red_right_elim(){
    alliance_red();
};
void red_sawp(){
    alliance_red();
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
    alliance_blue();
};
void blue_sawp(){
    alliance_blue();
};