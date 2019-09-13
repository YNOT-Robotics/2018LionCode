#include "Robot.h"

void Robot::redMid(){
  toggleIntake(1);
  wait(200);
  cataDown();
  //go to the first cap intake ball and return to start
  move(-1300,200);
  wait(1000);
  move(1050,200);
  //turn move to and shoot the flag
  turn(-108,100);
  wait(500);
  fire();
  //turn move to and toggle low flag then line up for 2 ball intake
  turn(17,100);
  move(1350,200);
  move(-2350,200);
  move(1000,200);
  slopTurn(136,100);
  toggleIntake(0);
  //move to cap and do 2 ball intake
  move(-500,150);
  move(-250,50);
  toggleIntake(1);
  //move forward turn around flip cap then shoot middle flags  
  move(300,75);
  slopTurn(-195,100);
  toggleFlipper();
  move(400,150);
  toggleFlipper();
  wait(200);
  toggleIntake(1);
  turn(10,100);
  wait(200);
  fire();
  wait(200);
  ///////PARK///////
  turn(-45,100);
  move(400,200);
  slopTurn(-90,100);
  //move(2000,200);

  endAuto();
}