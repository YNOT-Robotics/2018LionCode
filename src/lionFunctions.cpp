#include "vex.h"
#include "Robot.h"

Robot::Robot(bool autonomous){
  auton = autonomous;
  if(auton){
    autoInit();
  }else{
    start();
  }
}

void Robot::wait(int time){
  vex::task::sleep(time);
}

int driver(void){
  double power, turn;
  std::string errorCheck;
  while(true){
    power = 200*(Grant.Axis3.value()/127.0);
    turn = 200*((Grant.Axis1.value()/127.0));
    if(fabs(power) < 8){
      power = 0;
    }
    if(fabs(turn) < 7 ){
      turn = 0;
    }
    rightF1.spin(vex::fwd, power-turn, vex::rpm);
    rightF2.spin(vex::fwd,power-turn, vex::rpm);
    rightB.spin(vex::fwd,power-turn, vex::rpm);
    leftB.spin(vex::fwd,power+turn, vex::rpm);
    leftF1.spin(vex::fwd,power+turn, vex::rpm);
    leftF2.spin(vex::fwd,power+turn, vex::rpm);


    vex::task::sleep(10);
  }
}
void Robot::start(){
  state = true;
  intakeOn = true;
  Intake.set(state);
  roller.spin(vex::fwd,100, vex::pct);
  uptake.spin(vex::fwd,100, vex::pct);
  descorer.setBrake(vex::coast);
  flipper.setBrake(vex::hold);
  catapult.setBrake(vex::hold);
  catapult2.setBrake(vex::hold);
  rightF1.setBrake(vex::coast);
  rightF2.setBrake(vex::coast);
  rightB.setBrake(vex::coast);
  leftF1.setBrake(vex::coast);
  leftF2.setBrake(vex::coast);
  leftB.setBrake(vex::coast);
}
void Robot::clearAll(){
  flipper.spin(vex::fwd,50, vex::rpm);
  descorer.spin(vex::fwd,50, vex::rpm);
  Intake.set(state);
  bool go = true;
  wait(150);
  while(go){
    go = false;
    if(flipper.velocity(vex::rpm) > 5){
      go = true;
    }else{
      flipper.spin(vex::fwd,0, vex::rpm);
    }
    if(descorer.velocity(vex::rpm) > 5){
      go = true;
    }else{
      descorer.spin(vex::fwd,0, vex::rpm);
    }
  }
  descorer.resetRotation();
  flipper.resetRotation();
}

void Robot::OPclear(){
  if(Grant.ButtonA.pressing()){
    clearAll();
  }
}

void Robot::toggleFlipper(){
  if(auton){
    if(flipper.rotation(vex::deg) < -50){
      flipper.rotateTo(0, vex::deg, 200, vex::rpm);
    }else{
      flipper.rotateTo(-125, vex::deg, 100, vex::rpm);
    }
  }else{
    if(Grant.ButtonR2.pressing() && !lastR2){
      lastR2 = true;
      if(flipper.rotation(vex::deg) < -50){
        flipper.rotateTo(0, vex::deg, 200, vex::rpm);
      }else{
        flipper.rotateTo(-135, vex::deg, 100, vex::rpm);
      }
    }
    if(Grant.ButtonR2.pressing()){
      lastR2 = false;
    }
  }
}

void Robot::toggleDescorer(){
  if(auton){
    if(descorer.rotation(vex::deg) < -50){
      descorer.rotateTo(-10, vex::deg, 100, vex::rpm);
      descorer.setBrake(vex::coast);
    }else{
      descorer.rotateTo(-325, vex::deg, 100, vex::rpm);
      descorer.setBrake(vex::hold);
    }
  }else{
    if(Grant.ButtonR1.pressing() && !lastR1){
      lastR1 = true;
      if(descorer.rotation(vex::deg) < -100){
        descorer.rotateTo(-10, vex::deg, 100, vex::rpm);
        descorerOut = false;
      }else{
        descorer.rotateTo(-330, vex::deg, 100, vex::rpm);
        descorerOut = true;
      }
    }
    if(!Grant.ButtonR1.pressing()){
      lastR1 = false;
    }
  }
}



