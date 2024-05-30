#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <SoftwareSerial.h>
SoftwareSerial Serial1(6,7);
int sw1=14;
int sw2=15;

int d1,d2;
#define echoPinf 5
#define pingPinf 4

#define echoPinb 3
#define pingPinb 2

int IN1=8;
int IN2=9;
int IN3=10;
int IN4=11;

int buzzer=16;

void setup() {
  
 Serial.begin(9600);
 Serial1.begin(9600);
 lcd.init();
 lcd.backlight();
 pinMode(sw1,INPUT_PULLUP);
 pinMode(sw2,INPUT_PULLUP);
 pinMode(buzzer,OUTPUT);
 digitalWrite(buzzer,LOW);
 Serial.println("SOCIAL DISTANCING ROBOT..");
 lcd.clear();
 lcd.print("SOCIAL DISTA-");
 lcd.setCursor(0,1);
 lcd.print("-NCING ROBOT..");
 delay(1000);
 while(1)
 {
  Serial.println(digitalRead(sw1));
  Serial.println(digitalRead(sw2));
  delay(2000);
 }
 }

void loop()
{
  while(1)
  {
   lcd.clear();
   lcd.print("LINE ONE");
   lcd.setCursor(0,1);
   lcd.print("SELECTED");
   delay(1000); 
    if(digitalRead(sw1)==LOW)   
    {
      
         lcd.clear();
         lcd.print("LINE ONE");
         lcd.setCursor(0,1);
         lcd.print("SELECTED");
         delay(1000);
         line1_check();
       
    }
    if(digitalRead(sw2)==LOW)   
    {
         lcd.clear();
         lcd.print("LINE TWO");
         lcd.setCursor(0,1);
         lcd.print("SELECTED");
         delay(1000);
         line2_check();
    }
  }
}
void forward()
{
  Serial.println("FORWARD");
  lcd.clear();
  lcd.print("FORWARD");
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
}
void reverse()
{
  Serial.println("REVERSE");
  lcd.clear();
  lcd.print("REVERSE");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
}
void right()
{
  lcd.clear();
  lcd.print("RIGHT");
  Serial.println("RIGHT");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
}
void left()
{
  lcd.clear();
  lcd.print("LEFT");
  Serial.println("LEFT");
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
}
void stop1()
{
  Serial.println("STOP");
  lcd.clear();
  lcd.print("STOP");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(500);
}
int ultraf_check()
{  
   long durationf, cmf;
   pinMode(pingPinf, OUTPUT);
   digitalWrite(pingPinf, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPinf, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPinf, LOW);
   pinMode(echoPinf, INPUT);
   durationf = pulseIn(echoPinf, HIGH);
   cmf =  durationf*0.034/2;
   Serial.print("Front:");
   Serial.print(cmf);
   Serial.println("cm");
   Serial.println();
   delay(100);
   return cmf;
}
int ultrab_check()
{  
   long durationb, cmb;
   pinMode(pingPinb, OUTPUT);
   digitalWrite(pingPinb, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPinb, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPinb, LOW);
   pinMode(echoPinb, INPUT);
   durationb = pulseIn(echoPinb, HIGH);
   cmb =  durationb*0.034/2;
   Serial.print("Front:");
   Serial.print(cmb);
   Serial.println("cm");
   Serial.println();
   delay(100);
  return cmb;
}
void line1_check()
{
  while(1)
  {
  if(Serial.available())
  {
   char ch=Serial.read();
   if(ch=='F')
   {
     forward();
   }
   else if(ch=='B')
   {
     reverse();
   }
   else if(ch=='R')
   {
     right();
   }
   else if(ch=='L')
   {
     left();
   }
   else if(ch=='S')
   {
     stop1();
   }
 
  }
  d1=ultraf_check();
  d2=ultrab_check();
  if(d1<20)
        {
        stop1();
        Serial.println("FRONT OBJECT DETECTED IN LINE ONE");
        lcd.clear();
         lcd.print("FRONT OBJECT");
         lcd.setCursor(0,1);
         lcd.print("IN LINE ONE");
//         delay(1000);
        digitalWrite(buzzer,HIGH);
        delay(1000);
        digitalWrite(buzzer,LOW);
        delay(1000);
        }  
        if(d2<20)
        {
        stop1();
        Serial.println("BACK OBJECT DETECTED IN LINE ONE");
        lcd.clear();
         lcd.print("BACK OBJECT");
         lcd.setCursor(0,1);
         lcd.print("IN LINE ONE");
        digitalWrite(buzzer,HIGH);
        delay(1000);
        digitalWrite(buzzer,LOW);
        delay(1000);
        }      
}
}
void line2_check()
{
  while(1){
  if(Serial.available())
  {
   char ch=Serial.read();
   if(ch=='F')
   {
     forward();
   }
   else if(ch=='B')
   {
     reverse();
   }
   else if(ch=='R')
   {
     right();
   }
   else if(ch=='L')
   {
     left();
   }
   else if(ch=='S')
   {
     stop1();
   }
  }
  d1=ultraf_check();
  d2=ultrab_check();
        forward();
       if(d1<20)
        {
        stop1();
        Serial.println("FRONT OBJECT DETECTED IN LINE TWO");
        lcd.clear();
         lcd.print("FRONT OBJECT");
         lcd.setCursor(0,1);
         lcd.print("IN LINE TWO");
//         delay(1000);
        digitalWrite(buzzer,HIGH);
        delay(1000);
        digitalWrite(buzzer,LOW);
        delay(1000);
        }  
        if(d2<20)
        {
        stop1();
        Serial.println("BACK OBJECT DETECTED IN LINE TWO");
        lcd.clear();
         lcd.print("BACK OBJECT");
         lcd.setCursor(0,1);
         lcd.print("IN LINE TWO");
        digitalWrite(buzzer,HIGH);
        delay(1000);
        digitalWrite(buzzer,LOW);
        delay(1000);
        }      
}
}
