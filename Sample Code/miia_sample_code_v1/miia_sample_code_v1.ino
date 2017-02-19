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

// change to true/false to enable use of bluetooth module
#define BLUETOOTH_COMMS true

//Define global variables 
int  Init,increment,angle,steps;
int  left_leg,right_leg,left_hip,right_hip;
long randomNumber;
byte byteRead;

int  initial[4] = {90,90,90,90};
int  Range[4] = {0,0,0,0};
int  NewArray[4] = {0,0,0,0};

//Function declarations
//===============================================

//Fundamentals
void sweep_write(int NewArray);
void initialpos(); //pass

//Dynamic
//walk functions
void walk_forward(int steps);
void walk_back(int steps);

//turning functions
void turn_right(int angle);
void turn_right_back(int angle);
void turn_left(int angle);
void turn_left_back(int angle);

//Static
void toe_stand();
void heal_stand(); 

void left_foot_tap();
void right_foot_tap();

void stand_leg_left();
void stand_leg_right();

void right_foot_wave();
void left_foot_wave();
 
void half_fwd_hiproll();
void half_bck_hiproll();
void full_hiproll();

void left_hiproll();
void right_hiproll();


//random function
void randomFidget();

//Communication
void bluetoothControl();

//=============================================

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

  //Initial positions
  increment = 1;
  Init = 0;

  //random seed function to make the randomfidget to start at different places
  randomSeed(analogRead(0));
  
  if (not BLUETOOTH_COMMS)
  {
    // delay before controllable - add a bluetooth? flag above, if using bluetooth comms don't need this, else, do so MiiA doesn't walk immediately
    delay(10000);
    Serial.println("Waited 10 Seconds!");
  }
  Serial.println("Okay go");
}

void loop() {
 
  //Call functions here.
  if (BLUETOOTH_COMMS)
  {
    bluetoothControl();
  }
  else
  {
    randomFidget();
  }
  
}

//=============================================
//=============================================
//FUNCTION DEFINITIONS
//=============================================
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
    
  //set the motors to the inital positions
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 90;
  NewArray[3] = 90;
  Serial.println("Motors set to initial position");
  sweep_write(NewArray);    
}
//=============================================
//FUNCTION NAME: Sweep write
//DESCRIPTION: 
/*   
This function ensures the motors will sweep to 
each position given to it.Input to the function
is an array.The resolution of the 
sweep will be set by the increment amount. 
*/
//=============================================
//SWEEP WRITE
void sweep_write(int NewArray[4]){
  
  //This runs once
  if(Init == 0){
       Serial.println("Initial run");    
      //range initalised
      Range[0] = 0;
      Range[1] = 0;
      Range[2] = 0;
      Range[3] = 0;
  
      //initial position of the motors
      initial[0] = 90;
      initial[1] = 90;
      initial[2] = 90;
      initial[3] = 90;
      
      //initial change
      Init = 1;
    }
    
  for(int i = 0; i<4; i++){
    
      if (NewArray[i] == -1){                       
        Range[i] = 0;
        }
      else{
        
        Range[i] = abs(NewArray[i] - initial[i]);
        }
    }

  //Set the direction variables to add or subract
  //from the position
  int dir[4] = {0,0,0,0};  
  for(int k = 0; k<4; k++){
    
    if (NewArray[k]< initial[k]){      
      dir[k] = 1; //Subtract from the last one
      }
      
    else if ( NewArray[k] > initial[k]){      
      dir[k] = 2; //Add to the last one
      }
      
    else{      
      dir[k] = 3;//do nothing this is a no write
      }
    }
    
  //calculating the max range
  //This ensures that the max range is known so the
  //motors can be moved equally
  int max1 = max(Range[0],Range[1]);
  int max2 = max(Range[2],Range[3]);
  int max3 = max(max1,max2);
  
  for (int j = 0; j < max3;j+=increment){
    for(int l = 0; l<4; l+=1){
      if (j<Range[l]){
        if(dir[l] == 1){
          initial[l] = initial[l]-increment;
          }
        else if(dir[l] == 2){
          initial[l] = initial[l]+increment;
          }
         else{
          initial[l] = initial[l];
          }
        }
      }
      
    //this is where we write to the motors 

    Serial.println("Write the values to the motors");
    //servo write
    myservo_0.write(initial[0]);
    myservo_1.write(initial[1]);
    myservo_2.write(initial[2]);
    myservo_3.write(initial[3]);
    //delay(15); 
    }
  }
