#include <SerialCommand.h>
#include <Servo.h>

#define blueChannel 11
#define IRChannel 10
#define servoChannel 9
#define potChannel A0

int potValue = 0;
int IRValue = 0;

SerialCommand sCmd;     // The demo SerialCommand object
Servo tapServo;  // create servo object to control the servo that will produce the tap stimulus

void setup() {
  Serial.begin(9600);
  sCmd.addCommand("opto_on",    BLED_on);          // Turns LED on to test communication, turns the onboard led on.
  sCmd.addCommand("opto_off",   BLED_off);         // Turns LED off
  sCmd.addCommand("servo",   servo);               // set servo position
  tapServo.attach(servoChannel); //attach pin X to servo motor
  pinMode(blueChannel, OUTPUT);
  pinMode(IRChannel,OUTPUT);
  // set Optochannel to off
  analogWrite(blueChannel, 255);

}//end setup

void loop() {
  // put your main code here, to run repeatedly:
  sCmd.readSerial();     // We don't do much, just process serial commands
  potValue = analogRead(potChannel);
  IRValue = map(potValue,0,1023,0,255);
  analogWrite(IRChannel,IRValue);
  //analogWrite(blueChannel, 255);
  //delay(500);
  //analogWrite(blueChannel, 0);
  //delay(100);

}//end void loop

void BLED_on(){
  int aNumber;
  char *arg;

  //Serial.println("blue intensity");
  arg = sCmd.next();
  //Serial.println(arg);
  if (arg != NULL) {
    aNumber = atoi(arg);    // Converts a char string to an integer
    aNumber = map(aNumber,100,0,0,255);
    //Serial.print("First argument was: ");
    //Serial.println(aNumber);
  }
  analogWrite(blueChannel,aNumber);
}//end BLED_on

void BLED_off(){
analogWrite(blueChannel,0);

}//end BLED_off

void servo(){
  int aNumber;
  char *arg;

  //Serial.println("blue intensity");
  arg = sCmd.next();

  if (arg != NULL) {
    aNumber = atoi(arg);    // Converts a char string to an integer
    aNumber = map(aNumber,0,100,0,255);
    //Serial.print("First argument was: ");
    //Serial.println(aNumber);
  }
}//end servo


/*
void processCommand() {
  int aNumber;
  char *arg;

  Serial.println("We're in processCommand");
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);    // Converts a char string to an integer
    Serial.print("First argument was: ");
    Serial.println(aNumber);
  }
  else {
    Serial.println("No arguments");
  }
  */