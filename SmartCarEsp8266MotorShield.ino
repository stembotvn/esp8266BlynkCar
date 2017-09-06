/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * You can receive x and y coords for joystick movement within App.
 *
 * App project setup:
 *   Two Axis Joystick on V1 in MERGE output mode.
 *   MERGE mode means device will receive both x and y within 1 message
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Ultrasonic.h"
//#include <AFMotor.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

#define PWMLeft  D1
#define PWMRight D2
#define DirLeft  D3
#define DirRight D4

const char* ssid = "Thingschanging";
const char* password = "nguyennam123";
WiFiClient client;
Ultrasonic ultrasonic(D7,D8); // (Trig PIN,Echo PIN)
//char auth[] = "40d55436882b4fbf87ae0106145822bb";  //Hien Blynk App token
//char auth[] = "dbc9568d68d54604aeae1f3abcce8878";
//  char auth[] = "644e213a25a4485fa60395b4f9d0ef0d";
char auth[] = "644e213a25a4485fa60395b4f9d0ef0d";

int robotspeed = 255;
int Lspeed;
int Rspeed;


void Stop()
{
analogWrite(PWMLeft, 0);
analogWrite(PWMRight, 0);
  
}


void  Forward(int _speed)
{
analogWrite(PWMLeft, _speed);
analogWrite(PWMRight, _speed);
digitalWrite(DirLeft,LOW);
digitalWrite(DirRight,LOW);
  
}
/////////
void Backward(int Car_speed)
{
analogWrite(PWMLeft, Car_speed);
analogWrite(PWMRight, Car_speed);
digitalWrite(DirLeft,HIGH);
digitalWrite(DirRight,HIGH);  
}
////////////////////////
void Turn_Left(int Car_speed)
{
analogWrite(PWMLeft, Car_speed);
analogWrite(PWMRight, Car_speed);
digitalWrite(DirLeft,LOW);
digitalWrite(DirRight,HIGH);    
}

/////////////////
void Turn_Right(int Car_speed)
{
analogWrite(PWMLeft, Car_speed);
analogWrite(PWMRight, Car_speed);
digitalWrite(DirLeft,HIGH);
digitalWrite(DirRight,LOW);  
}
////////////////


//////////////// 
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
  pinMode (PWMLeft,OUTPUT);
  pinMode (PWMRight,OUTPUT);
  pinMode (DirLeft,OUTPUT);
  pinMode (DirRight,OUTPUT);
  digitalWrite(PWMLeft,0);
  digitalWrite(PWMRight,0);
  digitalWrite(DirLeft,0);
  digitalWrite(DirRight,0);
  
  analogWriteRange(255);
  analogWriteFreq(500);
}
////////////////////
BLYNK_WRITE(V1) {
  int x = param[0].asInt();
  int y = param[1].asInt();
  int xscale;
  int yscale;
  int DIRECTION;
  int LDIRECTION;
  int RDIRECTION;
  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);
      

    if (y >=220)   //  Robot direction = forward
   
      {
       // yscale = (y-128)* 2 + 1; 
       Forward(255);
            
        Serial.println("Go Forward");
       }
   else if (y <= 60)
      {
      // yscale = (128-y)* 2 + 1; 
       Backward(255);           
       Serial.println("Go Backward");
      }
    //robotspeed = 255;  
   else if (x >= 220) // go right
          {
          //xscale = (x -128)*2 + 1;
        Turn_Right(255);
          Serial.println("turn right");
           }
    else if(x<=60) // go left
           {
          // xscale = (128 - x)*2 + 1;
            Turn_Left(255);
       
            Serial.println("turn left");
           }   
   else if ((y<220)&&(y>60)&&(x<220)&&(x>60))
     {
          Stop();
      
     }
       
   }    
///////////////////////
BLYNK_READ(V0) // Widget in the app READs Virtal Pin V5 with the certain frequency
{
  // This command writes Arduino's uptime in seconds to Virtual Pin V5
  long range = ultrasonic.Ranging(CM);
  Blynk.virtualWrite(V0, range);
}  


void loop()
{
  Blynk.run();
}
