#include<FNHR.h>

FNHR robot;

int triggerLeft = A1;
int echoLeft = A0;
int triggerRight = 21;
int echoRight = 20;
long duration = 0;
long distanceLeft = 0;
long distanceRight = 0;

void setup() {
  pinMode(triggerLeft, OUTPUT);
  pinMode(triggerRight, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(echoRight, INPUT);

  robot.SetActionSpeed(50);
  robot.Start();
}

void loop() {
  do {
    distanceLeft = measureDistance(echoLeft, triggerLeft);
    delay(10);
    distanceRight = measureDistance(echoRight, triggerRight);
    delay(10);

    if (distanceLeft >= 20 && distanceRight >= 20) {
      robot.CrawlForward();
    } else {
      if (distanceLeft <= 35 && distanceLeft < distanceRight) {
        robot.TurnRight();
        robot.TurnRight();
      } else if (distanceRight <= 35 && distanceRight < distanceLeft) {
        robot.TurnLeft();
        robot.TurnLeft();
      }
    }
  } while (distanceLeft >= 10 && distanceRight >= 10);

  for (int i = 0; i <= 5; i++) {
    robot.CrawlBackward();
  }
  do {
    distanceLeft = measureDistance(echoLeft, triggerLeft);
    delay(10);
    distanceRight = measureDistance(echoRight, triggerRight);
    delay(10);
    robot.TurnLeft();
  } while (distanceLeft <= 20 || distanceRight <= 20);
}

long measureDistance(int pinEcho, int pinTrigger) {
  digitalWrite(pinTrigger, LOW);  //makes sure Signal is noise free
  delay(1);
  digitalWrite(pinTrigger, HIGH); //send signal
  delay(5);
  digitalWrite(pinTrigger, LOW);
  duration = pulseIn(pinEcho, HIGH);  //duration till signal gets returned

  return (duration / 2) / 29.1;  //calculate to cm
}
