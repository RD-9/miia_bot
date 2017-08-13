//Included libraries here
#include <Servo.h>

//Define servo motor objects
Servo myservo_0; //left  ankle
Servo myservo_1; //right ankle
Servo myservo_2; //left  hip
Servo myservo_3; //right hip

//Define global variables 

//Function declarations
void motor_movement(int motor);
void motor_position(int motor);
void initialpos();

void setup() {
  
  //Put your setup code here, to run once:
  Serial.begin(9600);
   
  //Click Ctrl+shift+M to see serial monitor
  Serial.println("Start of calibration code..."); 
  
  //Attach servo objects to  individual pins, this can be changed if required  
  myservo_0.attach(9);  //Pin 9 to the left leg
  myservo_1.attach(5);  //Pin 5 to the right leg  
  myservo_2.attach(10); //Pin 10 to the left hip
  myservo_3.attach(6);  //Pin 6 to the right hip 

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
  int motor = ;
  int angle = 120;

  //motor_movement(motor);
  //motor_position(motor,angle);
  //initialpos();
}

//=============================================
//=============================================
//FUNCTION DEFINITIONS
//=============================================
//=============================================

//FUNCTION NAME: motor_movement
//DESCRIPTION: 
/*   
  The user chooses which motor  movement to check.
  This checks if their motor movement moves correctly
  and if each motor is connected to the right pin. 
*/
//=============================================
//motor_movement
void motor_movement(int motor){
  //motor movement check
    
  Serial.println("Initalize motor movement function...");
  switch(motor){    
    case(1):
      //check motor one movement      
      Serial.println("motor 1 movement check: ");
      myservo_0.write(90);
      Serial.println("motor 1 is at 90");
      delay(2000);
      myservo_0.write(0);
      Serial.println("motor 1 is at 0");
      delay(2000);
      myservo_0.write(90);
      Serial.println("motor 1 is at 90");
      delay(2000);      
      myservo_0.write(180);
      Serial.println("motor 1 is at 180");
      delay(2000);
      break;
    case(2):
      //check motor two movement      
      Serial.println("motor 2 movement check ");
      myservo_1.write(90);
      Serial.println("motor 2 is at 90");
      delay(2000);
      myservo_1.write(0);
      Serial.println("motor 2 is at 0");
      delay(2000);
      myservo_1.write(90);
      Serial.println("motor 2 is at 90");
      delay(2000);
      myservo_1.write(180);
      Serial.println("motor 2 is at 180");
      delay(2000);      
      break;
    case(3):
      //check motor three movement      
      Serial.println("motor 3 movement check ");
      myservo_2.write(90);
      Serial.println("motor 3 is at 90");
      delay(2000);
      myservo_2.write(0);
      Serial.println("motor 3 is at 0");
      delay(2000);
      myservo_2.write(90);
      Serial.println("motor 3 is at 90");
      delay(2000);
      myservo_2.write(180);
      Serial.println("motor 3 is at 180");
      delay(2000);
      break;
      
    case(4):
      //check motor four movement      
      Serial.println("motor 4 movement check ");
      myservo_3.write(90);
      Serial.println("motor 4 is at 90");
      delay(2000);
      myservo_3.write(0);
      Serial.println("motor 4 is at 0");
      delay(2000);
      myservo_3.write(90);
      Serial.println("motor 4 is at 90");
      delay(2000);
      myservo_3.write(180);
      Serial.println("motor 4 is at 180");
      delay(2000);
      break;      
    }
  }


//=============================================
//FUNCTION NAME: motor_position
//DESCRIPTION: 
/*   
This function allows the user to set the angle they
want each individual motors to be at.
Users can choose between motor 1,2,3,4 and an angle
between 0 and 180. 
*/
//=============================================
//ADD FUNCTION HERE
void motor_position(int motor,int angle){
    Serial.println("Initalize motor position function...");
  switch(motor){    
    case(1):
      //Set angle to motor 1    
      Serial.println("motor 1 is set to an angle: ");
      Serial.println(angle);
      myservo_0.write(angle);
      delay(2000);
      break;
      
    case(2):
      //Set angle to motor 2        
      Serial.println("motor 2 is set to an angle: ");
      Serial.println(angle);
      myservo_1.write(angle);
      delay(2000);
      break;  
      
    case(3):
      //check motor three movement      
      Serial.println("motor 3 is set to an angle: ");
      Serial.println(angle);
      myservo_2.write(angle);
      delay(2000);
      break;     
      
    case(4):
      //check motor four movement      
      Serial.println("motor 4 is set to an angle: ");
      Serial.println(angle);
      myservo_3.write(angle);
      delay(2000);
      break;    
    }
  }

//=============================================
//=============================================
//FUNCTION NAME: Initial position
//DESCRIPTION: 
/*   
 This sets all the motors to the horizontal
 position. 
*/
//=============================================
//INTIAL POSITION
void initialpos(){
  Serial.println("Initalize initialpos function...");  
  //set the motors to the inital positions
  myservo_0.write(90);
  myservo_1.write(90);
  myservo_2.write(90);
  myservo_3.write(90);
  Serial.println("All motors are at 90");  
}
//=============================================
//END OF PROGRAM
//=============================================


