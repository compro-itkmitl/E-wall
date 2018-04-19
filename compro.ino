#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Servo.h"
#include "LedControl.h"
byte hf[8]= {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};
byte nf[8]={B00111100, B01000010,B10100101,B10000001,B10111101,B10000001,B01000010,B00111100};
byte sf[8]= {B00111100,B01000010,B10100101,B10000001,B10011001,B10100101,B01000010,B00111100};
int  mood=1, command=0;
char wheel;
long duration,cm,inches;
unsigned long timer;
int enA=9,enB=5,in1=8,in2=7,in3=4,in4=3,trig=6,echo=2;
LedControl lc=LedControl(8,10,9,1);//DIN,CLK,CS,num of display
void setup() {
  pinMode(in4,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  timer = millis();
  lc.shutdown(0,false); //start display
  lc.setIntensity(0,0);// Set b'r'ness
  lc.clearDisplay(0);   // Clear the display
} 
void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    command = Serial.read(); // Reads the data from the serial port
 }
  if (millis() - timer >= 5000){//timer of mood 
    timer = millis();
    mood--;
    Serial.println(mood);
  }
  if (command == '1') {
    mood++;
    command = 0;
  }

  if (mood <= 0) {
    mood = 0;
    sad();
  }
  else if(mood==1){
    normal();
  }
  else if(mood==2){
    happy();
    }
  sonic();
  delay(250);

  if (wheel == 'f') {
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  analogWrite(enB,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,255);
  Serial.println("'f'");
  wheel = 0;
 }
 else if (wheel == 'b') {
  digitalWrite(in4,LOW);
  digitalWrite(in3,HIGH);
  analogWrite(enB,255);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,255);
  Serial.println("'b'");
  wheel = 0;
 }
  else if (wheel == 'r') {
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
  analogWrite(enB,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,255);
  Serial.println("'r'");
  wheel = 0;
 } 
  else if (wheel == 'l') {
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  analogWrite(enB,255);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(enA,255);
  Serial.println("'l'");
  wheel = 0;
 } 
}
// use to find distance
void sonic(){
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  Serial.print(cm);
  Serial.print("cm");
  if (cm<10){
  wheel = 'l';
  }
  else if (cm>=10){
  wheel = 'f';
  }
  Serial.println();
  
}

void happy(){
  for(int i=0;i<8;i++){
      lc.setRow(0,i,hf[i]);
    }
  }
  
void sad(){
  for(int i=0;i<8;i++){
      lc.setRow(0,i,sf[i]);
    }
  }
  
void normal(){
  for(int i=0;i<8;i++){
      lc.setRow(0,i,nf[i]);
    }
  }