void Robot::toggleIntake(double direction = 0){
  if(auton){
    if(direction == 0){
      state = false;
      Intake.set(state);
      roller.spin(vex::fwd,0, vex::rpm);
      uptake.spin(vex::fwd,0, vex::rpm);
    }else if(direction > 0){
      state = true;
      Intake.set(state);
      vex::task::sleep(200);
      roller.spin(vex::fwd,600, vex::rpm);
      uptake.spin(vex::fwd,600, vex::rpm);
    }else{
      state = true;
      Intake.set(state);
      vex::task::sleep(200);
      roller.spin(vex::fwd,-600, vex::rpm);
      uptake.spin(vex::fwd,-600, vex::rpm);
    }
  }else{
    if(Grant.ButtonY.pressing() && !lastY){
      lastY = true;     //new press
      state = !state;
      roller.spin(vex::fwd,(int)state * 600, vex::rpm);
      uptake.spin(vex::fwd,600, vex::rpm);
    }
    if(!Grant.ButtonY.pressing()){
      lastY = false;
    }
    if(Grant.ButtonX.pressing() && !lastX){
      lastX = true;
      intakeOn = !intakeOn;
      roller.spin(vex::fwd,(int)intakeOn * 600, vex::rpm);
      uptake.spin(vex::fwd,(int)intakeOn * 600, vex::rpm);
    }
    if(!Grant.ButtonX.pressing()){
      lastY = false;
    }
    if(state && intakeOn){
      if(Grant.ButtonRight.pressing()){
        roller.spin(vex::fwd,-600, vex::rpm);
        uptake.spin(vex::fwd,-600, vex::rpm);
      }else if(Grant.ButtonL2.pressing()){
        roller.spin(vex::fwd,-250, vex::rpm);
        uptake.spin(vex::fwd,-600, vex::rpm);
      }else{
        
        roller.spin(vex::fwd,600, vex::rpm);
        uptake.spin(vex::fwd,600, vex::rpm);
      }
    }
  }
}

void Robot::fire(){
  if(auton){
    while(!Cbutton.pressing()){
      catapult.spin(vex::fwd,200, vex::rpm);
      catapult2.spin(vex::fwd,200, vex::rpm);
      vex::task::sleep(5);
    }
    while(Cbutton.pressing()){
      catapult.spin(vex::fwd,200, vex::rpm);
      catapult2.spin(vex::fwd,200, vex::rpm);
      vex::task::sleep(5);
    }
    vex::task::sleep(300);
    while(!Cbutton.pressing()){
      catapult.spin(vex::fwd,200, vex::rpm);
      catapult2.spin(vex::fwd,200, vex::rpm);
      vex::task::sleep(5);
    }
    catapult.spin(vex::fwd,0, vex::rpm);
    catapult2.spin(vex::fwd,0, vex::rpm);
    wait(200);
  }else{
    if(catapultOn){
      if(!Cbutton.pressing()){
        catapult.spin(vex::fwd,200, vex::rpm);
        catapult2.spin(vex::fwd,200, vex::rpm);
      }else if(Grant.ButtonL1.pressing()){
        catapult.spin(vex::fwd,200, vex::rpm);
        catapult2.spin(vex::fwd,200, vex::rpm);
      }else{
        catapult.spin(vex::fwd,0, vex::rpm);
        catapult2.spin(vex::fwd,0, vex::rpm);
      }
    }
    if(Grant.ButtonB.pressing() && !lastB){
      lastB = true;
      catapultOn = !catapultOn;
      if(catapultOn){
        catapult.setBrake(vex::hold);
        catapult2.setBrake(vex::hold);
        catapult.spin(vex::fwd,200, vex::rpm);
        catapult2.spin(vex::fwd,200, vex::rpm);
      }else{
        catapult.setBrake(vex::coast);
        catapult2.setBrake(vex::coast);
        catapult.spin(vex::fwd,0, vex::rpm);
        catapult2.spin(vex::fwd,0, vex::rpm);
      }
    }
    if(!Grant.ButtonB.pressing()){
      lastB = false;
    }
  }
}

void Robot::togglePiston(){
  blocker.set(true);
  wait(200);
  blocker.set(false);
}
void Robot::oneBall(){
  if(Grant.ButtonDown.pressing() && !downPress){
    downPress = true;
    unoBall = !unoBall;
  }else{
    downPress = false;
  }
  if(unoBall){
    if(backBall.value(vex::analogUnits::mV) < 2700 || frontBall.value(vex::analogUnits::mV) < 2700){
      blocker.set(true);
    }else{
      blocker.set(false);
    }
  }else{
    blocker.set(false);
  }
}

void Robot::visionYeet(){
  
}

//////////AUTONOMOUS FUNCTIONS//////////

