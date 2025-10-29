#include "functions.h"
#include "pros/rtos.hpp"
#include "config.h"

using namespace pros;
using namespace lemlib;




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
            if((op.get_hue() > 220 && op.get_hue() < 257) && (op.get_proximity() > 140 && op.get_proximity() <= 255)){
                
            setfort(false);
				Scoring_Mech.move(127 *-forw);
                pros::delay(160);
                setfort(true);
                spin(3);
            }
            // else 
        
            // if((op.get_hue() > 220 && op.get_hue() < 257) && (op.get_proximity() > 140 && op.get_proximity() <= 255)){
                
                //(op.get_hue() > 300 && op.get_hue() < 360) && (op.get_proximity() > 160 && op.get_proximity() <= 255)
			// }

            
        }
    }
    
    });
}


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