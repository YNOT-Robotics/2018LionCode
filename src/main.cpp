#include "Robot.h"
#include "v5.h"
#include "v5_vcs.h"


using namespace vex;

vex::competition Competition;

int choice  = 4;

void pre_auton( void ) {
  Robot Lion(true);
  Lion.clearAll();
  choice = autoSelect();
}

void autonomous( void ) {
  Robot Lion(true);
  if(choice == 1){
    Lion.redMid();
  }
  if(choice == 2){
    Lion.redFar();
  }
  if(choice == 3){
    Lion.skills();
  }
  if(choice == 4){
    Lion.auto1();
  }
  if(choice == 5){
    Lion.blueMid();
  }
  if(choice == 6){
    Lion.blueFar();
  }

}

void usercontrol( void ) {
 Robot Lion(false);
 Lion.clearAll();
 vex::task D = vex::task(driver);
   while (true) {
     Lion.toggleFlipper();
     Lion.toggleDescorer();
     Lion.toggleIntake(0);
     Lion.OPclear();
     Lion.fire();
     Lion.oneBall();
     vex::task::sleep(2);
   }
}

int main() {

    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    pre_auton();
                      
    while(1) {
      vex::task::sleep(100);
    }    
       
}