//=============================================
//FUNCTION NAME:walk_forward
//DESCRIPTION: 
/*   
This function enables the robot to walk forward
Input an odd amount of steps when enabling this
function. 
*/
//=============================================
//walk_forward
void walk_forward(int steps){
  
  Serial.println("Initialize forward walk...");     
  //this is the initial variable
  int dir = 1;
  int x = 1;
  
  for (int k = 0;k<=steps;k += 1){        

 //this is the initial position
 //*************************************

     if(dir ==1){
        dir = 2;
        NewArray[0] = 110;
        NewArray[1] = 170;
        NewArray[2] = -1;
        NewArray[3] = -1;
        Serial.println("Stand left. leg-phase 2");
        sweep_write(NewArray);              
        
     }
    else{      
       dir = 1;
       NewArray[0] = 10;
       NewArray[1] = 70;
       NewArray[2] = -1;
       NewArray[3] = -1;
       Serial.println("Stand right. leg-phase 1");
       sweep_write(NewArray);          
    }

  //this is the hip rotation
  //*************************************
  x = -1*x;
    
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 90 - x*30;
  NewArray[3] = 90 - x*30;
  Serial.println("Hip Rotation. leg-phase 2"); 
  sweep_write(NewArray);
  
//this is the end of the step
//**************************************
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1; 
  Serial.println("Foot down. leg-phase 3"); 
  sweep_write(NewArray);
  }
}

//=============================================
//FUNCTION NAME:walk_back
//DESCRIPTION: 
/*   
This function enables the robot to walk backwards
Input an odd amount of steps when enabling this
function. 
*/
//=============================================
//walk_back
void walk_back(int steps){
  
  Serial.println("Initialize back walk...");     
  //this is the initial variable
  int dir = 1;
  int x = 1;
  
  for (int k = 0;k<=steps;k += 1){        

 //this is the initial position
 //*************************************

     if(dir ==1){
        dir = 2;
        NewArray[0] = 110; //left ankle
        NewArray[1] = 170; //right ankle
        NewArray[2] = -1;
        NewArray[3] = -1;
        Serial.println("Stand left. leg-phase 2");
        sweep_write(NewArray);              
        
     }
    else{      
       dir = 1;
       NewArray[0] = 10;
       NewArray[1] = 70;
       NewArray[2] = -1;
       NewArray[3] = -1;
       Serial.println("Stand right. leg-phase 1");
       sweep_write(NewArray);          
    }

  //this is the hip rotation
  //*************************************
  x = -1*x;
    
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 90 + x*30;
  NewArray[3] = 90 + x*30;
  Serial.println("Hip Rotation. leg-phase 2"); 
  sweep_write(NewArray);
  
//this is the end of the step
//**************************************
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = -1;
  NewArray[3] = -1; 
  Serial.println("Foot down. leg-phase 3"); 
  sweep_write(NewArray);
  }
}
//Turning funtions need to be made here


//=============================================
//FUNCTION NAME: Toe_stand
//DESCRIPTION: 
/*   
 Robot stand on toes
*/
//=============================================
//toe_stand
void toe_stand(){
  
  Serial.println("Initialize toe_stand..."); 
  //stand on toes 
  NewArray[0] = 30;
  NewArray[1] = 150;
  NewArray[2] = -1;
  NewArray[3] = -1;
  sweep_write(NewArray);
  }
//=============================================
//=============================================
//FUNCTION NAME: heal_stand
//DESCRIPTION: 
/*   
 Robot stand on heals
*/
//=============================================
//heal_stand
void heal_stand(){
  //stand on heals now
  Serial.println("Initialize heal_stand...");
  NewArray[0] = 160;
  NewArray[1] = 20;
  NewArray[2] = -1;
  NewArray[3] = -1;
  sweep_write(NewArray);
  }
//=============================================
//FUNCTION NAME: left_foot_tap
//DESCRIPTION: 
/*   
Robot taps left foot. This function needs to be
looped to work
*/
//=============================================
//left_foot_tap
void left_foot_tap(){
  Serial.println("Initialize left foot tap...");
  initialpos();
  //this is the tap
  NewArray[0] = 110;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = -1;
  sweep_write(NewArray);
  }
//=============================================

//FUNCTION NAME: Initial positon
//DESCRIPTION: 
/*   
 Robot taps right foot. This function needs to be
 looped to work.
*/
//=============================================
//right_foot_tap
void right_foot_tap(){
  Serial.println("Initialize right foot tap...");
  initialpos();
  //this is the tap
  NewArray[0] = -1;
  NewArray[1] = 70;
  NewArray[2] = -1;
  NewArray[3] = -1; 
  sweep_write(NewArray);
  }
