#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "LedControl.h"
byte hf[3][8]= {{B01000010,B11100111,B11111111,B11111111,B11111111,B01111110,B00111100,B00011000}
               ,{B00000000,B00000000,B01111110,B01111110,B01111110,B01111110,B00000000,B00000000}
               ,{B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000}
};
byte nf[3][8]={{B00111100,B01111110,B11111111,B11100111,B11100111,B11111111,B01111110,B00111100}
              ,{B00111100,B01111110,B11111111,B11111111,B11100111,B11111111,B01111110,B00111100}, 
               {B00111100,B01111110,B11111111,B11111111,B11111111,B11111111,B01111110,B00111100}
};
byte sf[2][8]={{B11111111,B11111111,B00111000,B00111000,B00011100,B00011100,B00111000,B00111000}
              ,{B11111111,B11111111,B00011100,B00011100,B00111000,B00111000,B00011100,B00011100}};
byte zf1[8]={B11111111,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B11111111};
byte zf2[8]={B11111111,B11000000,B01100000,B00110000,B00011000,B00001100,B00000110,B11111111};
byte zf3[8]={B11111111,B11111111,B01110000,B00111000,B00011100,B00001110,B11111111,B11111111};
byte arf[3][8]={{B00110000,B01111000,B11111100,B11100110,B11100111,B11111111,B01111110,B00111100}
                ,{B00110000,B01111000,B11111100,B11111110,B11100111,B11111111,B01111110,B00111100}
                ,{B00110000,B01111000,B11111100,B11111110,B11111111,B11111111,B01111110,B00111100}
};
byte alf[3][8]={{B00001100,B00011110,B00111111,B01100111,B11100111,B11111111,B01111110,B00111100}
                ,{B00001100,B00011110,B00111111,B01111111,B11100111,B11111111,B01111110,B00111100}
                ,{B00001100,B00011110,B00111111,B01111111,B11111111,B11111111,B01111110,B00111100}
};
byte x[8]={B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001};
byte startl[8]={B00111100,B00000100,B00000100,B00111100,B00000100,B00000100,B00000100,B00111100};
byte startr[8]={B10000001,B10000001,B10000001,B10011001,B10100101,B10100101,B10100101,B01000010};
SoftwareSerial mySoftwareSerial(10, 11);
DFRobotDFPlayerMini sound;
int j=2, mood=1, command=0, animation=0;
int vol=25;
char wheel;
long duration,cm,inches;
unsigned long timer,frame,now,song;
int state=0; 
int enA=9,enB=3,in1=8,in2=7,in3=4,in4=2,trig=6,echo=5;
LedControl lc=LedControl(13,A0,12,2);//DIN,CLK,CS,num of display
void setup() {
  //pin setup
  pinMode(in4,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

 
  //led setup
  lc.shutdown(0,false); //start display
  lc.setIntensity(0,0);// Set brightness
  lc.clearDisplay(0);   // Clear the display
  lc.shutdown(1,false);
  lc.setIntensity(1,0);
  lc.clearDisplay(1);
  
  //sd card setup
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!sound.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));
  for(int i=0;i<8;i++){
    lc.setColumn(0,i,startl[i]);
    lc.setColumn(1,i,startr[i]);
    }
  sound.volume(25);  //Set volume value6 From 0 to 30
  sound.play(9);
  delay(6000);
  timer = now;
  frame = now;
  song = now;
  
} 
void loop() {
  now = millis();
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    command = Serial.read(); // Reads the data from the serial port
 }
  if (now - timer >= 15000){//timer of mood 
    timer = now;
    mood--;
    if (mood==1){
    Serial.println("E-wall mood is normal");
    }
    else if (mood==-1){
    Serial.println("E-wall have gone to sleep sleep");
    }
    else if (mood==0){
    Serial.println("E-wall is sad");
    }
    else if (mood==2){
    Serial.println("E-wall is happy");
    }
    else if (mood==3){
    Serial.println("E-wall is angry don't play with him too much");
    }
  }
  sonic();
  if (command == '1') {
 
    mood++;
    timer=now;
    if (mood==1){
    Serial.println("E-wall mood is normal");
    }
    else if (mood==-1){
    Serial.println("E-wall have gone to sleep sleep");
    }
    else if (mood==0){
    Serial.println("E-wall is sad");
    }
    else if (mood==2){
    Serial.println("E-wall is happy");
    }
    else if (mood==3){
    Serial.println("E-wall is angry don't play with him too much");
    }
    
    command = 0;
  }
  else if(command =='2'){

    if(vol>0){
    sound.volume(0);
    Serial.println("Mute");
    vol = 0;}
    else{
      sound.volume(25);
      vol=25;
      Serial.println("Unmute");
      }
    command=0;
    }
  if(command=='3'){
     Serial.println("stop");
    }
  while(command =='3'){
      if(Serial.available()>0){
          command =Serial.read();
        }
      digitalWrite(in4,LOW);
      digitalWrite(in3,LOW);
      analogWrite(enB,255);
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      analogWrite(enA,255);
      sonic();
    }
  if (mood == 0) {
    sad();
    if(now-frame>=150){
      frame=now;
      if(animation==1){
          animation=0;
        }
      else{
          animation=1;
        }
    }
    if(now-song>=13000){
      sound.play(2e  );
    song=now;
    }
   
  }
  else if(mood<=-1){
    mood =-1;
    sleep();
    wheel = 's';
    if(now-song>=13000){
      song=now;
    sound.play(1);
    }
    }
  else if(mood==1){
    normal();
     if (now-frame>=250){
      frame =now;
      if(animation< j){
        animation++;
        j=2; 
        }
       else{
        j=1;
        animation--;
       }  
      }
  if(now-song>=13000){
    song=now;
    sound.play(3);
    }
  }
  else if(mood==2){
    happy();
    if(now-frame>=250){
      frame=now;
      if(animation==1){
          animation=0;
        }
      else{
          animation=1;
        }
    }
    sound.play(12);
    song=now;
    }
  else if(mood>=3){
    //angry
    angry();
    if (now-frame>=150){
      frame=now;
      if(animation<j){
        animation++;
        j=2;}
      else{
        j=1;
        animation--;}
      }
    if(now-song>=13000){
      sound.play(10);
      song=now;
    }
    mood=3;
    }
  if(wheel=='s'){
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
  analogWrite(enB,255);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(enA,255);
  }
  else if (wheel == 'f') {
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  analogWrite(enB,60);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,60);
  wheel = 0;
 }
 else if (wheel == 'b') {
  digitalWrite(in4,LOW);
  digitalWrite(in3,HIGH);
  analogWrite(enB,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,255);
  wheel = 0;
 }
  else if (wheel == 'r') {
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
  analogWrite(enB,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,255);
  wheel = 0;
 } 
  else if (wheel == 'l') {
  digitalWrite(in4,LOW);
  digitalWrite(in3,HIGH);
  analogWrite(enB,60);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(enA,60);
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
  
  if (cm<30){
  wheel = 'l';
  }
  else if (cm>=30){
  wheel = 'f';
  }
  
}



