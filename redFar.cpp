#include "Robot.h"

void Robot::redFar(){
  toggleIntake(1);
  wait(200);
  cataDown();
  //go to the first cap intake ball and return to start
  move(-1250,200);
  wait(1000);
  move(950,200);
  //turn and shoot the flag and drop intake
  turn(-111,100);
  move(-200,100);
  wait(200);
  fire();
  //turn to move and toggle low flag and line up for 2 ball intake
  move(200,100);
  turn(203,100);
  move(-1300,200);
  move(1240,200);
  turn(-90,100);
  move(400,150);
  move(-150,100);
  turn(53,100);
  //move to the cap and do 2 ball intake
  move(-400,150);
  toggleIntake(0);
  move(-600,75);
  capBallIntake();
  //back away turn around and flip the cap
  move(300,150);
  turn(190,100);
  toggleFlipper();
  move(900,150);
  toggleFlipper();
  move(-125,100);
  //turn to the target are move into it and shoot the flags back to our color
  turn(-41,100);
  move(450,150);
  fire();
  wait(200);
  ///////PARK///////
  move(-500,100);
  turn(-98,100);
  move(2100,200);
}