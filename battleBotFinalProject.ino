// Demo code taken from WWFirst, further modified by @Kai5126

//Necessary libraries 
#include <Servo.h>
#include "elegoo-car.h"
#include "DriverStation.h"

// Used to check if autonomous mode is active
bool autonomousMode = true; 

// Create the ElegooCar object named myCar
ElegooCar myCar;
// Create the DriverStation object named ds
DriverStation ds;

// Speeds to set the motor to (0-255)
#define AUTO_FWD_SPEED 154
#define AUTO_FULL_SPEED 255
#define AUTO_MID_SPEED 200
#define FORWARD_SPEED 255
#define TURN_SPEED 64

// Joystick values close to 0 that we'll ignore
#define DEADBAND 16 

// Creates 4 servos to control the robot arm
Servo myServo;
Servo myServo2;
Servo myServo3;
Servo myServo4;

// Create default servo position value
int servoDefault = 90;

// Sets variables the servo uses to move at a default of 90 
int servoMover = 90;
int servoMover2 = 90;
int servoMover3 = 90;
int servoMover4 = 90;

void setup() {
 /* Put your setup code here, to run once:
  * The current setup here is initializing the console and attaching the servo pins
  * As well as setting the servo to default degree value
  */
  Serial.begin( 115200 );
  Serial.println( "Ready..." );
  Serial.println("lol im going to eat a servo motor");
  myServo.attach( c_u8ServoPin );
  myServo2.attach(c_u8ServoPin2);
  myServo3.attach(c_u8ServoPin3);
  myServo4.attach(c_u8ServoPin4);
  myServo.write(servoDefault); 
  myServo2.write(servoDefault);
  myServo3.write(servoDefault);
  myServo4.write(servoDefault);
}

 /* Autonomous is called 10 times per second during Autonomous mode.
  * This function must not block as new data is received every 100ms
  * Will be used to drive to zone D while picking up multiple cups
  * Current auto normally gets 6 cups - with 2 in starting zone upright
  * Possibly even get 7 or 8 depending on starting position 
  * Could get more than 8 by extending the code further
  * since this auto takes under 15 seconds
  */  
void autonomous(){
  int curTime = ds.getStateTimer();
  if (autonomousMode == true){
    myCar.setSpeed(-AUTO_FWD_SPEED, -AUTO_FWD_SPEED);
    delay(150);
    myCar.setSpeed(AUTO_FULL_SPEED, -AUTO_FULL_SPEED);
    delay(350);
    myCar.setSpeed(-AUTO_FWD_SPEED, -AUTO_FWD_SPEED);
    delay(500);
    myCar.setSpeed(0,0);
    myServo2.write(0);
    myServo3.write(20);
    myServo4.write(180);
    delay(500);
    myServo4.write(90);
    myCar.setSpeed(AUTO_FWD_SPEED, AUTO_FWD_SPEED);
    delay(400);
    myCar.setSpeed(0,0);
    myServo4.write(0);
    delay(500);
    myServo2.write(150);
    delay(500);
    myCar.setSpeed(AUTO_FWD_SPEED, AUTO_FWD_SPEED);
    delay(250);
    myCar.setSpeed(0,0);
    myServo2.write(0);
    delay(100);
    myCar.setSpeed(AUTO_FWD_SPEED, AUTO_FWD_SPEED);
    delay(300);
    myCar.setSpeed(-AUTO_MID_SPEED, AUTO_MID_SPEED);
    delay(1200);
    myCar.setSpeed(-AUTO_FULL_SPEED, -AUTO_FULL_SPEED);
    delay(100);
    myCar.setSpeed(0,0);
    myServo4.write(180);
    delay(500);
    myServo4.write(90);
    myServo2.write(150);
    
    myCar.setSpeed(AUTO_FULL_SPEED, -AUTO_FULL_SPEED);
    delay(500);
    myCar.setSpeed(-AUTO_FWD_SPEED, -AUTO_FWD_SPEED);
    delay(400);
    myServo2.write(0);
    myCar.setSpeed(AUTO_FWD_SPEED, AUTO_FWD_SPEED);
    delay(400);
    myCar.setSpeed(-AUTO_FWD_SPEED, AUTO_FWD_SPEED);
    delay(50);
    myCar.setSpeed(0,0);
    myServo4.write(0);
    delay(500);
    myServo2.write(150);
    myCar.setSpeed(-AUTO_FULL_SPEED, AUTO_FULL_SPEED);
    delay(200);
    myCar.setSpeed(AUTO_FULL_SPEED, AUTO_FULL_SPEED);
    delay(850);
    myCar.setSpeed(0,0);
    myServo2.write(0);
    myCar.setSpeed(AUTO_FWD_SPEED, AUTO_FWD_SPEED);
    delay(800);
    myServo4.write(180);
    delay(500);
    myServo4.write(90);
    myServo2.write(150);
    myCar.setSpeed(AUTO_FULL_SPEED, -AUTO_FULL_SPEED);
    delay(300);
    myCar.setSpeed(0,0);
    myServo2.write(0);
    myCar.setSpeed(AUTO_FWD_SPEED, AUTO_FWD_SPEED);
    delay(2300);
    myCar.setSpeed(0,0);
    myServo2.write(150);
    autonomousMode = false;
  }
}

