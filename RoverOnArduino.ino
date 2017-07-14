#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

#include <Servo.h>

Servo panServo;  // create servo object to control a servo
// a maximum of eight servo objects can be created
Servo tiltServo;  // create servo object to control a servo
// a maximum of eight servo objects can be created

int panPos = 90;
int tiltPos = 90;
int compassHeading;

//Arduino PWM Speed Control：
int Eright = 5;
int Mright = 4;
int Eleft = 6;
int Mleft = 7;

unsigned long previousMillis = 0; 
const long interval = 1000;

void setup() {
  Serial.begin(9600);

  if(!mag.begin())
  {
    while(1);
  }

  pinMode(Mright, OUTPUT);
  pinMode(Mleft, OUTPUT);
  panServo.attach(9);  // attaches the servo on pin 9 to the servo object
  tiltServo.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  panServo.write(panPos);
  tiltServo.write(tiltPos);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    compassHeading = (int) getCompassHeading();
    String output = "data," + String(compassHeading) + "," + String(panPos) + "," + String(tiltPos) + "," + "0";
    Serial.println(output);
  }
  
  if (Serial.available()){
/*
    int input = Serial.read();
  
    int hullControlCode = (input%100)%10;
    int panControlCode = input/100;
    int tiltControlCode = (input%100)/10;
*/

    String myString = Serial.readStringUntil('\n');
    int commaIndex = myString.indexOf(',');
    int secondCommaIndex = myString.indexOf(',', commaIndex + 1);
    String firstValue = myString.substring(0, commaIndex);
String secondValue = myString.substring(commaIndex + 1, secondCommaIndex);
String thirdValue = myString.substring(secondCommaIndex + 1);
int hullControlCode = firstValue.toInt();
    int panControlCode = secondValue.toInt();
    int tiltControlCode = thirdValue.toInt();
    
    //direction of driving
    if ( hullControlCode == 1 ) {
      Forward(255);
    }
    else if ( hullControlCode == 2 ) {
      ForwardLeft(255);
    }
    else if ( hullControlCode == 3 ) {
      ForwardRight(255);
    }
    else if ( hullControlCode == 4 ) {
      Reverse(255);
    }
    else if ( hullControlCode == 5 ) {
      ReverseLeft(255);
    }
    else if ( hullControlCode == 6 ) {
      ReverseRight(255);
    }
    else if ( hullControlCode == 7 ) {
      TurnLeft();
    }
    else if ( hullControlCode == 8 ) {
      TurnRight();
    }
    else {
      Stop();
    }

    //tilt control
    if ( tiltControlCode == 2 ) {
      if (tiltPos < 120)
        tiltPos++; //actually down
    }
    else if ( tiltControlCode == 1 ) {
      if (tiltPos > 0)
        tiltPos--; //actually up
    }

    //pan control
    if ( panControlCode == 1 ) {
      if (panPos < 180)
        panPos++;
    }
    else if ( panControlCode == 2 ) {
      if (panPos > 0)
        panPos--;
    }
  }
}

void Forward(int Speed) {
  digitalWrite(Mright, HIGH);
  digitalWrite(Mleft, HIGH);
  analogWrite(Eright, Speed);
  analogWrite(Eleft, Speed);
}

void ForwardLeft(int Speed) {
  digitalWrite(Mright, HIGH);
  digitalWrite(Mleft, HIGH);
  analogWrite(Eright, Speed);
  analogWrite(Eleft, Speed * 0.2);
}

void ForwardRight(int Speed) {
  digitalWrite(Mright, HIGH);
  digitalWrite(Mleft, HIGH);
  analogWrite(Eright, Speed * 0.2);
  analogWrite(Eleft, Speed);
}

void Reverse(int Speed) {
  digitalWrite(Mright, LOW);
  digitalWrite(Mleft, LOW);
  analogWrite(Eright, Speed);
  analogWrite(Eleft, Speed);
}

void ReverseLeft(int Speed) {
  digitalWrite(Mright, HIGH);
  digitalWrite(Mleft, HIGH);
  analogWrite(Eright, Speed);
  analogWrite(Eleft, Speed * 0.5);
}

void ReverseRight(int Speed) {
  digitalWrite(Mright, HIGH);
  digitalWrite(Mleft, HIGH);
  analogWrite(Eright, Speed * 0.5);
  analogWrite(Eleft, Speed);
}

void TurnLeft() {
  digitalWrite(Mright, HIGH);
  digitalWrite(Mleft, LOW);
  analogWrite(Eright, 255);
  analogWrite(Eleft, 255);
}

void TurnRight() {
  digitalWrite(Mright, LOW);
  digitalWrite(Mleft, HIGH);
  analogWrite(Eright, 255);
  analogWrite(Eleft, 255);
}

void Stop() {
  digitalWrite(Mright, HIGH);
  digitalWrite(Mleft, HIGH);
  analogWrite(Eright, 0);
  analogWrite(Eleft, 0);
}

float getCompassHeading() {
  sensors_event_t event; 
  mag.getEvent(&event);

  float Pi = 3.14159;

  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;

  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  return heading;
}





