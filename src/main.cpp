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



using namespace pros;
using namespace lemlib;

pros::Controller controller(pros::E_CONTROLLER_MASTER);

   float t = 0;
    float k = 0;
    float h = 0; 
    float j = 0;

int cp = 1;
int check = 0;
bool load;
bool toggle;
bool scoring;
bool park;
bool backshot;
int forw  = 1;
bool fort = true;
bool runcolor = false;
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
pros::adi::DigitalOut load_mech2('C', false);
pros::adi::DigitalOut load_mech('A', false);
pros::adi::DigitalOut score_toggle('B', false);
pros::adi::DigitalOut park_mech('D', false);
pros::adi::DigitalOut backshot_mech('E', false);

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

// Need to tune 
lemlib::ControllerSettings lateral_controller(11, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              70, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              1000, // large error range timeout, in milliseconds
                                              20// maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(1.25, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              16.5, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              2, // large error range, in degrees
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

float guh;


void runTime(){
    pros::Task unctask3([&]() {
        
        delay(104450);
        //delay(30000);
        cp = 5000;
    });
    
}




void forwSet(int i){
    forw = i;
}

void setfort(bool forrt){
    fort = forrt;
}

void spin(int f){
    if(fort == true){
    if(f == 1){
        Scoring_Mech.move(127);
        forwSet(1);
    }
    else if(f == 2){
        Scoring_Mech.move(-127);
        forwSet(-1);
    }
    else{
        Scoring_Mech.move(0);
        Scoring_Mech.brake();
    }
}
}




//!Try removing the &
void ourColor(){
     pros::Task unctask2([&]() {
        while(true){
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && scoring) {
            //lcd::print(2, "Prox %i", op.get_proximity());
            if((op.get_hue() > 330 && op.get_hue() < 360) && (op.get_proximity() > 160 && op.get_proximity() <= 255)){
                
            setfort(false);
				Scoring_Mech.move(127 *-forw);
                pros::delay(210);
                setfort(true);
                spin(3);
            }
            // else 
        
            // if((op.get_hue() > 220 && op.get_hue() < 257) && (op.get_proximity() > 140 && op.get_proximity() <= 255)){
                
                
			// }

            
        }
    }
    
    });
}

lv_obj_t* image;


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

//lv_obj_t* war;



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
//#define EXAMPLE_SIG 1

ASSET(unc_txt);

void runStop(int y){
    delay(y);
    chassis.cancelAllMotions();
}

void moveBack(bool test){
//     if(test){
//         if(check == 50){
//             Intake.move(-127);
//             pros::delay(100);
//             Intake.move(0);
//             check = 0;
//         }
//         check++;
// }
}

void moveauton(bool test){
    int checker;
    if(test){
        while(test == true){
            if(checker == 90){
                checker = 0;
            }
            if(checker > 75){
                Intake.move(-127);
            }
            else{
            Intake.move(127);
            }
            checker++;

        }
}
}

float f(float t){
    return t / 1.375;
}




