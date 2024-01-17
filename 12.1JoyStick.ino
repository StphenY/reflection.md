#include <ezButton.h>//imports the ezButton library to facilitate joystick coding
#include <Servo.h> //imports the servo library to facilitate servo coding
#define VRX_PIN  A0 // Arduino pin connected to VRX pin - outputs joystick's X poition
#define VRY_PIN  A1 // Arduino pin connected to VRY pin - outputs joystick's Y position

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int servoPin = 9; //labels digital pin 9 for servo pin - servos work based on a pulse of electrical currents. 
//Servos, depending on the pattern, turns in a specific manner

int trigPin = 12; //labels digital pin 12 for trig pin of USS
int echoPin = 11; //labels digital pin 11 for echo pin of USS
int buzz=13; //labels digital pin 13 for peizo speaker pin 

Servo myservo; // objects are chunks of data - this creates a servo object to control the servo

long duration; //declares a long variable (64 bits) called duration
int distance; //declares a int variable called distance

void setup() {
  myservo.attach(servoPin); // sets pin 9 as the digital pin used by servo
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  double servo = yValue*0.18; // converts joystick's position to ideal servo's position


  if (servo>=180){
    myservo.write(180); //servo positions itself to 180 (right) if servo variable above is 180 or greater
  }

  myservo.write(servo); //As the code loops, the servo will constantly reposition itself depending on joystick's position

  ultrasonicSetup();

  //depending on distance, play different sounds with speaker to alert user
  if(distance<15 && distance>10){
    tone(buzz, 392.00, 500);
  }
  if(distance<=10 && distance>5){
    tone(buzz, 450.00,200);
    tone(buzz, 0,200);
  }
  if(distance<=5 && distance>3){
    tone(buzz, 500.00,200);
    tone(buzz, 0,200);
  }
  if(distance<=3){
    tone(buzz, 500.00,500);
  }
}

void ultrasonicSetup(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //sends out ultrasonic wave
  delayMicroseconds(10); //for 10 micro seconds
  digitalWrite(trigPin, LOW); //turns it off
  duration = pulseIn(echoPin, HIGH); //sets duration equal to time it took for echo pin to recieve ultra wave after bouncing off an object
  distance = duration * 0.034 / 2; //duration (time) x 0.034 (speed of sound) and divide by 2 because the ultra sonic wave bounces back
}