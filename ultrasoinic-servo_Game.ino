//© Avi Herman and Shoshana Horoitz 2018

#include <Servo.h> // includes the servo library
#include <NewPing.h> // includes the NewPing library
#include <Wire.h> // includes the wire library
#include <LiquidCrystal_I2C.h> // includes the LiquidCrystal_I2C library

Servo control; // create servo object to control a servo
Servo ultra; // create servo object to control a servo

const int trigPin = 8; // for ultrasonic
const int echoPin = 9; // for ultrasonic
int randNum; // variable for random number which reads to the control servo
int angle = 1;  // varible which needs to match the randNum in order to win

NewPing sonar(trigPin, echoPin, 100); // for ultrasonic

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // delcares I2C pins

void setup() { // the setup void
  control.attach(10); // attaches the control servo on pin 9
  ultra.attach(11); // attaches the ultrasoni c-controlled servo on pin 10
  Serial.begin(9600); // open the serial port at 9600 bps

  lcd.begin(16, 2); // defines the 16 columns and 2 rows on the lcd display
  lcd.backlight();// powers on back light

}

void loop() { //main loop
  cont_void(); // runs the cont_void function
  ultra_void(); // runs the ultra_void function

  while (angle != randNum) { // while angle IS NOT EQUAL to the randNum:
    ultra_void(); // runs the ultra_void function
    // this keeps on going until angle is equal to randNum

  }

  if (angle = randNum) { // if angle is FINALLY equal to randNum:
    lcd.clear();
    lcd.setCursor(0, 0); // defines position of cursor (first row, first column)
    lcd.print("WINNER WINNER"); // prints "WINNER WINNER" to the lcd (because its only 2x16 charecters so it has to print it on two lines)
    lcd.setCursor(0, 1); // defines position of cursor (first row, first second)
    lcd.print("CHICKEN DINNER"); // prints "CHICKEN DINNER" to the lcd (because its only 2x16 charecters so it has to print it on two lines)
    Serial.print("WIN!"); // print "WIN!" to the monitor
    Serial.print('\n'); // puts cursor on new line
    randNum = 7531; // make randNum an integer angle will never be able to match

  }

  while (angle != randNum) { // creates an empty while loop to stop the code

  }

}

void cont_void() { // makes a void for the control motor that doesn't loop which can be called in the loop later
  randNum = random(5, 86); // picks a random number from 5-86
  randNum = randNum * 2; // multiplys it by 2 so it is from 10-170
  control.write(randNum); // writes that to the control motoe
  Serial.print(randNum); // prints randNum to the monitor
  Serial.println(" "); // makes a space so win and randNum aren't squished together
  delay(500); // delays for 500 miliseconds

}

void ultra_void() { // makes a void for the ultrasonic-controlled motor that doesn't loop which can be called in the loop later
  int cm = sonar.ping_cm(); // for ultrasonic
  int angle = map(cm, 5, 85, 10, 170); // maps 5-85 cm to 10° to 170° in increments of 2 for the degrees (2-34 if we need to do the five thing again)
  angle = constrain(angle, 10, 170); // constrains it to only 10-170
  ultra.write(angle); // writes angle to the ultrasonic-controlled servo
  Serial.print('\n'); // makes a new line
  Serial.print(angle); // prints angle to the serial monitor

  lcd.setCursor(0, 0); // defines position of cursor (first row, first column)
  lcd.print("Control = "); // prints "Control = " to the lcd
  lcd.print(randNum); // prints the randNum to the lcd on the same line

  lcd.setCursor(0, 1); // defines position of cursor (first row, second column)
  lcd.print("Ultra = "); // prints "Ultra = " to the lcd
  lcd.setCursor(8, 1); // defines position of cursor (first row, eighth column)
  lcd.print("     "); // prints spaces so the lcd dosen't get messy
  lcd.setCursor(8, 1); // defines position of cursor (first row, eighth column)
  lcd.print(angle); // prints angle to the lcd on the same line
  delay(100); // delays for 100 miliseconds so there is no crazy rapid readout

}
