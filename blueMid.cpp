#include "Robot.h"

void Robot::blueMid(){
  toggleIntake(1);
  wait(200);
  cataDown();
  //go to the first cap intake ball and return to start
  move(-1300,200);
  wait(1000);
  move(1350,200);
  move(-200,100);
  //turn move to and shoot the flag
  turn(92,100);
  wait(500);
  fire();
  //turn move to and toggle low flag then line up for 2 ball intake
  turn(-180,100);
  move(-1355,200);
  move(1400,200);
  turn(90,100);
  move(350,200);
  move(-150,100);
  turn(-47,100);
  //move to cap and do 2 ball intake
  toggleIntake(0);
  move(-600,150);
  move(-400,50);
  capBallIntake();
  //move forward turn around flip cap then shoot middle flags  
  move(300,200);
  turn(-195,100);
  toggleFlipper();
  move(900,150);
  toggleFlipper();
  move(-500,150);
  turn(-13,100);
  wait(200);
  fire();
  ///////PARK///////
  turn(65,100);
  move(400,100);
  turn(90,100);
  move(1600,200);

  endAuto();
}