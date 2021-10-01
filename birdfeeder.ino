// Board used NodeMCU.
#include<ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<Servo.h>

// WiFi credentials:
char auth[] = "";
char ssid[] = "";
char pass[] = "";

// Pins used:
Servo myservo; // servo object.
const int washer = 0; //D3
const int trigPin = 4;  //D2
const int echoPin = 5;  //D1
// Variables:
long duration;
int empty_level; //(distance)
int count = 0;

void setup() {
    //Serial.begin(9600);
    myservo.attach(15);// Servo connected to D8
    myservo.write(0);
    Blynk.begin(auth, ssid, pass);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(washer, OUTPUT);

}
// Function for measurement of food containers empty level by Ultrasonic sensor(hc-sr04): 
void loop() {
  Blynk.run();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  empty_level= duration*0.034/2;
  Blynk.virtualWrite(V1, empty_level);
  if (empty_level >= 15 && count==0){
    Blynk.notify("Feeder is empty!!");
    count = count + 1;
  }
  else if (empty_level < 15 && count==1){
    count = count -1;  
  }
  //Serial.print("Empty level: ");
  //Serial.println(empty_level);
}

//Function for container's lid opening:
BLYNK_WRITE(V2){
   myservo.write(90);
   delay(5000);
   myservo.write(0);
}
//Function for washing the platform:
BLYNK_WRITE(V3){
   digitalWrite(washer,HIGH);
   delay(10000);
   digitalWrite(washer,LOW);
}
