#include "Robot.h"

void Robot::blueFar(){
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
  turn(-46,100);
  //move to cap and do 2 ball intake
  toggleIntake(0);
  move(-600,150);
  move(-400,50);
  capBallIntake();
  //back away turn around and flip the cap
  move(300,150);
  turn(-195,100);
  toggleFlipper();
  move(1150,150);
  toggleFlipper();
  move(-100,100);
  turn(37,100);
  move(350,150);
  wait(200);
  fire();
  move(-500,200);
  turn(120,100);
  move(2000,200);
  /*
  turn(-55,100);
  move(-500,150);
  turn(-105,100);
  toggleFlipper();
  move(900,150);   //800
  move(-50,75);  //grant
  toggleFlipper();
  move(50, 75); //grant
  turn(-90, 100);// grant
  move(400, 75); //grant
  move(-100,60); //grant
  turn(90,100); //grant
  move(150,100);  //300
  turn(-25,100); 
  //turn to the target are move into it and shoot the flags back to our color
  wait(500);
  fire();
  wait(200);*/

  ///////PARK///////
  /*
  move(-400,200);
  turn(120,100);
  move(2000,200);
  */
}