/*
* This code controlles (3 watts)dc motor with IR remote.
* 0xF30CFF00:- these are hexadecimal numbers which differs for 
  different remote. So NOTE hexadecimal numbers of buttons on your
  remote and change it in below code.
* Complete prototype with code is explaned in my video on youtube
  Watch the video https://youtu.be/MwPN5wPqS7M
* Look at connection diagram for seting up the prototype.
* This code is prepared by Jaydeep Gupta for JG Projects.
* Permission granted to share this code with condition that 
  this note under comment lines must me kept. 
*/
#include <IRremote.hpp>
int IRPin = 2;     // IR receiver connected to D2 Pin 
int speedPin = 5;  // EN pin  connected to D5 Pin
int dir1 = 4;      // Input 1 connected to D4 Pin
int dir2 = 6;      // Input 2 connected to D6 Pin
int mSpeed = 255;  // initial speed 
String myCom;
bool motorRunning, motorRunning1, motorRunning2, motorRunning3 = false;
bool motorRunning4, motorRunning5, motorRunning6 = false;
bool motorRunning7, motorRunning8, motorRunning9 = false;
unsigned long motorStartTime1, motorStartTime2, motorStartTime3 = 0;
unsigned long motorStartTime4, motorStartTime5, motorStartTime6 = 0;
unsigned long motorStartTime7, motorStartTime8, motorStartTime9 = 0;
bool powerButtonPressed = false;
void startMotor();
void startMotor2();
void startMotor3();
void startMotor4();
void startMotor5();
void startMotor6();
void startMotor7();
void startMotor8();
void startMotor9();
void stopMotor();

void setup() {
  Serial.begin(9600);      // setup Serial Monitor
  IrReceiver.begin(IRPin); // Start the receiver
  pinMode(speedPin, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    delay(1000);  // Must use
    long rawData = IrReceiver.decodedIRData.decodedRawData;
    IrReceiver.resume();

    if (rawData == 0xBA45FF00) { // Power button
      powerButtonPressed = !powerButtonPressed; // Toggle power button state
      if (powerButtonPressed) {
        Serial.println("Power ON");
        startMotor();
      } else {
        Serial.println("Power OFF");
        stopMotor(); // Stop the motor if power is turned off
      }
    }
    if (powerButtonPressed) {
     switch (rawData) {
      case 0xF30CFF00: // One button pressed
        if (!motorRunning1) {
          startMotor1();
          motorRunning1 = true;
          motorStartTime1 = millis(); // Record the motor start time
        }
        break;
      case 0xE718FF00: // Two button pressed
        if (!motorRunning2) {
          startMotor2();
          motorRunning2 = true;
          motorStartTime2 = millis(); 
        }
        break;
      case 0xA15EFF00: // Three button pressed
        if (!motorRunning3) {
          startMotor3();
          motorRunning3 = true;
          motorStartTime3 = millis(); 
        }
        break;
      case 0xF708FF00:
        if (!motorRunning4) {
          startMotor4();
          motorRunning4 = true;
          motorStartTime4 = millis(); 
        }
        break;
      case 0xE31CFF00:
        if (!motorRunning5) {
          startMotor5();
          motorRunning5 = true;
          motorStartTime5 = millis(); 
        }
        break;
      case 0xA55AFF00:
        if (!motorRunning6) {
          startMotor6();
          motorRunning6 = true;
          motorStartTime6 = millis(); 
        }
        break;
      case 0xBD42FF00:
        if (!motorRunning7) {
          startMotor7();
          motorRunning7 = true;
          motorStartTime7 = millis(); 
        }
        break;
      case 0xAD52FF00:
        if (!motorRunning8) {
          startMotor8();
          motorRunning8 = true;
          motorStartTime8 = millis(); 
        }
        break;
      case 0xB54AFF00:
        if (!motorRunning9) {
          startMotor9();
          motorRunning9 = true;
          motorStartTime9 = millis(); 
        }
        break;
      
      case 0xB847FF00:
       Serial.println("Stop");
       stopMotor();
        break;
      case 0xB946FF00:
       myCom="V+";
        Serial.println(myCom);
         mSpeed=mSpeed+15;
        if(mSpeed>255){
          mSpeed=255;
        }
        analogWrite(speedPin,mSpeed);
        
       break;
      case 0xEA15FF00:
        myCom="Vol-";
        Serial.println(myCom);
         mSpeed=mSpeed-15;
        if(mSpeed<100){
          mSpeed=100;
        }
        analogWrite(speedPin,mSpeed);
      
       break;
      case 0xBC43FF00:
        myCom="FF";
        Serial.println(myCom);
        digitalWrite(dir1,LOW);
        digitalWrite(dir2,HIGH);
        analogWrite(speedPin,mSpeed);
       break;
      case 0xBB44FF00:
        myCom="Rew";
        Serial.println(myCom);
        digitalWrite(dir1,HIGH);
        digitalWrite(dir2,LOW);
        analogWrite(speedPin,mSpeed);
       break;
      default: Serial.println("Function not available :)");
    
     }
     } else {
    Serial.println("press -Pwr- to turn ON");
    }
    
  }

  // Check if it's time to stop the motor
  if (motorRunning1 && (millis() - motorStartTime1) > 10000) { // 10 sec.
    stopMotor();
    motorRunning1 = false;
  }
  if (motorRunning2 && (millis() - motorStartTime2) > 20000) { // 20 sec.
    stopMotor();
    motorRunning2 = false;
  }
  if (motorRunning3 && (millis() - motorStartTime3) > 30000) { // 30 sec.
    stopMotor();
    motorRunning3 = false;
  }
  if (motorRunning4 && (millis() - motorStartTime4) > 40000) { // 40 sec.
    stopMotor();
    motorRunning4 = false;
  }
  if (motorRunning5 && (millis() - motorStartTime5) > 50000) { // 50 sec.
    stopMotor();
    motorRunning5 = false;
  }
  if (motorRunning6 && (millis() - motorStartTime6) > 60000) { // 60 sec.
    stopMotor();
    motorRunning6 = false;
  }
  if (motorRunning7 && (millis() - motorStartTime7) > 70000) { // 70 sec.
    stopMotor();
    motorRunning7 = false;
  }
  if (motorRunning8 && (millis() - motorStartTime8) > 80000) { // 80 sec.
    stopMotor();
    motorRunning8 = false;
  }
  if (motorRunning9 && (millis() - motorStartTime9) > 90000) { // 90 sec.
    stopMotor();
    motorRunning9 = false;
  }
}

void startMotor() {   //define functions
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.print("Motor started. ");
  motorRunning = true;
 
}
void startMotor1() {   //define functions
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.print("10 sec. ");
}
void startMotor2() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("20 sec.");
}
void startMotor3() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("30 sec.");
}
void startMotor4() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("40 sec.");
}
void startMotor5() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("50 sec.");
}
void startMotor6() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("60 sec.");
}
void startMotor7() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("70 sec.");
}
void startMotor8() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("80 sec.");
}
void startMotor9() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, mSpeed);
  Serial.println("90 sec.");
}

void stopMotor() {
  digitalWrite(dir1, HIGH); // Set both inputs to high to stop the motor
  digitalWrite(dir2, HIGH);
  analogWrite(speedPin, 0); // Stop applying PWM
  Serial.println("Task compl.");
 
}
