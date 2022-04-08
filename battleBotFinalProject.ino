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
#define FORWARD_SPEED 255
#define TURN_SPEED 64

// Joystick values close to 0 that we'll ignore
#define DEADBAND 16 

// Creates 4 servos to control the robot arm
Servo myServo;
Servo myServo2;
Servo myServo3;
Servo myServo4;

void setup() {
 /* Put your setup code here, to run once:
  * The current setup here is initializing the console and attaching the servo pins
  */
  Serial.begin( 115200 );
  Serial.println( "Ready..." );
  Serial.println("lol im going to eat a servo motor");
  myServo.attach( c_u8ServoPin );
  myServo2.attach(c_u8ServoPin2);
  myServo3.attach(c_u8ServoPin3);
  myServo4.attach(c_u8ServoPin4);
}

 /* Autonomous is called 10 times per second during Autonomous mode.
  * This function must not block as new data is received every 100ms
  * Will be used to drive to zone D while picking up multiple cups
  */  
void autonomous(){
  int curTime = ds.getStateTimer();
  myServo.write(90);
  Serial.println("writing 90");
  delay(500);
  Serial.println("delay 500");
  myServo.write(0);
  Serial.println("writing 0");
  delay(500);
  Serial.println("deleayding 500");
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

  /* This is where you would likely add your code to control your attachment
   * For example, the 4 Servo motors are controlled here 
   */


  /* Controls 2 servos by using the X and Y axis of the right  analog stick 
   * Controls 2 servos by extending 90° in either direction
   * 1 face button to extend 90° in one direction
   * Release button for servo position to reset
   */
  int servoPos = ds.getRX();
  int servoPos2 = ds.getRY();
  bool servoPosExtend3 = ds.getButton(12);
  bool servoPosRetract3 = ds.getButton(13);
  bool servoPosExtend4 = ds.getButton(4);
  bool servoPosRetract4 = ds.getButton(5);

  /* Joystick input values range from -256 - 255, but the Servo expects
   * values from 0-180, so the numbers have to be scaled.
   * These statements are broken into separate lines to prevent the compiler from
   * calculating the value 90/256.  As an integer this would compute to 0
   */
  servoPos *= 90;
  // servoPos /= 256;
  servoPos >>= 8;  // Shifting right 8 is the same as dividing by 256 but is faster
  // Writes the value to the servo
  myServo.write( servoPos + 90 );
  
  // Same function and use as above, only for the 2nd servo
  servoPos2 *= 90;
  // servoPos2 /= 256;
  servoPos2 >>= 8;  // Shifting right 8 is the same as dividing by 256 but is faster
  // Writes the value to the servo
  myServo2.write( servoPos2 + 90 );

  /* Checks if either the extend or retract buttons are pressed
   * If one is pressed write the given value to servo3
   * If not keep servo3 at 90° (default)
   */ 
  if (servoPosExtend3 == true){
    myServo3.write(120);
  }
  else{
    myServo3.write(90);
  }
  
  if (servoPosRetract3 == true){
    myServo3.write (60);
  }
  // Same as servo3 extend/retract, but for servo4
  if (servoPosExtend4 == true){
    myServo4.write(180);
  }
  else{
    myServo4.write(90);
  }

  if (servoPosRetract4 == true){
    myServo4.write (0);
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
      
      case ePostGame:
      autonomousMode = true;
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
      if( ds.getGameState() == eAutonomous ) {
      if(autonomousMode == true){
    }
  }
}
