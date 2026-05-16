#include "VirtualMotor.h"
#include "Controller.h"

int const potPin = A0;
int const portKP = A1;
int const portKD = A3;
VirtualMotor vm = VirtualMotor(double(100),double(1.0),0.1,double(5));
Controller controller;
long currentTime;
long lastTime = 0;
long delta_t = 0;
double dd_t;




void setup() {
  // put your setup code here, to run once:
  analogReadResolution(12);
  Serial.begin(115200);
  for(int i = 3 ; i < 7; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(potPin);
  controller.setKp(((double)analogRead(portKP)/ 4095) * 0.04);
  controller.setKd(((double)analogRead(portKD) /4095) * 0.35);
  controller.setTarget((double)map(potVal, 0, 4095, 100, 600));
  Serial.print(String(controller.getTarget()) +",");
  Serial.print(String(controller.computeError()) +",");
  Serial.print(String(vm.getPosition())+",");
  Serial.print(String(controller.getKp())+",");
  Serial.print(String(controller.getKd())+",");
  currentTime = millis();
  delta_t = currentTime - lastTime;
  dd_t = delta_t / 1000.0;
  controller.setDD_T(dd_t);
  lastTime = currentTime;
  if (dd_t > 0.0015){
    controller.setCurrentPosition(vm.getPosition());
    controller.update();
    vm.update(controller.getPower(), dd_t);
  }
  double percentComplete = (vm.getPosition() - 100)/(controller.getTarget()- 100) * 100;
  Serial.print(String(percentComplete)+"\n");
  if( percentComplete <= 50){
      // Left redLight
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
  }else if ( (percentComplete > 50) && (percentComplete <=  90)){
    // left yellow light
    digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
  } else if ((percentComplete < 110 )  && (percentComplete > 90 ) ){
    // green light
    digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
  }else if ( (percentComplete >= 110) &&( percentComplete < 160 ) ){
    //  right yellow light
    digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
  } else {
  // right Red Light
    digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
  }

}

