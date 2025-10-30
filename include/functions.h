#pragma once



extern float t;
extern float k;
extern float h;
extern float j;
extern int cp;
extern int check;
extern bool load;
extern bool toggle;
extern bool scoring;
extern bool park;
extern bool backshot;
extern int forw;
extern bool fort;
extern bool runcolor;
enum class COLOR {
    RED,
    BLUE
};
void runTime();
void forwSet(int i);
void setfort(bool forrt);
void spin(int f);
void ourColor();
void runStop(int y);
void moveBack(bool test);
void moveauton(bool test);
float f(float t);
void cycle_intake(int volts);
void score_long(int volts);
void score_mid(int volts);
void score_low(int volts);
void stop_cycle();
void sort_red();
void sort_blue();
void alliance_red();
void alliance_blue();