void Robot::autoInit(){
  rightF1.resetRotation();
  rightF2.resetRotation();
  rightB.resetRotation();
  leftF1.resetRotation();
  leftF2.resetRotation();
  leftB.resetRotation();

  rightF1.setBrake(vex::hold);
  rightF2.setBrake(vex::hold);
  rightB.setBrake(vex::hold);
  leftF1.setBrake(vex::hold);
  leftF2.setBrake(vex::hold);
  leftB.setBrake(vex::hold);
}

void Robot::cataDown(){
  while(!Cbutton.pressing()){
    catapult.spin(vex::fwd,100, vex::rpm);
    catapult2.spin(vex::fwd,100, vex::rpm);
    vex::task::sleep(10);
  }
  catapult.spin(vex::fwd,0, vex::rpm);
  catapult2.spin(vex::fwd,0, vex::rpm);
  catapult.setBrake(vex::hold);
  catapult2.setBrake(vex::hold);

}
void Robot::newMove(double distance, int speed){
  leftF1.resetRotation();
  leftF2.resetRotation();
  leftB.resetRotation();
  rightF1.resetRotation();
  rightF2.resetRotation();
  rightB.resetRotation();
  printf("Starting Move\n");
  double maxSpeed = speed;
  double leftAvg = (leftF1.rotation(vex::deg) + leftB.rotation(vex::deg)) / 2;
  double rightAvg = (rightF1.rotation(vex::deg) + rightB.rotation(vex::deg)) / 2;
  double targetLeft = distance + leftAvg;
  double targetRight = distance + rightAvg;
  double toTargetLeft = distance;
  double toTargetRight = distance;
  double toTargetAvg = distance;
  double leftSpeed = 0;
  double rightSpeed = 0;
  bool accel = true;
  bool deccel = false;
  int dir = distance/fabs(distance);
  double accelDis;
  int agg = 5;
  double startSpeed = 20;
  double theSpeed = startSpeed;
  double rampSpeed = 10 * dir;
  printf("\n\nNext Run\n\n");

  while(fabs(toTargetLeft) > 10 && fabs(toTargetRight) > 10){
    leftAvg = (leftF1.rotation(vex::deg) + leftB.rotation(vex::deg)) / 2;
    rightAvg = (rightF1.rotation(vex::deg) + rightB.rotation(vex::deg)) / 2;
    toTargetLeft = targetLeft - leftAvg;
    toTargetRight = targetRight - rightAvg;
    toTargetAvg = (toTargetLeft + toTargetRight) / 2;

    if(accel){
      printf("sp:%f ",theSpeed);
      if(fabs(theSpeed)<fabs(maxSpeed)){
        theSpeed += rampSpeed;
      }else{
        accel = false;
        accelDis = distance - toTargetAvg;
        printf("%f",accelDis);
        printf(" = accell dis\n\n");
      }
      printf("a:%f b:%f",toTargetAvg,(distance/2));
      if(fabs(toTargetAvg)<fabs(distance/2)){
        printf("accell half\n\n");
        deccel = true;
        accel = false;
        accelDis = distance-toTargetAvg;
      }
    }else if(deccel){
      printf("dec:%f",theSpeed);
      if(fabs(theSpeed) > .1*maxSpeed){
        theSpeed -= rampSpeed;
      }
    }else{
      printf("Yeet");
      if(toTargetAvg>(accelDis)){
        theSpeed = maxSpeed;
      }else{
        deccel = true;
      }
    }
    
    if(fabs(toTargetLeft) > fabs(toTargetRight)+20 || fabs(toTargetRight) > fabs(toTargetLeft) + 20){
      leftSpeed = theSpeed + (toTargetLeft - toTargetRight) / agg;
      rightSpeed = theSpeed - (toTargetLeft - toTargetRight) / agg;
    }else{
      leftSpeed = theSpeed;
      rightSpeed = theSpeed;
    }
    leftF1.spin(vex::fwd,leftSpeed, vex::rpm);
    leftF2.spin(vex::fwd,leftSpeed, vex::rpm);
    leftB.spin(vex::fwd,leftSpeed, vex::rpm);
    rightF1.spin(vex::fwd,rightSpeed, vex::rpm);
    rightF2.spin(vex::fwd,rightSpeed, vex::rpm);
    rightB.spin(vex::fwd,rightSpeed, vex::rpm);
    vex::task::sleep(50);
  }
  leftF1.spin(vex::fwd,0, vex::rpm);
  leftF2.spin(vex::fwd,0, vex::rpm);
  leftB.spin(vex::fwd,0, vex::rpm);
  rightF1.spin(vex::fwd,0, vex::rpm);
  rightF2.spin(vex::fwd,0, vex::rpm);
  rightB.spin(vex::fwd,0, vex::rpm);
  wait(200);

}

