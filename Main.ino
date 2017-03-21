

int in1=10,in2=4,in3=7,in4=8,MotorSpeed,counterleft=0,counterright=0,XbeeLight,FireMotor=5;
int result;
boolean forward,right,left,backward,count;
int enable1=11,enable2=9;

//Encoders
//volatile int stateleft = LOW;
//volatile int stateright = LOW;
//float countleft=0,countright=0;

//Servo
#include <Servo.h> 
Servo ServoX;
Servo ServoY; 
int PosX = 0,PosY=0,FlameValue=0,BiggestValueX=0,BiggestValueY=0,OldValueX=0,OldValueY=0,AngleBiggestValueY=0,AngleBiggestValueX=0;  
boolean RunOnceX=false,RunOnceY=false,SteadyX=false,SteadyY=false,OneCycle=true;

//Low batt
int LowBatt=53;

//fire
int Light1,Light2,Light3,Light4,Light5;

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(FireMotor,OUTPUT);
  
  //Servo
  ServoX.attach(12);
  ServoY.attach(13); 
 ServoY.write(12);
 ServoX.write(0);
 
 //LowBatt
pinMode(LowBatt,OUTPUT);

  Serial.begin(115200);
  Serial1.begin(115200);


}


void loop() {
  
  //LowBatt
  
  if( map(analogRead(A4),0,1023,0,5) < 4 ){
    digitalWrite(LowBatt,HIGH);
  }
  else{
    digitalWrite(LowBatt,LOW);
  }
  
  
  
  
  
  
  
  
  
  //Servo
  if(RunOnceX==1 && OneCycle==1){
    ServoX.write(PosX);
    PosX=PosX+1;
    delay(25);
  FlameValue=analogRead(A5);
  if(FlameValue>=OldValueX && BiggestValueX<=FlameValue){
    BiggestValueX=FlameValue;
    AngleBiggestValueX=PosX;

  }
 OldValueX=FlameValue;

  }
  if(PosX==110){
RunOnceX=0;
OneCycle=0;
SteadyX=true;
 RunOnceY=true;
  }
if(SteadyX==1){
  ServoX.write(AngleBiggestValueX);
  SteadyX==false;
  
 
}

// Y direction

 if(RunOnceY==1 && PosY<50){
    ServoY.write(PosY);
    PosY=PosY+1;
    delay(50);
  
  if( analogRead(A5)>=OldValueY && BiggestValueY<=analogRead(A5)){
    BiggestValueY=analogRead(A5);
    AngleBiggestValueY=PosY;
    Serial.print("Flame ValueY:");
    Serial.println(BiggestValueY);
    Serial.print("Biggest ValueY");
    Serial.println(BiggestValueY);
    Serial.print("POSITIONY");
    Serial.println(AngleBiggestValueY);
  }
 OldValueY=analogRead(A5);

  }
  if(PosY==50){

SteadyY=true;
 RunOnceY=false;
  }
if(SteadyY==1){
  ServoY.write(AngleBiggestValueY);
  SteadyY==false;
 
}















  //  Manual or automated
  XbeeLight=map(analogRead(A3),0,1023,0,5);
  //Serial communication xbee
  
    
if(Serial.available() > 0 && XbeeLight > 2){
    // Direction of Motors
    if(Serial.read()=='a') {                                                                           
      forward=0;
      right=0;
      left=0;
      backward=0;
    }
    if(Serial.read()=='b'){
      forward=1;
      right=0;
      left=0;
      backward=0;
    }  
    if(Serial.read()=='c'){
      forward=0;
      right=0;
      left=0;
      backward=1;
    }  
    if(Serial.read()=='d'){
      forward=0;
      right=1;
      left=0;
      backward=0;
    }  
    if(Serial.read()=='e'){
      forward=0;
      right=0;
      left=1;
      backward=0;
    }  
    if(Serial.read()=='f'){
      forward=1;
      right=1;
      left=0;
      backward=0;
    }
    if(Serial.read()=='g'){
      forward=1;
      right=0;
      left=1;
      backward=0;
    }
       if(Serial.read()=='h'){
      digitalWrite(FireMotor,HIGH);
      RunOnceX=1;
      
    }
       if(Serial.read()=='i'){
     digitalWrite(FireMotor,LOW);
    }
  }

  /*
   //Motor Speed
   if(Serial.read()=='j'){
   MotorSpeed=0;
   }
   if(Serial.read()=='k'){
   MotorSpeed=51;
   }
   if(Serial.read()=='l'){
   MotorSpeed=102;
   }
   if(Serial.read()=='m'){
   MotorSpeed=153;
   }
   if(Serial.read()=='n'){
   MotorSpeed=204;
   }
   if(Serial.read()=='o'){
   MotorSpeed=255;
   }
   */



  //speed of motor 1 2 
  analogWrite(enable1,255);
  analogWrite(enable2,255);
  //Read ultrasonic 1 2 3 and change value between 0 and 1

  if(XbeeLight < 2){//if xbee not available

    int voltageult0 = analogRead(A0) * (5.0 / 1023.0);
    if(voltageult0 > 1){
      voltageult0=1;
    }
    else{
      voltageult0=0;
    }
    int voltageult1 = analogRead(A1) * (5.0 / 1023.0);
    if(voltageult1 > 1){
      voltageult1=1;
    }
    else{
      voltageult1=0;
    }
    int voltageult2 = analogRead(A2) * (5.0 / 1023.0);

    if(voltageult2 > 1){
      voltageult2=1;
    }
    else{
      voltageult2=0;
    }
    //
    //result
    result=(voltageult0*2)+(voltageult1*3)+(voltageult2*4); 


    // depending on ultrasonic value , assign direction 
    //
    
    
    if(result==0){
      forward=true;
      left=false;
      right=false;
      backward=false;
    }

    if(result==5){
      forward=false;
      left=true;
      right=false;
      backward=false;
    }
    if(result==3){
      forward=true;
      left=true;
      right=false;
      backward=false;
    }

    if(result==6){
      forward=false;
      left=false;
      right=true;
      backward=false;
    }

    if(result==4){
      forward=true;
      left=false;
      right=true;
      backward=false;
    }

    if(result==9){
      forward=false;
      left=false;
      right=false;
      backward=true;
    }
   
    //Fire
    Light1= analogRead(A8);
  Light2= analogRead(A9);
  Light3= analogRead(A10);

  Light4= analogRead(A11);
  Light5= analogRead(A12);

  
  if( (Light4 >(Light2 + 20) && Light4 >(Light1 +20) && Light4 >(Light3+20)) || (Light5>(Light2+20) && Light5>(Light1+20)  && Light5>(Light3+20)) && result==0 ){
    forward=false;
      left=false;
      right=true;
      backward=false;
      delay(50);
    
    Serial.println("Right");}
    
  else if( (Light2>(Light3 +20) && Light2>(Light4 +20)  && Light2>(Light5 +20)) || (Light1>(Light3 +20) && Light1>(Light4 +20)  && Light1>(Light5 +20) ) && result==0){
    forward=false;
      left=true;
      right=false;
      backward=false;
      delay(50);
    Serial.println("Left"); }
    
    else if(Light3>Light4 && Light3>Light5 && Light3>Light1 && Light3>Light2 && result==0 ){
      forward=true;
      left=false;
      right=false;
      backward=false;  
    
    Serial.println("Forward");}
    if(Light1>950 || Light2>950 || Light3>950 || Light4>950 || Light5>950){
    forward=false;
    left=false;
    right=false;
    backward=false;
    RunOnceX=true;
    
    
    }

  }//xbee avilability

  //
  // depending on direction control motors( do not change this code)
  if(left==1 || forward==1){
    digitalWrite(in1,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
  }

  if(right==1 || forward==1){
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in2,LOW);
  }
  if(left==1 || backward==1){
    digitalWrite(in3,HIGH);
  }
  else{
    digitalWrite(in3,LOW);
  }
  if(right==1 || backward==1){
    digitalWrite(in4,HIGH);
  }
  else{
    digitalWrite(in4,LOW);
  }




  // Encoders Left and Right
/*
  attachInterrupt(0, blinkleft, CHANGE);
  attachInterrupt(1, blinkright, CHANGE);
  float countl=countleft;
  float countr=countright;
  countleft=counterleft/20;
  countright=counterright/20;
  if(countl != countleft){
    Serial1.print("L:");
    Serial1.println(countleft);
  }
  if(countr != countright){
    Serial1.print("R:");
    Serial1.println(countright);
  } 
*/


}

//Fucttions  for encoders
/*
void blinkleft()
{
  stateleft = !stateleft;
  counterleft=counterleft+1;

}
*/