// Teleop function is called every time there is new data from the DriverStation
// This function must not block as new data is received every 100ms
void teleop() {
  // Get the Left Y axis and use this as the "forward speed" for the robot
  int fwd = ds.getLY();

  // Get the Left X axis and use it as the rate of turn
  int turn = ds.getLX();

  // Apply the turn adding the turn rate to the left wheels
  // and subtracting it from the right wheels
  int left = fwd + turn;
  int right = fwd - turn;

  // If the power to left or right wheel is too low, the motors can't
  // turn, so set them to 0 in the 'dead band'
  if( left > -DEADBAND && left < DEADBAND )
    left = 0;
  if( right > -DEADBAND && right < DEADBAND )
    right = 0;

  // This tells the Elegoo how fast to turn the left and right wheels
  // Using the values from the left  analog stick  
  myCar.setSpeed( left, right );       

  //Set half speed on car
if (int halfspeed = ds.getLTrig() > 0){
  left = left/2;
  right = right/2;
  myCar.setSpeed( left, right);
}

  //Set 75% speed on car
if (int seventyspeed = ds.getRTrig() > 0){
  left = left/1.5;
  right = right/1.5;
  myCar.setSpeed( left, right);
}
  /* This is where you would likely add your code to control your attachment
   * For example, the 4 Servo motors are controlled here 
   */


  /* Controls 2 servos by using the X and Y axis of the right  analog stick 
   * Controls 2 servos by extending 90° in either direction
   * 1 face button to extend 90° in one direction
   * Release button for servo position to reset
   */
  bool servoPosExtend = ds.getButton(0);
  bool servoPosRetract = ds.getButton(1);
  bool servoPosExtend2 = ds.getButton(2);
  bool servoPosRetract2 = ds.getButton(3);
  bool servoPosExtend3 = ds.getButton(13);
  bool servoPosRetract3 = ds.getButton(12);
  bool servoPosExtend4 = ds.getButton(4);
  bool servoPosRetract4 = ds.getButton(5);

  /* Checks if either the extend or retract buttons are pressed
   * If one is pressed write 1+ degree every 10ms 
   * If not keep servo at last written degree
   */ 

// For servo 1 
  if (servoPosExtend == true) {
    servoMover = servoMover + 10 ;
    myServo.write (servoMover);
    delay(1);
  }

  if (servoPosRetract == true) {
    servoMover = servoMover - 10;
    myServo.write (servoMover);
    delay(1);
  }

// For servo 2  
  if (servoPosExtend2 == true) {
    servoMover2 = servoMover2 + 10;
    myServo2.write (servoMover2);
    delay(1);
  }

  if (servoPosRetract2 == true) {
    servoMover2 = servoMover2 - 10;
    myServo2.write (servoMover2);
    delay(1);
  }

// For servo 3 
  if (servoPosExtend3 == true) {
    servoMover3 = servoMover3 + 10; 
    myServo3.write (servoMover3);
    delay(1);
  }

  if (servoPosRetract3 == true) {
    servoMover3 = servoMover3 - 10;
    myServo3.write (servoMover3);
    delay(1);
  }

// For servo 4
// This is a different servo that just sets a direction and spins as long as it is held
  if (servoPosExtend4 == true) {
    myServo4.write(150);
  }
  else{
    myServo4.write(90);
  }

  if (servoPosRetract4 == true) {
    myServo4.write(30);
  }
}

void loop() {
  // Update the Elegoo Car state
  uint16_t res = myCar.u16Update();

  // update the DriverStation class - this will check if there is new data from the
  // DriverStation application.
  // ds.bUpdate() returns true if new data has been received (10 times/second)
  if( ds.bUpdate() ) {
    // now, handle the driver station data depending on what game state we are in
    // During Pre and Post game, the Elegoo should not move!
    switch( ds.getGameState() ) {
      case ePreGame:
      myCar.setSpeed( 0, 0 );
  myServo.write(servoDefault); 
  myServo2.write(servoDefault);
  myServo3.write(servoDefault);
  myServo4.write(servoDefault);
      case ePostGame:
      autonomousMode = true;
        myCar.setSpeed( 0, 0 );  
  myServo.write(servoDefault); 
  myServo2.write(servoDefault);
  myServo3.write(servoDefault);
  myServo4.write(servoDefault);
        break;
  
      case eAutonomous:
        // Handle Autonomous mode
        autonomous();
        break;

      case eTeleop:
        // Handle telop mode
        teleop();
        break;
    }
  }

    // do other updates that need to happen more frequently than 10 times per second here...
    // e.g. checking limit switches...
      if( ds.getGameState() == eAutonomous ) {
  }
}