void Robot::move(double distance, int speed){
  double leftAvg = (leftF1.rotation(vex::deg) + leftB.rotation(vex::deg)) / 2;
  double rightAvg = (rightF1.rotation(vex::deg) + rightB.rotation(vex::deg)) / 2;
  double targetLeft = distance + leftAvg;
  double targetRight = distance + rightAvg;
  double toTargetLeft = distance;
  double toTargetRight = distance;
  double toTargetAvg = distance;
  double agg = 5;
  double leftSpeed = 0;
  double rightSpeed = 0;
  double adjDistance = fabs(distance / 2);
  int dir = distance / fabs(distance);


  while(fabs(toTargetLeft) > 10 && fabs(toTargetRight) > 10){
    leftAvg = (leftF1.rotation(vex::deg) + leftB.rotation(vex::deg)) / 2;
    rightAvg = (rightF1.rotation(vex::deg) + rightB.rotation(vex::deg)) / 2;
    toTargetLeft = targetLeft - leftAvg;
    toTargetRight = targetRight - rightAvg;
    toTargetAvg = (toTargetLeft + toTargetRight) / 2;

    

    /////////////Do Not Change this////////////
    if(fabs(distance) >= 700){
      agg = 600;
      if(fabs(toTargetAvg) < 400){
        leftSpeed = speed * ((toTargetAvg / 450) + (dir * .06) + ((toTargetLeft - toTargetRight) / agg));
        rightSpeed = speed * ((toTargetAvg / 450) + (dir * .06) - ((toTargetLeft - toTargetRight) / agg));
      }else if(fabs(distance - toTargetAvg) < 300){
        leftSpeed = speed * (((distance - toTargetAvg) / 500) + (dir * .35) + ((toTargetLeft - toTargetRight) / agg));
        rightSpeed = speed * (((distance - toTargetAvg) / 500) + (dir * .35) - ((toTargetLeft - toTargetRight) / agg));
      }else{
        leftSpeed = speed * ((dir * .95) + ((toTargetLeft - toTargetRight) / agg));
        rightSpeed = speed * ((dir * .95) - ((toTargetLeft - toTargetRight) / agg));
      }
    }else{
      agg = 600;
      if(fabs(toTargetAvg) < adjDistance){
        leftSpeed = speed * ((toTargetAvg / 450) + (dir * .25) + ((toTargetLeft - toTargetRight) / agg));
        rightSpeed = speed * ((toTargetAvg / 450) + (dir * .25) - ((toTargetLeft - toTargetRight) / agg));
      }else if(fabs(distance - toTargetAvg) < adjDistance){
        leftSpeed = speed * (((distance - toTargetAvg) / 500) + (dir * .35) + ((toTargetLeft - toTargetRight) / agg));
        rightSpeed = speed * (((distance - toTargetAvg) / 500) + (dir * .35) - ((toTargetLeft - toTargetRight) / agg));
      }else{
        leftSpeed = speed * ((dir * .95) + ((toTargetLeft - toTargetRight) / agg));
        rightSpeed = speed  * ((dir * .95) - ((toTargetLeft - toTargetRight) / agg));
      }
    }
    leftF1.spin(vex::fwd,leftSpeed, vex::rpm);
    leftF2.spin(vex::fwd,leftSpeed, vex::rpm);
    leftB.spin(vex::fwd,leftSpeed, vex::rpm);
    rightF1.spin(vex::fwd,rightSpeed, vex::rpm);
    rightF2.spin(vex::fwd,rightSpeed, vex::rpm);
    rightB.spin(vex::fwd,rightSpeed, vex::rpm);
    vex::task::sleep(2);
  }
  leftF1.spin(vex::fwd,0, vex::rpm);
  leftF2.spin(vex::fwd,0, vex::rpm);
  leftB.spin(vex::fwd,0, vex::rpm);
  rightF1.spin(vex::fwd,0, vex::rpm);
  rightF2.spin(vex::fwd,0, vex::rpm);
  rightB.spin(vex::fwd,0, vex::rpm);
  vex::task::sleep(250);
}

