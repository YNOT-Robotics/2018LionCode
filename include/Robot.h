
class Robot{
  public:
    Robot(bool);
    void clearAll();
    void start();
    void toggleFlipper();
    void toggleDescorer();
    void OPclear();
    void toggleIntake(double);
    void fire();
    void visionYeet();
    void toggleBlocker();
    void wait(int);
    void oneBall();
    void togglePiston();

    bool lastR2;
    bool lastR1;
    bool lastY;
    bool lastX;
    bool lastB;
    bool intakeOn;

    //auton functions
    void autoInit();
    void cataDown();
    void move(double, int);
    void newMove(double, int);
    void turn(double, int);
    void slopTurn(double, int);
    void capBallIntake();
    void endAuto();

    void auto1();
    void redMid();
    void redFar();
    void blueMid();
    void blueFar();
    void skills();
  private:

    bool auton;
    bool driveOverride = false;
    bool state = false;
    bool catapultOn = true;
    bool descorerOut = false;
    bool unoBall = false;
    bool downPress = false;
    int xPos = 0;
    int yPos = 0;
    int angle = 0;
};


void autonomous(void);
void initialize(void);
void disabled(void);
//void competition_initialize(void);
void opcontrol(void);
int driver(void);
void resetScreen();
void nl();
int autoSelect();