//=============================================
//FUNCTION NAME: stand_leg_left
//DESCRIPTION: 
/*   
stand on left leg
*/
//=============================================
//stand_leg_left
void stand_leg_left(){
  Serial.println("Initialize stand left leg...");
  NewArray[0] = 120;
  NewArray[1] = 170;
  NewArray[2] = 90;
  NewArray[3] = 90;
  //write to the motors
  sweep_write(NewArray);
  }
//=============================================
//=============================================
//FUNCTION NAME: stand_leg_right
//DESCRIPTION: 
/*   
stand on right leg
*/
//=============================================
//stand_leg_right
void stand_leg_right(){
  Serial.println("Initialize stand right leg...");
  NewArray[0] = 10;
  NewArray[1] = 60;
  NewArray[2] = 90;
  NewArray[3] = 90;

  //write to the motors
  sweep_write(NewArray);
  }
//=============================================
//FUNCTION NAME: right_foot_wave
//DESCRIPTION: 
/*   
Stand on right foot and wave with the other foot
*/
//=============================================
//right_foot_wave
void right_foot_wave(){
  Serial.println("Initialize right foot wave...");
  stand_leg_left();
  
  for(int i = 0; i<=1; i+=1){
    NewArray[0] = -1;
    NewArray[1] = 70;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  
    NewArray[0] = -1;
    NewArray[1] = 120;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  }
}
//=============================================
//FUNCTION NAME: left_foot_wave
//DESCRIPTION: 
/*   
 Stand on left foot and wave with the other foot
*/
//=============================================
//left_foot_wave
void left_foot_wave(){
  Serial.println("Initialize left foot wave...");
  stand_leg_right();
  
  for(int i = 0; i<=1; i+=1){
    NewArray[0] = 120;
    NewArray[1] = -1;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  
    NewArray[0] = 70;
    NewArray[1] = -1;
    NewArray[2] = -1;
    NewArray[3] = -1;
    //write to the motors
    sweep_write(NewArray);
  }
 }
//=============================================
//FUNCTION NAME: half_fwd_hiproll
//DESCRIPTION: 
/*   
half a hip roll with both legs forward.This function
needs to be looped to work.
*/
//=============================================
//half_fwd_hiproll
void half_fwd_hiproll(){
  Serial.println("Initialize half fwd hiproll...");
  initialpos();
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 70;
  NewArray[3] = 110;
  //write to the motors
  sweep_write(NewArray);  
  }
//=============================================
//FUNCTION NAME: half_bck_hiproll
//DESCRIPTION: 
/*   
half a hip roll with both legs backwards.This function needs
to be looped to work
*/
//=============================================
//half_bck_hiproll
void half_bck_hiproll(){
  Serial.println("Initialize half bck hiproll...");
  initialpos();
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 110;
  NewArray[3] = 70;
  //write to the motors
  sweep_write(NewArray); 
  }
//=============================================
//FUNCTION NAME: full_hiproll
//DESCRIPTION: 
/*   
full hiproll with both legs.This needs to be looped
to work.
*/
//=============================================
//full_hiproll
void full_hiproll(){
  Serial.println("Initialize full hiproll...");
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 110;
  NewArray[3] = 70;
  //write to the motors
  sweep_write(NewArray);
  
  NewArray[0] = 90;
  NewArray[1] = 90;
  NewArray[2] = 70;
  NewArray[3] = 110;
  //write to the motors
  sweep_write(NewArray);
}
//=============================================
//FUNCTION NAME: left_hiproll
//DESCRIPTION: 
/*   
hiproll with the left leg.This function needs to
looped to work.
*/
//=============================================
//left_hiproll
void left_hiproll(){
  Serial.println("Initialize left leg hiproll...");
  initialpos();  
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = 70;
  NewArray[3] = -1;
  //write to the motors
  sweep_write(NewArray);
   
  }
//=============================================
//FUNCTION NAME: right_hiproll
//DESCRIPTION: 
/*   
hiproll with the right leg.This function needs
to be looped to be work.
*/
//=============================================
//right_hiproll
void right_hiproll(){
  Serial.println("Initialize right hiproll...");
  initialpos();  
  NewArray[0] = -1;
  NewArray[1] = -1;
  NewArray[2] = -1;
  NewArray[3] = 110;
  //write to the motors
  sweep_write(NewArray);
  }
