/*
* Nunchuck Example
* Reads an Official Nunchuck Controler and prints the joystick position
*
*Wiring:
*Connect Nunchuck to the Arduinos I2C Bus
*using a 3.3V level shifter.
*
* By: Joseph Diaz
*/

#include <Nunchuck.h>
#include <Wire.h>

Nunchuck nunchuck;

void setup(){
  //Initialize Serial
  Serial.begin(9600);
  //Initialize Nunchuck
  nunchuck.begin();
  
  //Calibrate Nunchuck
  Serial.println("Center joystick and press C to continue.");
  nunchuck.calibrateCenter();
  Serial.println("Move joystick in all directions, then press C to continue.");
  nunchuck.calibrateRange();
  Serial.println("Calibrated.");
}

void loop(){
  //Read Nunchuck Memory
  nunchuck.read();
  
  //Print Scaled Joystick Position
  Serial.print("Joystick X: ");
  Serial.print(nunchuck.getPercentJoyX());
  Serial.println(" Josytick Y: ");
  Serial.println(nunchuck.getPercentJoyY());
  delay(200); 
}