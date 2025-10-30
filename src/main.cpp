//https://wcs-isepol1.wcs.edu:8443/portal/PortalSetup.action?portal=6e11bb20-1f62-11e5-9106-005056960da1&sessionId=01A4050A0001BB977B193225&action=cwa&redirect=http%3A%2F%2Fwww.msftconnecttest.com%2Fredirect

#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/llemu.h"
#include "liblvgl/llemu.hpp"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/widgets/lv_img.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/colors.h"
#include "pros/colors.hpp"
#include "pros/gps.hpp"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"
#include "pros/vision.h"
#include "pros/vision.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <chrono>
#include "autons.h"
#include "functions.h"
#include "config.h"



using namespace pros;
using namespace lemlib;

// void prin(){
//     pros::Task goonmommy2([&](){
//         while(true){
//             float hh = imu.get_heading();        
//         int yy = horizontal_tracking_wheel.getDistanceTraveled();
//         int tt = vertical_tracking_wheel.getDistanceTraveled();
//         lcd::print(0, "H: %i V: %i I: %i", yy, tt, hh);
//         delay(3000);
//         }
//     });
// }

// lv_obj_t* war;



lv_obj_t* image;

void initialize() {
           //prin();
    //lcd::initialize();
    
    score_toggle.set_value(false);
    image = lv_img_create(lv_scr_act());
    LV_IMG_DECLARE(apo);
lv_img_set_src(image, &apo);
    lv_obj_set_size(image, 480, 240);
   lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);

// LV_IMG_DECLARE(hogmommy);
//     
// image = ;

    chassis.setPose(0, 0, 0);
   
    bool swit = true;
    cp = 1;
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    op.set_led_pwm(100);
    
    pros::Task goonmommy([&]() {
        while(true){
                printf("x: %f", chassis.getPose().x);
                delay(100);
        }
    
    
    });
    
    
    
            

                              Intake.set_voltage_limit_all(99900000);


    imu.reset();
   
	chassis.calibrate();
    //pros::lcd::initialize(); //?initialize brain screen
	vertical_tracking_wheel.reset();
	horizontal_tracking_wheel.reset();
    //lcd::initialize();

    //!vs.set_led(c::COLOR_WHITE);
    
            
            // else if(cp == -1){
            // lv_img_set_src(image, &hogmommy);
            // lv_obj_set_size(image, 480, 240);
            // lv_obj_align(image, LV_ALIGN_CENTER, 0, 0);
            // }
            // cp *= -1;
            //pros::delay(3000);

        ourColor();
 


    
    
    

  
    

	 
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}


void competition_initialize() {}

void autonomous() {
    red_left_qual();
}





void involt(){
                            //Intake.set_voltage_limit_all(1000000/50);

}


void opcontrol() {
    
    runTime();
    cp = 0;
    bool sixseven = false;
	while (true) {
        

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);      


        

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            score_toggle.toggle();
        }

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
            load_mech.toggle();
            load_mech2.toggle();
        }


        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            sixseven = false;
            backshot_mech.set_value(true);
            delay(125);
            park_mech.set_value(true);
            delay(200);
            backshot_mech.set_value(false);
        }


        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            sixseven = true;
        }

        if(sixseven == true && cp >= 5000){
            sixseven = false;
            backshot_mech.extend();
            delay(125);
            park_mech.extend();
            delay(200);
            backshot_mech.retract();
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            sixseven = false;
             backshot_mech.retract();
            //delay(125);
            park_mech.retract();
            
        }

        
        

       //!If r2 is pressed down, it sets the bool val, otherwise its false;
        
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            runcolor = true;
        }
        else{
            runcolor = false;
        }
        
        
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
 
            
            if(scoring){
                //moveBack(false);
                spin(1);
            }
            else if(!scoring){
                //moveBack(true);
                spin(2);
            }
            else{
                Scoring_Mech.move(0);
                Scoring_Mech.brake();
            }
            Intake.move(127);
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){

            //moveBack(true);
            Intake.move(127);
            if(scoring){
                //ourColor();
                spin(1);
            }
            
            else if(!scoring){
                spin(1);
            }
            else{
                Scoring_Mech.move(0);
                Scoring_Mech.brake();
                
            }
            
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
            //involt();
            Intake.move(-127);
            delay(1);
        }
        else{
            Intake.move(0);
            spin(3);
        }
        
        delay(20);
    }
}
