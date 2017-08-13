// LOFI Brain firmware to communicate with LOFI Robot ScratchX Chrome Plugin
// USB + Bluetooth version
// Author: Maciej Wojnicki
// WWW.LOFIROBOT.COM
/*
 * Lofi firmware developed for MiiA bot. 
 * Version vA0
 * Date: 12/08/2017
 * Instruction: 
 * Connect your Ardiuno using the usb cable. 
 * Set the board to the arduino board.go to:
 * tools -> board -> arduino Nano
 * Connect port:
 *tools -> port -> choose port board is connected to
 * click the upload button(use the second button from the left above)
 */


#include <Servo.h>

//data sending (arduino->computer) interval  
//raise it if you encouter communication jitter
const long interval = 100;

int analog1 = 0;
int analog2 = 0;
int analog3 = 0;
int analog4 = 0;
int trigPin = 2;
int echoPin = 3;
int dist;
int current_byte = 0;
int prev_byte = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis;


Servo serwo1;
Servo serwo2;
Servo serwo3;
Servo serwo4;

void setup() {
  //Serial.begin(57600);
  //Serial1.begin(57600);  
  //pinMode(2,OUTPUT);
  //pinMode(3,OUTPUT);
  
  Serial.begin(9600);
  Serial1.begin(9600);
  
  pinMode(4,OUTPUT);  
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(5,OUTPUT);
  
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(6,OUTPUT);  
  pinMode(16,OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

currentMillis = millis();

  //receiving data from ScratchX Chrome plugin
  receiving();

  // timer delay reduce data bandwidth
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    //sending data to ScratchX Chrome plugin
    sending();
    //digitalWrite(16,HIGH);
    //delay(10);
  }
//digitalWrite(16,LOW);
}



void odleglosc() {
  
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(5); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 5000);
  distance = (duration/2) / 29.1;

  //Serial.print(distance);
  //Serial.println(" cm");
  
  //delay(20);
  
  dist = distance;
}

void receiving() {

  // 201 - buzzer
  // 202 - motor1
  // 203 - motor2

  if (Serial.available() > 0) {
  current_byte = Serial.read();
   //Serial.print(recieved);
  
//buzzer
  if (prev_byte == 201) {
      digitalWrite(16,current_byte);
  }
  outputs_set();
  prev_byte = current_byte;

  }

  //bluetooth
  if (Serial1.available() > 0) {
  current_byte = Serial1.read();
   //Serial.print(recieved);
  
//buzzer
  if (prev_byte == 201) {
      digitalWrite(16,current_byte);
  }
  outputs_set();
  prev_byte = current_byte;
  }


  
}


void outputs_set() {

//motor1
  if (prev_byte == 202) {

    if (current_byte <= 100) {
      digitalWrite(2,HIGH);
      digitalWrite(4,LOW);
      analogWrite(3,current_byte*2.35);
    }
    
    if (current_byte > 100) {
      digitalWrite(4,HIGH);
      digitalWrite(2,LOW);
      analogWrite(3,(current_byte-100)*2.35);
    }
    
  }

//motor2
  if (prev_byte == 203) {

    if (current_byte <= 100) {
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      analogWrite(5,current_byte*2.35);
    }
    
    if (current_byte > 100) {
      digitalWrite(8,HIGH);
      digitalWrite(7,LOW);
      analogWrite(5,(current_byte-100)*2.35);
    }
    
  }

  //output1
  if (prev_byte == 204) {
      analogWrite(10,current_byte*2.55);
  }
  //output2
    if (prev_byte == 205) {
      analogWrite(9,current_byte*2.55);
  }
  //output3
    if (prev_byte == 206) {
      analogWrite(6,current_byte*2.55);
  }
  //output4
    if (prev_byte == 207) {
      analogWrite(5,current_byte*2.55);
  }

    //servo output1
    if (prev_byte == 208) {
      servo1(current_byte);
  }
      //servo output2
    if (prev_byte == 209) {
      servo2(current_byte);
  }
      //servo output3
    if (prev_byte == 210) {
      servo3(current_byte);
  }
      //servo output4
    if (prev_byte == 211) {
      servo4(current_byte);
  }

  if (prev_byte == 212 && current_byte == 99) {
      servo_off();
  }
  


}

void sending() {

  analog1 = analogRead(0)/10.23;
  analog2 = analogRead(1)/10.23;
  analog3 = analogRead(2)/10.23;
  analog4 = analogRead(3)/10.23;
  
//[224, 115, 2, 225, 102, 4, 226, 107, 5, 227, 63, 6]
  Serial.write(224);
  Serial.write(byte(analog1));
  Serial.write(225);
  Serial.write(byte(analog2));
  Serial.write(226);
  Serial.write(byte(analog3));
  Serial.write(227);
  Serial.write(byte(analog4));

  odleglosc();

  Serial.write(240);
  Serial.write(byte(dist));

  //bluetooth
  Serial1.write(224);
  Serial1.write(byte(analog1));
  Serial1.write(225);
  Serial1.write(byte(analog2));
  Serial1.write(226);
  Serial1.write(byte(analog3));
  Serial1.write(227);
  Serial1.write(byte(analog4));

  odleglosc();

  Serial1.write(240);
  Serial1.write(byte(dist));
  // last byte "i" character as a delimiter for BT2.0 on Android
  Serial1.write(105);


}

void servo1(int position) {
serwo1.attach(11);
serwo1.write(position);
//delay(5);
//serwo.detach();
}

void servo2(int position) {
serwo2.attach(10);
serwo2.write(position);
//delay(5);
//serwo.detach();
}
void servo3(int position) {
serwo3.attach(9);
serwo3.write(position);
//delay(5);
//serwo.detach();
}
void servo4(int position) {
serwo4.attach(8);
serwo4.write(position);
//delay(5);
//serwo.detach();
}

void servo_off() {
serwo1.detach();
serwo2.detach();
serwo3.detach();
serwo4.detach();
}