//check sd card detail
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
void happy(){
  for(int i=0;i<8;i++){
      lc.setColumn(0,i,hf[animation][i]);
      lc.setColumn(1,i,hf[animation][i]);
    }
  }
  
void sad(){
  for(int i=0;i<8;i++){
      lc.setColumn(0,i,sf[animation][i]);
      lc.setColumn(1,i,sf[animation][i]);
  }
        
  }
  
void normal(){
  for(int i=0;i<8;i++){
      lc.setColumn(0,i,nf[animation][i]);
      lc.setColumn(1,i,nf[animation][i]);
    }
  }
  
void sleep(){
  for(int i=0;i<8;i++){
      lc.setColumn(0,i,zf1[i]);
      lc.setColumn(1,i,zf1[i]);
    }

  delay(500);
  for(int i=0;i<8;i++){
      lc.setColumn(0,i,zf2[i]);
      lc.setColumn(1,i,zf2[i]);
    }
   delay(500);
  for(int i=0;i<8;i++){
      lc.setColumn(0,i,zf3[i]);
      lc.setColumn(1,i,zf3[i]);
    }
  delay(500);
   timer+=1500;
  }
void angry(){
  for(int i=0;i<8;i++){
    lc.setColumn(0,i,alf[animation][i]);
    lc.setColumn(1,i,arf[animation][i]);
    }
  }

