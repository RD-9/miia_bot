//Included libraries here
#include <Servo.h>

//Define servo motor objects
Servo myservo_0; //left  ankle
Servo myservo_1; //right ankle
Servo myservo_2; //left  hip
Servo myservo_3; //right hip

// constant definitions

// change pins according to which servos are connected where
#define LEFT_FOOT A0
#define RIGHT_FOOT A1
#define LEFT_HIP A2
#define RIGHT_HIP A3

//Define global variables 

//Function declarations
void example_Function();

void setup() {
  
  //Put your setup code here, to run once:
  Serial.begin(9600);
   
  //Click Ctrl+shift+M to see serial monitor
  Serial.println("Start of Code..."); 
  
  //configure pin modes
  pinMode(LEFT_FOOT, OUTPUT);
  pinMode(RIGHT_FOOT, OUTPUT);
  pinMode(LEFT_HIP, OUTPUT);
  pinMode(RIGHT_FOOT, OUTPUT);
  
  // configure servos
  myservo_0.attach(LEFT_FOOT);  // attaches the servo on pin 9 to the left leg
  myservo_1.attach(RIGHT_FOOT); //attaches the servo on pin 10 to the right leg  
  myservo_2.attach(LEFT_HIP);  // attaches the servo on pin 11 to the left hip
  myservo_3.attach(RIGHT_HIP); //attaches the servo on pin 10 to the right hip 

  //Set initial position of motors
  myservo_0.write(90);
  myservo_1.write(90);
  myservo_2.write(90);
  myservo_3.write(90); 

  //Delay
  delay(5000); //5 second delay
}

void loop() {
  
  //Put your main code here, to run repeatedly:
  //Call functions here.
  example_Function();
}

//=============================================
//=============================================
//FUNCTION DEFINITIONS
//=============================================
//=============================================

//FUNCTION NAME: Example function
//DESCRIPTION: 
/*   
 Add information Describing the function here:
 This is an example function.This header can be
 copied for each individual function where a 
 description of the function of the function 
 can be stated.
*/
//=============================================
//ADD FUNCTION HERE
void example_Function(){
  
  Serial.println("This is the exmaple function call..."); 
  //Delay
  delay(1000);
}
//=============================================



//=============================================
//END OF PROGRAM
//=============================================