//=============================================
//FUNCTION NAME: randomFidget
//DESCRIPTION: 
/*   
This function chooses 2 random numbers which corresponds
to a function and delay between functions. By doing this
the function will make the robot fidget,this funcion can be
used to give life to miia
*/
//=============================================
//RandomFidget
void randomFidget(){
  Serial.println("Initialize Random fidget...");
  increment = 3;
  initialpos();

  //random numbers generated
  randomNumber = random(1,20);
  delay(randomNumber*1000);
  
  randomNumber = random(1,14);
  //switch statement which chooses which function to use
  //in each case.
  switch(randomNumber){

    case 1:{
    //this taps the left foot 5 times
      for(int k=0;k<=5;k+=1){
        left_foot_tap();  
        }
      break;
    }
     case 2:{
      //this taps the left and right foot 5 times
      for(int k=0;k<=5;k+=1){
        left_foot_tap();
        right_foot_tap();
        delay(50);  
        }
      break;     
    }
     case 3:{
      for(int k=0;k<=4;k+=1){
       left_hiproll();
      }
      break;
    }
     case 4:{
      stand_leg_left();
      delay(2000);
      break;
    }
     case 5:{
      stand_leg_right();
      delay(500);
      break;
    }
     case 6:{
       for(int k=0;k<=3;k+=1){
        full_hiproll();
       }
       break;
    }
     case 7:{
       for(int k=0;k<=2;k+=1){
         right_foot_wave();
         left_foot_wave();
         delay(50);
       }
      break;
    }
     case 8:{
      right_foot_wave();
      break;
    
    }
     case 9:{
       left_foot_wave();
       break;
    }
     case 10:{
      for(int k=0;k<=2;k+=1){
        toe_stand();
        heal_stand();
      }
      break;
    }
     case 11:{
      toe_stand();
      break;
    }
     case 12:{
      heal_stand();
      break;
    } 
      case 13:{
      for(int k=0;k<=5;k+=1){
      right_foot_tap();  
      }
      break;        
    }
    case 14:{
      for(int k=0;k<=4;k+=1){
       right_hiproll();
      }
      break;
    }         
  }
  randomNumber = random(1,14);
  delay(randomNumber*1000);
  
}
//=============================================
//FUNCTION NAME: Bluetooth communication
//DESCRIPTION: 
/*   
This function is used with a bluetooth chip HC06 bluetooth chip.The function
can be conditions can be changed depending on what is required.
*/
//=============================================
//bluetoothControl
void bluetoothControl(){
  Serial.println("Initialize bluetooth communication...");   
  //This waits for a connection from a bluetooth device
  if (Serial.available()){
    byteRead = Serial.read();
    Serial.println(" ");
    Serial.println("I have read the byte, and that byte is: ");
    Serial.println(byteRead);

    //switch(byteRead)
    if (byteRead == 'a'){
      //this will be the walk forward
      steps = 3;
      increment = 5;
      walk_forward(steps);
      byteRead == 0;
    }
    if (byteRead == 'b'){
      //this will be the walk back
      steps = 3;
      increment = 5;
      walk_back(steps);
      byteRead == 0;
    }
    if (byteRead == 'c'){
      //this will be the walk left, however we will use left leg
      stand_leg_left();
      byteRead == 0;      
    }
    if (byteRead == 'd'){
      //this will be the walk right, however we will use right leg
      stand_leg_right();
      byteRead == 0;
    }
    if (byteRead == 'e'){
      //this will be the walk right, however we will use right leg
      initialpos();
      byteRead == 0;
    }
    if (byteRead == 'f'){
      //this will be the walk right, however we will use right leg
      for(int k=0;k<=5;k+=1){
        right_foot_tap();  
      }
      byteRead == 0;
    }
    if (byteRead == 'g'){
      //this will be the walk right, however we will use right leg
      for(int k=0;k<=5;k+=1){
        left_foot_tap();  
      }
      byteRead == 0;
    }
    if (byteRead == 'h'){
      //this will be the walk right, however we will use right leg
       for(int k=0;k<=3;k+=1){
        full_hiproll();
       }
      byteRead == 0;
    }
    if (byteRead == 'i'){
      //this will be the walk right, however we will use right leg
      right_foot_wave();         
      byteRead == 0;
    }
    if (byteRead == 'j'){
      //this will be the walk right, however we will use right leg
      left_foot_wave();
      byteRead == 0;
    }
  }    
}
//=============================================
//END OF PROGRAM
//=============================================
