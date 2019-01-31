// © Avi Herman 2018

#include <Servo.h> // includes the servo library
#include <NewPing.h> // includes NewPing

Servo control; // create servo object to control a servo
Servo ultra; // create servo object to control a servo

int randNum; // variable for random number which reads to the control servo
int fives[33] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170};

int win = 10; // green light that turns on when the control and ultra match
int keeptrying = 11; // red light that turns of when you don't have it

const int trigPin = 9; // for ultrasonic
const int echoPin = 8; // for ultrasonic
int angle = 1;  // varible which needs to match the randNum in order to win

NewPing sonar(trigPin, echoPin, 100); // for ultrasonic

void setup() {
  control.attach(12); // attaches the control servo on pin 9
  ultra.attach(13); // attaches the ultrasonic-controlled servo on pin 10
  Serial.begin(9600); // open the serial port at 9600 bps

}

void loop() { //main loop
  cont_void(); // runs the cont_void function
  ultra_void(); // runs the ultra_void function

  while (angle != randNum) { // while angle IS NOT EQUAL to the randNum:
    digitalWrite(win, LOW); // turn green light off
    digitalWrite(keeptrying, HIGH); // turn red light on
    ultra_void(); // runs the ultra_void function
    // this keeps on going until angle is equal to randNum

  }

  if (angle = randNum) { // if angle is FINALLY equal to randNum:
    digitalWrite(keeptrying, LOW); // turn off red light
    digitalWrite(win, HIGH); // turn on green light
    Serial.print("WIN!"); // print "WIN!" to the monitor
    Serial.print('\n'); // puts cursor on new line
    randNum = 7531; // make randNum an integer angle will never be able to match

    while (angle != randNum) { // creates an empty while loop to stop the code

    }

  }

}

void cont_void() { // makes a void for the control motor that doesn't loop which can be called in the loop later
  randNum = random(fives); // picks a random number from the "fives" array
  control.write(randNum); // writes that to the control motoe
  Serial.print(randNum); // prints randNum to the monitor
  Serial.println(" "); // makes a space so win and randNum aren't squished together
  delay(500);

}

void ultra_void() { // makes a void for the ultrasonic-controlled motor that doesn't loop which can be called in the loop later
  int cm = sonar.ping_cm(); // for ultrasonic
  int angle = map(cm, 2, 34, 10, 170); // maps 2-34 cm to 10° to 170° in increments of 5 for the degrees
  ultra.write(angle); // writes angle to the ultrasonic-controlled servo
  Serial.print('\n'); // makes a new line
  Serial.print(angle); // puts the cursor on new line
  delay(100); // delays for 100 miliseconds so there is no crazy rapid readout

}
