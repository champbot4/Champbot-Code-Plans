boolean debug = true;
int ch1;
int x;
int y;
int timmmer = 0;
const int MPU_addr=0x68;
#include<Wire.h>
#include <Servo.h>
Servo burnit;
int dgrees;
void submersion() {
  if (debug) {
  Serial.println("trying to submersion");
  }
    int FR; // Relay1
    int BR; // Relay2
    int FL; // Relay3
    int BL; // Relay4
    int Start = 1;
    int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
   // x = 0;
   // y = 0;
      FR == true;
      BR == true;
      FL == true;
      BL == true;
      timmmer == 0;

      digitalWrite(6, LOW);
      digitalWrite(4, LOW);
      digitalWrite(9, LOW);
      digitalWrite(5, LOW);
      delay(4000);

    while (Start == 1){
      Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
      AcY =Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ =Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
      delay (10);
      x = AcZ/100;
      y = AcY/100*-1;
      if (debug == true){
         //Serial.println(y);
         //Serial.println("Y");
         //Serial.println(x);
         //Serial.println("X");
         Serial.println(timmmer);
        }
      if (FR == true){
        digitalWrite(9, LOW);
        }
        else {
        digitalWrite(9, HIGH);
        }
         if (FL == true){
        digitalWrite(5, LOW);
        }
        else {
        digitalWrite(5, HIGH);
        }
        if (BR == true){
        digitalWrite(6, LOW);
        }
        else {
        digitalWrite(6, HIGH);
        }
        if (BL == true){
        digitalWrite(4, LOW);
        }
        else {
        digitalWrite(4, HIGH);
        }
        delay(1000);
        FR = true;
        FL = true;
        BR = true;
        BL = true;
      if ( x < -10){
      FR = false;
      FL = false;
      //Serial.println("yeay");
      }
      else if ( x > 10){
        BR = false;
        BL = false;
        }
        else {
          delay(10);
          }
      if ( y > 10){
        //Serial.println("YEAY");
        BR = false;
        FR = false;
        }
      else if ( y < -10){
        FL = false;
        BL = false;
        }
        else {
          delay(10);
          }
      if(x < 8 && x > -8 && y < 8 && y > -8 ){
        FR = true;
        FL = true;
        BR = true;
        BL = true;
        }
      timmmer+=1; 
      if (digitalRead(3)== HIGH){
        Start = 0;
      }
     
      if (timmmer >= 45){
        Start = 0;
        }
        
        
    }
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(9, HIGH);
  if(timmmer < 45){
    delay(10000);
  }
    digitalWrite(10, LOW);
    delay(10000);
    digitalWrite(10, HIGH);
    delay(100);    
}

//void floation() {
  
  //digitalWrite(10, LOW);
  //delay(2000);
  //digitalWrite(10, HIGH);
  //delay(100);
  //}

void clearpins() {
  if (debug) {
  Serial.println("trying to clearpins");
  }
   digitalWrite(4, HIGH);
   digitalWrite(5, HIGH);
   digitalWrite(6, HIGH);
   digitalWrite(9, HIGH);   //   Turn off relay for valve 
   digitalWrite(10, HIGH);  //   Turn off relay for valve 
   digitalWrite(12, HIGH); // Turn off relay for nichrome wire
}
int debounce2 (int inpb2){
 int j2=0;
 int i2=0;
 int cow;
 int inpvalsum2=0;
 for (int a=0; a<5; a++){
  cow = pulseIn(7, HIGH, 25000);
  if (cow <= 1000 && cow > 100){
    i2 = 1;
    }
  else {
    i2 = 0;
    }
  inpvalsum2 = inpvalsum2 + i2;
  if (debug){
    Serial.println(inpvalsum2);
    }
  delay(100);
  }
  if(inpvalsum2 >= inpb2 ){
  j2=1;
    }
  else{
    j2=0;
}
return j2;
}
int debounce (int inpb){
 int j=0;
 int i=0;
 int ch1d;
 int inpvalsum=0;
  for (int k=0; k<5; k++) {
 ch1d = pulseIn(7, HIGH, 25000); 
  if (ch1d >= 1600 && ch1d < 3000){
    
    i = 1;
    }
   else{ 
    i = 0;
  }
  inpvalsum = inpvalsum + i;
  if (debug) {
  Serial.println(inpvalsum);
  }
  delay(100);
 }
 if (inpvalsum >= inpb) {
   j =1;
 } else {
   j=0;
 }
 if (debug) {
 Serial.println("return from debounce:");
 Serial.println(j);
 }
 return j;
}
void setup() {
  // put your setup code here, to run once:
 Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(2, OUTPUT); // output
  pinMode(11, OUTPUT); // output
pinMode(3, INPUT); // Float switch
pinMode(4, OUTPUT); // Air out relay4
pinMode(5, OUTPUT); // Air out relay3
pinMode(6, OUTPUT); // Air out relay2
pinMode(7, INPUT); // Reciever input
pinMode(8, INPUT); // Inflate bladders
pinMode(9, OUTPUT); // Air out relay1
pinMode(10, OUTPUT); // Air in relay
pinMode(12, OUTPUT); // Flame thrower relay
pinMode(13, OUTPUT); // Servo
burnit.attach(13);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatly.
  clearpins();
int okaytosink=0;
int floatit = 0;
int oktofire = 0;
/*if (digitalRead(8) == HIGH){
  floation();
  }
  */
ch1 = pulseIn(7, HIGH, 25000); 
  if (debug) {
    Serial.println(ch1); 
  }
  delay(500);
if (ch1 > 1700 && ch1 < 3000){
  okaytosink=debounce(4);
}
else if (ch1 < 1200 && ch1 > 100){
// debounce2 goes here.  
  oktofire=debounce2(4);
  }

  if (okaytosink == 1){
    if (debug) {
    Serial.println("try debug okaytosink");
    }
    submersion();
  } 
  if (oktofire == 1){
    //fireflamethrower
    int dgrees;
    digitalWrite(12,LOW);
    for (dgrees = 0; dgrees<= 30; dgrees+=1){
      burnit.write(dgrees);
      delay(15);
      }
      digitalWrite(12, HIGH);
      delay(8000);
      for (dgrees = 30; dgrees>= 0; dgrees-= 1){
        burnit.write(dgrees);
        delay(15);
        }
    }  

}
