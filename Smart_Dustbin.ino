//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include <FirebaseArduino.h>
#define trigPin1 14
#define echoPin1 12
#define trigPin2 2
#define echoPin2 0
#include <Q2HX711.h>

const byte hx711_data_pin = 5;
const byte hx711_clock_pin = 4;
Q2HX711 hx711(hx711_data_pin, hx711_clock_pin);

// Set these to run example.
long duration, distance, RightSensor,LeftSensor,Percentage1,Percentage2,Percentage, level;

#define FIREBASE_HOST "smart-dustbin-1ff2d.firebaseio.com"
#define FIREBASE_AUTH "rJPkxuNuA9nPpDRO1LhmkyN4Hhwd2APTzDPS53YG"
#define WIFI_SSID "honor 9i_A54A"
#define WIFI_PASSWORD "rukjaaaa"

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
    StaticJsonBuffer<500> jsonBuffer;

  SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;
  // set value
Percentage1 = (((26 - LeftSensor) * 100) / 26);
Percentage2 = (((26 - RightSensor) * 100) / 26);
if(Percentage1 > Percentage2)
  Percentage = Percentage1;
else Percentage = Percentage2;
if( Percentage < 50)
  level = 1;
else if ( Percentage < 75)
  level = 2;
else level = 3;
// Firebase.setFloat("/dustbins/d1/percent", Percentage);

 
 //Firebase.setFloat("/dustbins/d1/Sensor1", LeftSensor);

 
 //Firebase.setFloat("/dustbins/d1/Sensor2", RightSensor);

  
  // handle error
 
  float weight = ((hx711.read()/100.0) - 83600);
  //Firebase.setFloat("/dustbins/d1/weight", weight);
  // handle error
  delay(2000);
  JsonObject& obj = jsonBuffer.createObject();
  obj["percent"] = Percentage;
  obj["sensor1"] = LeftSensor;
  obj["sensor2"] = RightSensor;
  obj["weight"] = weight;
  obj["level"] = level;
  obj["area"] = "IIIT";
  obj["latitude"] = 23.176599;
  obj["longitude"] = 80.019584;
  obj["rate"] = 4.287;
  obj["id"] = 5600931;
  Firebase.set("/dustbins/d1",obj);
  // get value 
  //Serial.print("number: ");
  //Serial.println(Firebase.getFloat("number"));
  //delay(1000);

  // remove value
  //Firebase.remove("number");
  //delay(1000);

  // set string value
  //Firebase.setString("message", "hello world");
  // handle error
  //if (Firebase.failed()) {
    //  Serial.print("setting /message failed:");
      //Serial.println(Firebase.error());  
    //  return;
  //}
  //delay(1000);
  
  // set bool value
  //Firebase.setBool("truth", false);
  // handle error
  //if (Firebase.failed()) {
    //  Serial.print("setting /truth failed:");
      //Serial.println(Firebase.error());  
      //return;
  //}
  //delay(1000);

  // append a new value to /logs
  //String name = Firebase.pushInt("logs", n++);
  // handle error
  //if (Firebase.failed()) {
     // Serial.print("pushing /logs failed:");
      //Serial.println(Firebase.error());  
      //return;
  //}
  //Serial.print("pushed: /logs/");
  //Serial.println(name);
  //delay(1000);
}
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}
