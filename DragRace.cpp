#include<LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const byte buttonPin = 5;
const byte reactionPin = A1;
const byte finishSensor1Pin = A0;
const byte finishSensor2Pin = A5;
const byte finishSensor3Pin = A4;
const byte finishLine1 = A3;
const byte finishLine2 = A2;
const int darkThreshold = 800;
int reactionSensor;
int finishSensor1;
int finishSensor2;
int finishSensor3;
int winnerSensor1;
int winnerSensor2;
int counter = 0;
boolean finishFlag1 = false;
boolean finishFlag2 = false;
boolean finishFlag3 = false;
boolean winnerFlag1 = false;
boolean winnerFlag2 = false;
long startTime;
long stopTime1;
long stopTime2;
long stopTime3;
long stopTime4;
float reactionTime;
float raceTimeStart;
float raceTimeMiddle;
float raceTimeLast;
int led = 7;
int ledFinish1 = 4;
int ledFinish2 = 1;
const int buzzer = 6;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(ledFinish1, OUTPUT);
  pinMode(ledFinish2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop()
{

  switch(counter) {
     case 0:
      pinMode(buttonPin, INPUT_PULLUP);
      lcd.begin(16, 2);
      lcd.clear();
      lcd.print("Car #2 Timer");
      lcd.setCursor(0, 1);
      lcd.print("Push to start");
      counter++;
     break;
     case 1:
      reactionSensor = analogRead(reactionPin);
       if (reactionSensor < darkThreshold) {
        lcd.clear();
        lcd.print("FALSE START!!");
        digitalWrite(led, HIGH);
        tone(buzzer, 1000);
        delay(1000);
        noTone(buzzer);
        delay(5000);
        digitalWrite(led, LOW);
        counter = 0;
       }
       else if (digitalRead(buttonPin) == LOW) {
        lcd.clear();
        lcd.print("Go!");
        startTime = millis();
        counter++;
       }
     break;
     case 2:
      reactionSensor = analogRead(reactionPin);
       if ((finishFlag1 == false) && (reactionSensor < darkThreshold)) {
        stopTime1 = millis();
        reactionTime = stopTime1 - startTime;
        lcd.clear();
        lcd.print("R:");
        lcd.print(reactionTime / 1000, 3);
        counter++;
       }
     break;
     case 3:
        finishSensor1 = analogRead(finishSensor1Pin);
        if ((finishFlag1 == false) && (finishSensor1 < darkThreshold)) {
          stopTime2 = millis();
          raceTimeStart = stopTime2 - (reactionTime + startTime);
          lcd.setCursor(9, 0);
          lcd.print("1/3:");
          lcd.print(raceTimeStart / 1000, 1);
          counter++;
      }
      break;
      case 4:
      finishSensor2 = analogRead(finishSensor2Pin);
      if ((finishFlag2 == false) && (finishSensor2 < darkThreshold)) {
          stopTime3 = millis();
          raceTimeMiddle = stopTime3 - (raceTimeStart + reactionTime + startTime);
          lcd.setCursor(0, 1);
          lcd.print("2/3:");
          lcd.print(raceTimeMiddle / 1000, 1);
          counter++;
      }
      break;
      case 5:
      finishSensor3 = analogRead(finishSensor3Pin);
      if ((finishFlag3 == false) && (finishSensor3 < darkThreshold)) {
        stopTime3 = millis();
        raceTimeLast = stopTime3 - (raceTimeMiddle + raceTimeStart + reactionTime + startTime);
        lcd.setCursor(9, 1);
        lcd.print("3/3:");
        lcd.print(raceTimeLast / 1000 , 1);
        counter++;
      }
      break;
      case 6:
      winnerSensor1 = analogRead(finishLine1);
      winnerSensor2 = analogRead(finishLine2);
      if ((winnerFlag1 == false) && (winnerSensor1 < darkThreshold)){
         digitalWrite(ledFinish1, HIGH);
         counter++;
      }
      if ((winnerFlag2 == false) && (winnerSensor2 < darkThreshold)){
        digitalWrite(ledFinish2, HIGH);
        counter++;
      }
      break;
      case 7:
      pinMode(buttonPin, INPUT_PULLUP);
      if(digitalRead(buttonPin) == LOW){
        delay(1000);
        digitalWrite(ledFinish1, LOW);
        digitalWrite(ledFinish2, LOW);
        counter = 0;
      }
      break;
  }
}


