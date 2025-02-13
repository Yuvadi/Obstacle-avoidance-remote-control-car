#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

// data var for the bluetooth
char t;

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 250
int distance;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

void setup(){
  // link between arduino and bluetooth
  Serial.begin(9600);
  // setting pin type
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(90); // set sensor to front

}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  if(Serial.available()){// to recieve data from bluetooth
  t = Serial.read();
  Serial.println(t);
  }
  distance = readPing();// read the distance

  if (distance <= 20){// to avoid the obsitcal
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){// to decide which side to move
      moveRight();
      delay(500);      
      moveStop();
    }
    else{
      moveLeft();
      delay(500);
      moveStop();
    }
  }
  else{
    if(t == 'F'){            //move forward
      moveForward();
    }
 
    else if(t == 'B'){      //move reverse 
      moveBackward();
    }
 
    else if(t == 'L'){      //turn right 
      moveLeft();
    }
 
    else if(t == 'R'){      //turn left 
      moveRight();
    }
 
    else if(t == 'S'){      //STOP 
      moveStop();
    }
    delay(100);
  }
  
}

int lookRight(){ //read data on the right 
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){ //read data on left
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){ // reading setting because if its outside the range the sensor reads the value 0
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){ // stopping function
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){ // to move forward function
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW); 
}

void moveBackward(){ // to move back function
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW); 
}

void moveRight(){ // to move right function
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void moveLeft(){ // to move left function 
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW); 
}