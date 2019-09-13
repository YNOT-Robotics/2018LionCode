#include "Robot.h"

void Robot::skills(){
  toggleIntake(1);
  cataDown();
  //go to the first cap intake ball and return to start
  move(-1300,200); //-1300
  wait(1000);
  move(1100,200);  //1000
  slopTurn(-90,100);
  move(1350,200);
  turn(-21,100);
  wait(200);
  fire();
  turn(115,100);
  move(350,200);
  move(-1300,200);
  wait(1000);
  move(1150,200);
  //turn move to and shoot the flag
  slopTurn(-90,100);
  move(1450,200);
  move(-1425,200);
  turn(90,100);
  move(250,200);
  move(-150,150);
  turn(45,100);
  toggleIntake(0);
  move(-550,150);
  move(-100,100);
  toggleIntake(1);
  //move forward turn around flip cap then shoot middle flags  
  move(300,200);
  slopTurn(-195,100);
  toggleFlipper();
  move(625,150);
  toggleFlipper();
  toggleIntake(1);
  wait(200);
  fire();
  ///////PARK///////
  turn(151,100);
  toggleIntake(0);
  move(-1500,200);
  move(-250,50);
  toggleIntake(1);
  wait(300);
  move(200,150);
  toggleIntake(-1);
  move(-600,200);
  turn(-135,100);
  toggleIntake(1);
  move(-850,150);
  wait(500);
  move(200,100);
  turn(10,100);
  fire();
  turn(-160,100);
  move(1400,200);
  turn(-90,100);
  move(1000,200);

  endAuto();
}