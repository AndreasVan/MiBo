
// Control of Mibo Mini Bot - Last update: AndreasVan 2015-03-19 Version 2.01    
// Motor 2xServo MSR 1.3
// Micro controller = Arduino Nano 
// Avoiding obstacles with IR sensor Sharp GP2Y0D810Z0F
// this code is public domain, enjoy!
  
  #include <Servo.h>                           // Include servo library
 
  Servo servoLeft;                             // Declare left servo
  Servo servoRight;                            // Declare right servo
  int IR_pin = 0;                              // Analog pin for reading the IR sensor
  float IR_read;                               // Floating point number to hold converted voltage as distance
  
  void setup() {
    Serial.begin(9600);                        // Start the serial port
    pinMode(12, OUTPUT);                       // Blinking led
    servoLeft.attach(5);                       // Servo left to D5 
    servoRight.attach(6);                      // Servo right to D6 

  }

  void loop() {
    digitalWrite(12, HIGH);
    
    GetDistance();
//    Serial.println(distance);                // print the distance
    
    if (IR_read > 399)                         // No obstacle
    {
      forward();
    }
        
    if (IR_read < 400)                         // Obstacle
    {
      turn();
    }
  }
  
  void GetDistance(){
    IR_read = analogRead(IR_pin);               // Reads the value of the sharp sensor
    Serial.println(IR_read);                    // Prints the value of the sensor to the serial monitor
    delay(50);                                  // Delay to get stable readings
  }
  
  void turn(){                                 // Turn right subroutine
    servoLeft.write(1995);
    servoRight.write(1995);
    Serial.println("TURN");
  }

  void forward(){                                // Forward subroutine
    servoLeft.write(1995); 
    servoRight.write(1005);
    Serial.println("FORWARD");
  }
  
