#include <Ultrasonic.h>
#include <Servo.h>
//PWM enabled pins -(9,3) 9,8,7,5,4,3
// hcsr04 any digital pin

Servo myservo;
Ultrasonic ultrasonic(11,12);
int pos=0;
const int ENA_PIN = 3; //EN1 pin L298N
const int IN1_PIN = 4; //IN1 pin L298N
const int IN2_PIN = 5; //IN2 pin L298N
const int ENB_PIN = 9; //EN2 pin L298N
const int IN3_PIN = 8; //IN1 pin L298N
const int IN4_PIN = 7; //IN2 pin L298N
// servo on pin 1
int speed;
void setup() {
  myservo.attach(1);
  pinMode(ENA_PIN, OUTPUT); //dc1
  pinMode(IN1_PIN, OUTPUT); //dc1
  pinMode(IN2_PIN, OUTPUT); //dc1
  pinMode(ENB_PIN, OUTPUT); //dc2
  pinMode(IN3_PIN, OUTPUT); //dc2
  pinMode(IN4_PIN, OUTPUT); //dc2
	Serial.begin(9600); 

  // put your setup code here, to run once:

}
// bool pol1,pol2; // polarity 1&2
void left_wheel(){
  digitalWrite(IN1_PIN, HIGH); // control motor A spins clockwise
  digitalWrite(IN2_PIN, LOW);  // control motor A spins clockwise
}
void right_wheel(){
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW); 
}
void left_wheel_rev(){
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
}
void right_wheel_rev(){
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}
void stop_wheels(){
  analogWrite(ENA_PIN, 0);
  analogWrite(ENB_PIN, 0);
}
void drive_forward(){
  right_wheel();
  left_wheel();
}
void drive_rev(){
  right_wheel_rev();
  left_wheel_rev();
}
int turn(){

  right_wheel_rev();
  left_wheel_rev();
}
void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);              
    delay(15);                       
  }
  delay(100);
  drive_forward();
  delay(40);
  if(ultrasonic.read()<200){
    for (int speed = 255; speed >= 0; speed--) {
    analogWrite(ENA_PIN, speed); // control the speed
    analogWrite(ENB_PIN, speed);
    delay(4);
    }
    stop_wheels();
    analogWrite(ENA_PIN,255);
    analogWrite(ENB_PIN,255);
    while(ultrasonic.read()<=200){
    left_wheel();
    right_wheel_rev();
    }
    stop_wheels();
    delay(40);
  }
}
