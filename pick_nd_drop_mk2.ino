#include <Servo.h>
#include <math.h>
const float a=15,b=15;
float c;
int theta=180;
int base_angle=0;
Servo servo_1;
Servo servo_2;
Servo servo_0;

void setup() {
  // put your setup code here, to run once:
servo_1.attach(9);
servo_2.attach(8);
servo_0.attach(7);
servo_1.write(180);
servo_2.write(180);
servo_0.write(0);
Serial.begin(9600);
delay(100);
}
void init_state(){
  servo_1.write(180);
  servo_2.write(180);
  servo_0.write(0);
}
void curr_state(){
  servo_1.write(theta);
  servo_2.write(theta);
  servo_0.write(base_angle);
}
void search_cycle(){
 for(theta>=180;theta--){
 //c=(a*a)+(b*b)-2*a*b*(cos(theta));
 servo_1.write(theta);
 servo_2.write(theta);
 //if(at theta object positive)
 //init_state()+drop+curr_state()
 //&&countinue;               
 delay(15);
}
theta=180;
}

void loop() {
  // put your main code here, to run repeatedly:
 for(base_angle<=180;base_angle++){
  servo_0.write(base_angle);
  search_cycle();
  //make-shift electromagnet in arduino for gripper
  delay(10);
 }
}
