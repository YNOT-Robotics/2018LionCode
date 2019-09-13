
#ifndef Robots
#define Robots

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <iostream>

#include "v5.h"
#include "v5_vcs.h"


vex::brain Brain;

vex::motor rightF1 = vex::motor(vex::PORT11,false);
vex::motor rightF2 = vex::motor(vex::PORT18,false);
vex::motor rightB = vex::motor(vex::PORT2,true);
vex::motor leftF1 = vex::motor(vex::PORT12,vex::gearSetting::ratio18_1,true);
vex::motor leftF2 = vex::motor(vex::PORT16,vex::gearSetting::ratio18_1,true);
vex::motor leftB = vex::motor(vex::PORT3,vex::gearSetting::ratio18_1,false);
vex::motor catapult = vex::motor(vex::PORT13,vex::gearSetting::ratio36_1, true);
vex::motor catapult2 = vex::motor(vex::PORT14,vex::gearSetting::ratio36_1,false);
vex::motor roller = vex::motor(vex::PORT1,vex::gearSetting::ratio6_1,false);
vex::motor uptake = vex::motor(vex::PORT10,vex::gearSetting::ratio6_1,true);
vex::motor flipper = vex::motor(vex::PORT17,vex::gearSetting::ratio18_1,false);
vex::motor descorer = vex::motor(vex::PORT15,vex::gearSetting::ratio18_1,false);


vex::controller Grant = vex::controller();

vex::bumper Cbutton = vex::bumper(Brain.ThreeWirePort.F);
vex::digital_out Intake = vex::digital_out(Brain.ThreeWirePort.E);
vex::gyro gyro = vex::gyro(Brain.ThreeWirePort.A);
vex::line backBall = vex::line(Brain.ThreeWirePort.C);
vex::line frontBall = vex::line(Brain.ThreeWirePort.B);
vex::digital_out blocker = vex::digital_out(Brain.ThreeWirePort.D);
vex::vision VisionLion = vex::vision(vex::PORT19);

/*
void autonomous(void);
void initialize(void);
void disabled(void);
//void competition_initialize(void);
void opcontrol(void);
*/

#endif