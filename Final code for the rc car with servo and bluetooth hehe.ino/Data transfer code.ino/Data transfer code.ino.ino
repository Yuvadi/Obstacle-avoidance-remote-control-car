#include <NewPing.h>
NewPing sonar(A1,A2,255);
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(9,OUTPUT);
}

void loop(){
  //read and print data
  Serial.println(sonar.ping_cm());
  if (sonar.ping_cm()<10){
    digitalWrite(9,HIGH);
  }
  else{
    digitalWrite(9,LOW);
  }
}