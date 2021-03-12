#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

//SensorTemperatura
#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float Celsius = 0;
int pinLEDCalor = 11;
//SensorUltrasonico
#define trigPin 9
#define echoPin 10
long duration;
long distance;
//servomotor
Servo servo0;
//Fotoresistencia
int sensorPin = A0;
int sensorValue = 0;
int pinLEDLampara = 12;
void setup() {
  // put your setup code here, to run once:
  sensors.begin();
  Serial.begin(9600);
  pinMode(pinLEDCalor, OUTPUT);
  pinMode(pinLEDLampara, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo0.attach(7);
  servo0.write(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  //SensorDeTemperatura
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);
  //Serial.print(Celsius);
  //Serial.println("C");
  if(Celsius >= 28){
      digitalWrite(pinLEDCalor,HIGH);
      //Serial.println("PRENDIDO");
    }else{
      digitalWrite(pinLEDCalor,LOW);
      //Serial.println("APAGADO");
      }
  //SensorUltrasonico
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = duration/58.2;
  Serial.println(distance);
  if(distance <= 300){
    if(distance <= 18){
    servo0.write(90);
    delay(200);
    }else{
      servo0.write(0);
      delay(200);
      }
   delay(200);
  }
  
  //Fotorresistencia
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue, DEC);
  if(sensorValue >= 880){
      digitalWrite(pinLEDLampara,HIGH);
      //Serial.println("PRENDIDO");
    }else{
      digitalWrite(pinLEDLampara,LOW);
      //Serial.println("APAGADO");
      }
  //delay(500);
}