void Robot::turn(double angle, int speed){
  int dir = angle / fabs(angle);
  //double turn90 = 353 - (29.0 * fabs(angle / 90.0));  //90 = 297  90 = 290
  double turn90 = 300 - (10.0 * fabs(angle / 90));
  double distance = (angle * turn90) / 90.0;
  if(dir == -1){
    distance *= .97;
  }
  
  double leftAvg = leftF1.rotation(vex::deg);
  double rightAvg = rightF1.rotation(vex::deg);
  double targetLeft = -distance + leftAvg;
  double targetRight = distance + rightAvg;
  double toTargetLeft = -distance;
  double toTargetRight = distance;
  double leftSpeed = 0;
  double rightSpeed = 0;
  

  while(fabs(toTargetLeft) > 10 && fabs(toTargetRight) > 10){
    leftAvg = leftF1.rotation(vex::deg);
    rightAvg = rightF1.rotation(vex::deg);
    toTargetLeft = targetLeft - leftAvg;
    toTargetRight = targetRight - rightAvg;

    if(fabs(toTargetLeft) < 50){
      leftSpeed = (fabs(toTargetLeft / 125) + .6) * -speed * dir;
    }else if(fabs(distance - toTargetLeft) < 50){
      leftSpeed = (.6 + fabs((distance - toTargetLeft)/125)) * -speed * dir;
    }else{
      leftSpeed = -speed * dir;
    }
    if(fabs(toTargetRight) < 50){
      rightSpeed = (fabs(toTargetRight / 125) + .6) * speed * dir;
    }else if(fabs(distance - toTargetRight) < 50){
      rightSpeed = (.6 + fabs((distance - toTargetRight)/125)) * speed * dir;
    }else{
      rightSpeed = speed * dir;
    }
    leftF1.spin(vex::fwd,leftSpeed, vex::rpm);
    leftF2.spin(vex::fwd,leftSpeed, vex::rpm);
    leftB.spin(vex::fwd,leftSpeed, vex::rpm);
    rightF1.spin(vex::fwd,rightSpeed, vex::rpm);
    rightF2.spin(vex::fwd,rightSpeed, vex::rpm);
    rightB.spin(vex::fwd,rightSpeed, vex::rpm);
    vex::task::sleep(2);
  }
  leftF1.spin(vex::fwd,0, vex::rpm);
  leftF2.spin(vex::fwd,0, vex::rpm);
  leftB.spin(vex::fwd,0, vex::rpm);
  rightF1.spin(vex::fwd,0, vex::rpm);
  rightF2.spin(vex::fwd,0, vex::rpm);
  rightB.spin(vex::fwd,0, vex::rpm);
  vex::task::sleep(200);
}

void Robot::capBallIntake(){
  move(120,50);
  Intake.set(1);

  wait(50);
  roller.spin(vex::directionType::fwd);
  roller.setVelocity(100,vex::velocityUnits::pct);
  uptake.spin(vex::directionType::fwd);
  uptake.setVelocity(100,vex::velocityUnits::pct);
    
  move(125,160);
  wait(100);
  roller.setVelocity(0,vex::velocityUnits::pct);
    
  wait(200);
  Intake.set(0);
  roller.setVelocity(100,vex::velocityUnits::pct);
  wait(300);
  Intake.set(1);
  move(50,50);
  roller.setVelocity(70,vex::velocityUnits::pct);
  wait(400);
  roller.setVelocity(-60,vex::velocityUnits::pct);
  uptake.setVelocity(-60,vex::velocityUnits::pct);
  wait(155);
  roller.setVelocity(70,vex::velocityUnits::pct);
  uptake.setVelocity(70,vex::velocityUnits::pct);
    
  wait(300);
  move(-200,50);
  roller.setVelocity(100,vex::velocityUnits::pct);
  uptake.setVelocity(100,vex::velocityUnits::pct);

    
    
    
}

void Robot::endAuto(){
  rightF1.setBrake(vex::coast);
  rightF2.setBrake(vex::coast);
  rightB.setBrake(vex::coast);
  leftF1.setBrake(vex::coast);
  leftF2.setBrake(vex::coast);
  leftB.setBrake(vex::coast);
  catapult.setBrake(vex::coast);
  catapult2.setBrake(vex::coast);
}