void autonomous() {
    //c::lcd_initialize();
        //imu.reset();
        //imu.set_heading(90);

        // chassis.moveToPoint(1, 0, 1500);
        // chassis.turnToPoint(1, 5, 1500, {.maxSpeed = 70});
        //     chassis.turnToPoint(1, -5, 1500, {.maxSpeed = 70});
        //         chassis.turnToPoint(5, 0, 1500, {.maxSpeed = 70});
        // chassis.moveToPoint(2, 0, 1500);


        // for(int i = 0; i < 10; i++){
            
        //     chassis.moveToPoint(0, 0, 1500, {.forwards = false, .maxSpeed = 70});
        //     delay(1000);
        //     chassis.moveToPoint(10, 0, 1500, {.maxSpeed = 70});
        //     delay(1000);
        // }
//         chassis.setPose(0, 0, 90);
//         Intake.move(127);
//         score_toggle.set_value(true);
//         Scoring_Mech.move(127);
//         //chassis.turnToPoint(-25.408, -24.714, 1500, {.maxSpeed = 80});
//         // chassis.turnToHeading(90, 2000);
//         //         chassis.turnToHeading(180, 2000);
//         //                         chassis.turnToHeading(270, 2000);
       
//         //                                                         chassis.moveToPoint(43, -30.5, 1000, {.forwards = false, .maxSpeed = 60});
//         //                                                         delay(50);
//         //                                                                 chassis.moveToPoint(45, -31, 750, {.forwards = false, .maxSpeed = 60} ,false);

//         //                     
//         //                                     score_toggle.set_value(false);

//!

// chassis.setPose(0, 0, 0);

//     chassis.moveToPoint(0, 15, 1500);
//     delay(750);
//     chassis.turnToPoint(20, 15, 2000);
//     delay(750);
//     chassis.turnToPoint(0, 30, 2000);
//     delay(750);
    
    // chassis.turnToHeading(90, 1500, {.maxSpeed = 60});
    // chassis.turnToHeading(180, 1500, {.maxSpeed = 60});
    // chassis.turnToHeading(270, 1500, {.maxSpeed = 60});
    // chassis.turnToHeading(360, 1500, {.maxSpeed = 60});



//!



//!
    while(imu.is_calibrating()){
        delay(1);
    }
    Intake.move(127);
    score_toggle.set_value(true);
    Scoring_Mech.move(110);
       chassis.setPose(0,0, 90); 
           chassis.moveToPoint(15, 0, 700 , {.maxSpeed = 90});

 chassis.turnToPoint(43, -7, 725, {.maxSpeed = 90});
    chassis.moveToPoint(44, -7, 850, {.maxSpeed = 90});
 chassis.turnToPoint(55, -30, 750, {.maxSpeed = 85});
Scoring_Mech.move(0);
 chassis.moveToPoint(60, -24.5, 950, {.maxSpeed = 85});
 delay(100);
  chassis.moveToPoint(42, -5, 950, {.forwards = false, .maxSpeed = 85});
   chassis.turnToPoint(25, -31, 800, {.maxSpeed = 85});
     chassis.moveToPoint(25, -31, 950, {.maxSpeed = 85});
        chassis.turnToPoint(90, -31, 800, {.forwards = false, .maxSpeed = 85});

         chassis.moveToPoint(90, -31, 1000, {.forwards = false, .maxSpeed = 70}, false);
                 chassis.turnToPoint(0, -31, 800, {.forwards = true, .maxSpeed = 85});

        delay(50);
        Scoring_Mech.move(0);
        delay(1);
        Scoring_Mech.move(127);
        score_toggle.set_value(false);
    delay(1300);
    score_toggle.set_value(true);
    Scoring_Mech.move(0);
    delay(1);
    Scoring_Mech.move(100);
    delay(300);
    load = true;
    load_mech.set_value(load);
    load_mech2.set_value(load);
    chassis.setPose(0, -31, 270);
    chassis.turnToPoint(-30, -31, 950, {.maxSpeed = 85});
         chassis.moveToPoint(-30, -31, 1500, {.maxSpeed = 70});
         delay(500);
chassis.turnToPoint(90, -31, 800, {.forwards = false, .maxSpeed = 85});

         chassis.moveToPoint(0, -31, 1000, {.forwards = false, .maxSpeed = 70}, false);
                 chassis.turnToPoint(-30, -31, 800, {.forwards = true, .maxSpeed = 85});

        delay(50);
        Scoring_Mech.move(0);
        delay(1);
        Scoring_Mech.move(127);
        score_toggle.set_value(false);


// chassis.moveToPoint(43, -6, 850, {.forwards = false, .maxSpeed = 85});
//     Scoring_Mech.move(100);

// chassis.turnToPoint(30, -27, 725, {.maxSpeed = 90});
// chassis.moveToPoint(30, -27, 850, {.forwards = true, .maxSpeed = 90});
// //         //chassis.turnToHeading(270, 750, {.maxSpeed = 70});
// //         float offset = 30 - vertical_tracking_wheel.getOffset();
//  delay(50);
//  chassis.turnToPoint(50, -33.5, 1000, {.forwards = false, .maxSpeed = 90});
//  chassis.moveToPoint(44, -33.5, 750, {.forwards = false, .maxSpeed = 90}, false);
//  delay(25);
//    chassis.turnToPoint(0, -33.5, 300, {.forwards = true, .maxSpeed = 90});

//  delay(50);
//  Scoring_Mech.move(0);
//  delay(1);
//  Scoring_Mech.move(127);
//  score_toggle.set_value(false);
//  delay(1300);
//  score_toggle.set_value(true);
//  Scoring_Mech.move(0);
//  delay(1);
//  Scoring_Mech.move(100);
 
//  load = true;
//  load_mech.set_value(load);
//   load_mech2.set_value(load);
//   delay(100);
//   chassis.setPose(0, -33.5, 270);
// chassis.moveToPoint(-30, -33.5, 1000, {.maxSpeed = 65}, false);
// chassis.setPose(-30, -33.5, 270);
// delay(525);
//  chassis.moveToPoint(1, -33.5, 1000, {.forwards = false, .maxSpeed = 70}, false);
// delay(50);
//  score_toggle.set_value(false);
//  Scoring_Mech.move(0);
//  delay(1);
//  Scoring_Mech.move(127);


//chassis.moveToPoint(30, -27, 1000, {.maxSpeed = 85});    
//chassis.moveToPoint(43, -6, 1500, {.maxSpeed = 75});
//!
// chassis.turnToPoint(0, -30, 1000, {.maxSpeed = 85}, false);
// delay(100);
// load = true;
// load_mech.set_value(load);
// load_mech2.set_value(load);
// chassis.moveToPoint(10.5, -31.5, 1600, {.forwards = true, .maxSpeed = 70});
// // delay(50);
// // chassis.moveToPoint(10, -28, 1000, {.forwards = true, .maxSpeed = 60});

// delay(1000);
// // chassis.moveToPoint(40.5, -29, 1000, {.forwards = false, .maxSpeed = 67}, false);
// // delay(50);

// chassis.moveToPoint(42, -31.5, 800, {.forwards = false, .maxSpeed = 70}, false);
// // chassis.moveToPoint(100, -32, 200, {.forwards = false, .maxSpeed = 85}, false);
// // chassis.moveToPoint(100, -25, 200, {.forwards = false, .maxSpeed = 85}, false);

// chassis.cancelAllMotions();

// score_toggle.set_value(false);

//!
                        //chassis.turnToPoint(10, -29, 1000, {.maxSpeed = 50});
                        

//          Scoring_Mech.move(127);
//                          chassis.moveToPoint(17, -29, 2075, {.forwards = true, .maxSpeed = 35});
//                                                 delay(50);
                                            
//                                                 load_mech.set_value(true);
//                                                  load_mech2.set_value(true);
// delay(50);
//                                                   chassis.moveToPoint(12, -29, 2075, {.forwards = true, .maxSpeed = 35});

//         //                // controller.rumble(".");
//         // //delay(850);
//         //                  //       controller.rumble(".");
//         chassis.moveToPoint(24, -29, 1000, {.forwards = false, .maxSpeed = 60});




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





void notColor(){
    //load_mech.set_value(false);
    //load_mech2.set_value(false);
}


void involt(){
                            //Intake.set_voltage_limit_all(1000000/50);

}


void opcontrol() {
    
    runTime();
    cp = 0;
    bool sixseven = false;
	while (true) {
		// get joystick positions
        

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with arcade drive - can change later
        chassis.arcade(leftY, rightX);      
        // Run for 20 ms then update


        
          


        

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            toggle = !toggle;
            score_toggle.set_value(toggle);
            scoring = toggle;
            

        }

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
            load = !load;
            load_mech.set_value(load);
            load_mech2.set_value(load);
            
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
            backshot_mech.set_value(true);
            delay(125);
            park_mech.set_value(true);
            delay(200);
            backshot_mech.set_value(false);
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            sixseven = false;
             backshot_mech.set_value(false);
            //delay(125);
            park_mech.set_value(false);
            
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

        

        // if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        //    autonomous();
        // }
        
        

   
}

                            
        // delay(20);
       
        //!Vision::signature SIG_1  (1, 8453, 10923, 9688, -1767, -463, -1114, 6.100, 0);
    //! vision::signature SIG_2 (2, -4719, -3755, -4236, 6987, 8529, 7758, 7.400, 0);
    //! vision::signature SIG_3 (3, -3751, -2715, -3232, 3083, 4977, 4030, 2.800, 0);
    //! vision::signature SIG_4 (4, 9361, 10591, 9976, -2223, -1123, -1672, 3.000, 0);

    
    


	
}
