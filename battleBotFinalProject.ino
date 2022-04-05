#include <Servo.h>
#include "elegoo-car.h"
#include "DriverStation.h"

bool autonomousMode = true; 

// Demo code taken from wpilib

// Create the ElegooCar object named myCar
ElegooCar myCar;
// Create the DriverStation object named ds
DriverStation ds;

#define AUTO_FWD_SPEED 154
#define FORWARD_SPEED 255
#define TURN_SPEED 64

#define DEADBAND 16 // Joystick values close to 0 that we'll ignore

// create a Servo object named myServo
Servo myServo;
Servo myServo2;
Servo myServo3;
Servo myServo4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );
  Serial.println( "Ready..." );
  Serial.println("lol im going to eat a servo motor");
  myServo.attach( c_u8ServoPin );
  myServo2.attach(c_u8ServoPin2);
  myServo3.attach(c_u8ServoPin3);
  myServo4.attach(c_u8ServoPin4);
}

// autonomous is called 10 times per second during Autonomous mode.
// this function must not block as new data is received every 100ms
//
// you could implement line following here...
void autonomous(){
  int curTime = ds.getStateTimer();
  myServo.write (90);
        delay(500);
        myServo.write (0);
}

// teleop function is called every time there is new data from the DriverStation
// this function must not block as new data is received every 100ms
void teleop() {
  // get the Right Y axis and use this as the "forward speed" for the robot
  int fwd = ds.getRY();

  // get the Right X axis and use it as the rate of turn
  int turn = ds.getRX();

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

  // Now tell the Elegoo how fast to turn the left and right wheels
  myCar.setSpeed( left, right );       

  // This is where you would likely add your code to control your attachment
  // As an example, we will set the Ultrasonic Range Finder direction based on
  // the Left stick X value



  // Get left X to use for Servo position
  int servoPos = ds.getLX();
  int servoPos2 = ds.getLY();
  int servoPos3 = ds.getLTrig();
  int servoPos4 = ds.getRTrig();

  // Joystick input values range from -256 - 255, but the Servo is expects
  // values from 0-180, so the numbers have to be scaled.
  // these statements are broken into separate lines to prevent the compiler from
  // calculating the value 90/256.  As an integer this would compute to 0
  servoPos *= 90;
  // servoPos /= 256;
  servoPos >>= 8;  // shifting right 8 is the same as dividing by 256 but is faster

  myServo.write( servoPos + 90 );
  
  // Joystick input values range from -256 - 255, but the Servo is expects
  // values from 0-180, so the numbers have to be scaled.
  // these statements are broken into separate lines to prevent the compiler from
  // calculating the value 90/256.  As an integer this would compute to 0
  servoPos2 *= 90;
  // servoPos /= 256;
  servoPos2 >>= 8;  // shifting right 8 is the same as dividing by 256 but is faster

  myServo2.write( servoPos2 + 90 );

  
  // Joystick input values range from -256 - 255, but the Servo is expects
  // values from 0-180, so the numbers have to be scaled.
  // these statements are broken into separate lines to prevent the compiler from
  // calculating the value 90/256.  As an integer this would compute to 0
  servoPos3 *= 90;
  // servoPos /= 256;
  servoPos3 >>= 8;  // shifting right 8 is the same as dividing by 256 but is faster

  myServo3.write( servoPos3 + 90 );

  
  // Joystick input values range from -256 - 255, but the Servo is expects
  // values from 0-180, so the numbers have to be scaled.
  // these statements are broken into separate lines to prevent the compiler from
  // calculating the value 90/256.  As an integer this would compute to 0
  servoPos4 *= 90;
  // servoPos /= 256;
  servoPos4 >>= 8;  // shifting right 8 is the same as dividing by 256 but is faster

  myServo4.write( servoPos4 + 90 );
}

void loop() {
  // Update the Elegoo Car state
  int res = myCar.u16Update();

  // update the DriverStation class - this will check if there is new data from the
  // DriverStation application.
  // ds.bUpdate() returns true if new data has been received (10 times/second)
  if( ds.bUpdate() ) {
    // now, handle the driver station data depending on what game state we are in
    switch( ds.getGameState() ) {
      case ePreGame:
      myCar.setSpeed( 0, 0 );

      case ePostGame:
      autonomousMode = true;
        // During Pre and Post game, the Elegoo should not move!
        myCar.setSpeed( 0, 0 );
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
  
  //forward speed is declared at the top, add negatives to control the direction you want it to go
    if( ds.getGameState() == eAutonomous ) {
      if(autonomousMode == true){
}
    }
}
