//Author: Ryan Bowers
//Updated by Billy Straub
//Sketch to drive a control board, process values, and transmit desired actions to blimp via XBee

//Libraries to include
#include <XBee.h>

//Pin definitions
#define pot1_pin A0
#define pot2_pin A1
#define slidepot_pin A2
//XBee serial connection
#define XBeeSerial Serial1  //RX(D_out) is pin 18, TX(D_in) is pin 19
 
//XBee object
XBee xbee = XBee(&XBeeSerial);

//Input device values
int pot1, pot2, slidepot;
//Requested motor values
int motor1, motor2, motor3;
//String to transmit to blimp
String message;

void setup() {
  Serial.begin(9600);
  
  //pin setup
  pinMode(pot1_pin,INPUT);
  pinMode(pot2_pin,INPUT);
  pinMode(slidepot_pin,INPUT);

  //start XBee communication
  XBeeSerial.begin(9600);

}

void loop() {
  //read input devices
  pot1 = analogRead(pot1_pin);
  pot2 = analogRead(pot2_pin);
  slidepot = analogRead(slidepot_pin);
  //-------ADD/CHANGE AS NEEDED-------

  //convert to desired motor values - 0-255 for regular motors, 0-180 for servo
  //-------IMPORTANT-------
  //This is where the majority of your control board implementation happens.
  //You need to choose how to assign potentiometer and button values to motors - 
  //eg. coupling multiple motors to a single pot,
  //mapping forward/reverse to full pot range,
  //adding an on/off switch, etc.
  //Here's where your team has the most design flexibility - use it.

  //My example is a bare minimum - 1 pot/motor or servo
  motor1 = map(pot1, 0, 1023, -255, 255);
  motor2 = map(pot2, 0, 1023, -255, 255);
  motor3 = map(slidepot, 0, 1023, -255, 255);

  //Once all motor values are assigned, combine them into a single string of numbers
  //separated by commas, and transmit to the blimp.
  //ORDER MATTERS - MAKE SURE YOUR BLIMP CODE ASSIGNS THE RIGHT VALUES TO THE RIGHT MOTORS
  message = String(motor1) + ',' + String(motor2) + ',' + String(motor3);
  xbee.println(message);
  Serial.println(message);

  //Transmit ~10 times per second.
  //You can adjust if needed, but is updating more frequently really going to make these things
  //any more controllable?
  delay(100);
}