void Robot::slopTurn(double angle, int speed){
  int dir = angle / fabs(angle);
  move(dir * 90,speed);
  wait(100);
  //double turn90 = 353 - (29.0 * fabs(angle / 90.0));  //90 = 297  //180 = 274
  double turn90 = 286 - (6.0 * fabs(angle/90.0));
  double distance = (angle * turn90) / 90.0;
  if(dir == -1){
    distance *= .98;
  }
  double leftAvg = leftF1.rotation(vex::deg);
  double rightAvg = rightF1.rotation(vex::deg);
  double targetLeft = -distance + leftAvg;
  double targetRight = distance + rightAvg;
  double toTargetLeft = -distance;
  double toTargetRight = distance;
  double leftSpeed = 0;
  double rightSpeed = 0;
  

  while(fabs(toTargetLeft) > 10 && fabs(toTargetRight) > 10){
    leftAvg = leftF1.rotation(vex::deg);
    rightAvg = rightF1.rotation(vex::deg);
    toTargetLeft = targetLeft - leftAvg;
    toTargetRight = targetRight - rightAvg;

    if(fabs(toTargetLeft) < 50){
      leftSpeed = (fabs(toTargetLeft / 125) + .6) * -speed * dir;
    }else if(fabs(distance - toTargetLeft) < 50){
      leftSpeed = (.6 + fabs((distance - toTargetLeft)/125)) * -speed * dir;
    }else{
      leftSpeed = -speed * dir;
    }
    if(fabs(toTargetRight) < 50){
      rightSpeed = (fabs(toTargetRight / 125) + .6) * speed * dir;
    }else if(fabs(distance - toTargetRight) < 50){
      rightSpeed = (.6 + fabs((distance - toTargetRight)/125)) * speed * dir;
    }else{
      rightSpeed = speed * dir;
    }
    leftF1.spin(vex::fwd,leftSpeed, vex::rpm);
    leftF2.spin(vex::fwd,leftSpeed, vex::rpm);
    leftB.spin(vex::fwd,leftSpeed, vex::rpm);
    rightF1.spin(vex::fwd,rightSpeed, vex::rpm);
    rightF2.spin(vex::fwd,rightSpeed, vex::rpm);
    rightB.spin(vex::fwd,rightSpeed, vex::rpm);
    vex::task::sleep(2);
  }
  leftF1.spin(vex::fwd,0, vex::rpm);
  leftF2.spin(vex::fwd,0, vex::rpm);
  leftB.spin(vex::fwd,0, vex::rpm);
  rightF1.spin(vex::fwd,0, vex::rpm);
  rightF2.spin(vex::fwd,0, vex::rpm);
  rightB.spin(vex::fwd,0, vex::rpm);
  vex::task::sleep(200);
  move(dir*90,speed);
  wait(100);
}


/////////AUTON SELECT///////////
void resetScreen(){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
}
void nl(){
    Brain.Screen.newLine();
}
int autoSelect(){
  int chose;
  resetScreen();
  for(int x = 0; x<4; x++){
    Brain.Screen.drawRectangle((x*120)+1,(0*120)+1,118,118,vex::color::red);
  }
  for(int x = 0; x<3; x++){
    Brain.Screen.drawRectangle((x*120)+1,(1*120)+1,118,118,vex::color::blue);
  }
  Brain.Screen.setPenColor(vex::color::cyan);
  nl();
  nl();
  nl();
  Brain.Screen.print("  Red Mid   ");
  Brain.Screen.print("  Red Back  ");
  Brain.Screen.print("   Skills   ");
  Brain.Screen.print("    Test    ");
  nl();
  nl();
  nl();
  nl();
  nl();
  Brain.Screen.print("  Blue Mid  ");
  Brain.Screen.print(" Blue Back ");
  Brain.Screen.print("            ");
  Brain.Screen.print("            ");
  int xSelect,ySelect;
  while(!Brain.Screen.pressing()){
    Grant.rumble("..-..-");
  }
  xSelect = Brain.Screen.xPosition();
  ySelect = Brain.Screen.yPosition();
  while(Brain.Screen.pressing()){}
  if(ySelect < 120){
    if(xSelect < 120){
      chose = 1;
    }else if(xSelect < 240){
      chose =  2;
    }else if(xSelect < 360){
      chose = 3;
    }else{
      chose = 4;
    }
  }else{
    if(xSelect < 120){
      chose = 5;
    }else if(xSelect < 240){
      chose = 6;
    }else if(xSelect < 360){
      chose = 7;
    }else{
      chose = 8;
    }
  }
  resetScreen();
  Brain.Screen.print("Selected Option %d",chose);
  return chose;
}