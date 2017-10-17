// LOFI Brain firmware to communicate with LOFI Robot ScratchX Chrome Plugin
// USB + Bluetooth version
// Author: Maciej Wojnicki
// WWW.LOFIROBOT.COM

/*
 * Lofi firmware developed for MiiA bot. 
 * Version v1.2
 * Date: 17/10/2017
 * Instructions: 
 * Connect your Arduino using the usb cable. 
 * Set the board to the arduino board, in the arduino ide go to:
 * tools -> board -> arduino Nano
 * Connect port:
 * tools -> port -> choose port board is connected to
 * click the upload button(use the second button from the left above, arrow pointing right)
 * ******************************************************************
 * Electronic Connections:
 * ******************************************************************
 * While facing the front of MiiA:
 * 
 * Left Hip Servo - 8
 * Right Hip Servo - 9
 * Left Foot Servo - 10
 * Right Foot Servo - 11
 * UltraSonic Sensor TrigPin - 2
 * UltraSonic Sensor EchoPin - 2
 * Bluetooth Module TX - 0 (RX)
 * Bluetooth Module RX - 1 (TX)
 * Servo to Calibrate - A0
 */

// included libraries
#include <Servo.h>

// function prototypes
void set_servo_position(Servo my_servo, int pin, int pos);
void calibrate(Servo my_servo, int pos);
void servo_off(Servo my_servo);
void configure_pins();

// pin assignments
#define left_hip_servo_pin 8
#define right_hip_servo_pin 9
#define left_foot_servo_pin 10
#define right_foot_servo_pin 11
#define servo_calibration_pin A0
#define uss_trigger_pin 2
#define uss_echo_pin 3

// constants
#define baud_rate 57600 // nb baud rate must be 57600 for LoFi Blocks
#define servo_calibration_pos 90

// create servo objects
Servo servo_calibrate;
Servo servo_left_hip;
Servo servo_right_hip;
Servo servo_left_foot;
Servo servo_right_foot;

//data sending (arduino->computer) interval  
//raise it if you encouter communication jitter
const long interval = 100;

int current_byte = 0;
int prev_byte = 0;
int analog1 = 1;
int analog2 = 2;
int analog3 = 3;
int analog4 = 4;

unsigned long previousMillis = 0;
unsigned long currentMillis;

void setup() 
{
  // initialize serial communications at specified baud rate
  Serial.begin(baud_rate);

  // configure all pin modes
  configure_pins();

  // set calibration pin and drive pin to calibrated position
  servo_calibrate.attach(servo_calibration_pin);
  calibrate(servo_calibrate, servo_calibration_pos);

  // setup complete
}

void loop() 
{
  currentMillis = millis();

  //receiving data from ScratchX Chrome plugin
  receiving();

  // timer delay reduce data bandwidth
  if (currentMillis - previousMillis >= interval) 
  {
    
    previousMillis = currentMillis;

    //sending data to ScratchX Chrome plugin
    sending();
  }
}

long odleglosc() 
{
  
  long duration, distance;
  digitalWrite(uss_trigger_pin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(uss_trigger_pin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(uss_trigger_pin, LOW);
  duration = pulseIn(uss_echo_pin, HIGH);
  distance = (duration/2)/29.1;
  return distance;  
}

void receiving() 
{
  if (Serial.available() > 0) 
  {
  current_byte = Serial.read();    
  outputs_set();
  prev_byte = current_byte;
  } 
}

void outputs_set() 
{
    //servo output1
    if (prev_byte == 208) 
    {
      set_servo_position(servo_left_hip, left_hip_servo_pin, current_byte);      
    }
      //servo output2
    if (prev_byte == 209) 
    {
      set_servo_position(servo_right_hip, right_hip_servo_pin, current_byte);
    }
      //servo output3
    if (prev_byte == 210) 
    {
      set_servo_position(servo_left_foot, left_foot_servo_pin, current_byte);
    }
      //servo output4
    if (prev_byte == 211) 
    {
      set_servo_position(servo_right_foot, right_foot_servo_pin, current_byte);
    }

    if (prev_byte == 212 && current_byte == 99) 
    {
      // detach all servos
      servo_off(servo_left_hip);
      servo_off(servo_right_hip);
      servo_off(servo_left_foot);
      servo_off(servo_right_foot);      
    }
}

void sending() {

  // even if not using analog inputs, LoFi requires this.
  Serial.write(224);
  Serial.write(byte(analog1));
  Serial.write(225);
  Serial.write(byte(analog2));
  Serial.write(226);
  Serial.write(byte(analog3));
  Serial.write(227);
  Serial.write(byte(analog4));
  Serial.write(240);

  // ultra sonic sensor output
  Serial.write(byte(odleglosc()));   
  // last byte "i" character as a delimiter for BT2.0 on Android
  Serial.write(105);  
}

// function to configure pins and pin modes
void configure_pins()
{
  // servo calibration pin
  pinMode(servo_calibration_pin, OUTPUT);
  
  // miia servo motor signal pins
  pinMode(left_hip_servo_pin, OUTPUT);  
  pinMode(right_hip_servo_pin, OUTPUT);
  pinMode(left_foot_servo_pin, OUTPUT);
  pinMode(right_foot_servo_pin, OUTPUT);

  // ultrasonic sensor trigger and echo pins
  pinMode(uss_trigger_pin, OUTPUT);
  pinMode(uss_echo_pin, INPUT);
}

// function to turn off, and detach, all a servo
void servo_off(Servo my_servo) 
{
  my_servo.detach();
}

// function to calibrate servo motors to predtermined position
void calibrate(Servo my_servo, int pos)
{
  my_servo.write(pos);
  delay(15);
}

// function to set position of a servo motor
void set_servo_position(Servo my_servo, int pin, int pos)
{
  my_servo.attach(pin);
  if (pos < 15)
  {
    my_servo.write(15);
  }
  else
  {
    my_servo.write(pos);
  }
}

//end