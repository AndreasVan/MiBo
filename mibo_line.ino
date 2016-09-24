/*Line Follower
This code is for a simple line following robot with continuous rotation servo
*****************************************************************************/

#include <QTRSensors.h>                  // Pololu QTR Sensor Library
#include <Servo.h>                       // Include servo library
#define LeftSensePin    3                // Left Line Sensor Pin
#define RightSensePin   2                // Right Line Sensor Pin
#define MiddleSensePin  4                // Middle Line Sensor Pin
#define ThreshHoldVal   1000             // Line Sensor Threshold value

//Create QTR Sensor Line Following Object
QTRSensorsRC qtrrc((unsigned char[]) {LeftSensePin, RightSensePin, MiddleSensePin},3, 2500, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[3];

//Create Servo   
Servo servoLeft;                          // Declare left servo
Servo servoRight;                         // Declare right servo
int IR_pin = 0;                           // Analog pin for reading the IR sensor
float IR_read;                            // Floating point number to hold converted voltage as distance

void setup()
{
  pinMode(12, OUTPUT);                    // Blinking led
  servoLeft.attach(5);                    // Servo left to D5 
  servoRight.attach(6);                   // Servo right to D6
  Serial.begin(9600);                     // set the data rate in bits per second for serial data transmission
  servoLeft.write(140);                   // 180
  servoRight.write(40);                   // 0
  Serial.println("Forward");
}

void loop()
{
   digitalWrite(12, HIGH);
   qtrrc.read(sensorValues);               //Read Sensors
   while(sensorValues[0]<ThreshHoldVal)    //Check Left Sensor Value
  {
    servoLeft.write(110);                  // 180 (130)
    servoRight.write(80);                  // 80
    qtrrc.read(sensorValues);
    Serial.println("Turn Right");
  }
  while(sensorValues[0]<ThreshHoldVal && sensorValues[2]<ThreshHoldVal)    //Check Left and Middle Sensor Value
  {
    servoLeft.write(180);                  // 180
    servoRight.write(80);                  // 65
    qtrrc.read(sensorValues);
    Serial.println("Driving Right");
  }
  while(sensorValues[1]<ThreshHoldVal)     //Check Right Sensor Value
  {
    servoLeft.write(90);                   // 90
    servoRight.write(60);                  // 0 (50)
    qtrrc.read(sensorValues);
    Serial.println("Turn Left");
  }
  while(sensorValues[1]<ThreshHoldVal && sensorValues[2]<ThreshHoldVal)     //Check Right and Middle Sensor Value
  {
    servoLeft.write(90);                   // 115
    servoRight.write(0);                   //  0
    qtrrc.read(sensorValues);
    Serial.println("Driving Left");
  }
  while(sensorValues[0]>ThreshHoldVal && sensorValues[1]>ThreshHoldVal)     //Check Right and Middle Sensor Value
  {
    servoLeft.write(140);                   // 180
    servoRight.write(40);                   //  0
    qtrrc.read(sensorValues);
    Serial.println("Driving Forward");
  }  
   delay(5);
}
