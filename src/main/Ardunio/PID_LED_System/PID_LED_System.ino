#include "VirtualMotor.h"
#include "Controller.h"
#include <math.h>

int const potPin = A0;
int const portKP = A1;
int const portKD = A3;
VirtualMotor vm = VirtualMotor(double(101),double(1.0),0.1,double(5));
Controller controller;
long currentTime;
long lastTime = 0;
long delta_t = 0;
double dd_t;
double baseOffset = 100;
double safeOffset =1;
char inputArr[64];
double  field1;
double field2;
char field1Arr[32];
char field2Arr[32];
int delimiterDetectorValue = 0;
int clearData = 0;
int i =0;
int j = 0;



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

  while(Serial.available() && !clearData){
    char c = Serial.read();
    if( i > 30 || j >30 ){
      field1 = 0;
      field2 = 0;
      i = 0;
      j =0;
      delimiterDetectorValue = 0;
    }
    if(c == ','){
      delimiterDetectorValue = 1;
      field1Arr[i] = '\0';
    }
    else if(c != '\n' && delimiterDetectorValue != 1){
      field1Arr[i] = c;
      i++;
    }else if(c != '\n' && delimiterDetectorValue == 1){
      field2Arr[j] = c;
      j++;
    }
    else{
      clearData = 1;
      field2Arr[j] = '\0';
    }
}
  field1 = atof(field1Arr);
  field2 = atof(field2Arr);
  controller.setTarget((double)map(potVal, 0, 4095, 101, 600));
  if(clearData == 1){
    controller.setKp(field1);
    controller.setKd(field2);
    field1 = 0;
    field2 = 0;
    clearData = 0;
    delimiterDetectorValue = 0;
    i = 0;
    j = 0;
    std::fill(std::begin(field1Arr), std::end(field1Arr), NULL);
    std::fill(std::begin(field2Arr), std::end(field2Arr), NULL);
  }
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
  double percentComplete =0;
  if( controller.getTarget() - baseOffset > 0 && controller.getTarget() - baseOffset <1 ){
    percentComplete = (vm.getPosition() - safeOffset)/(controller.getTarget()- safeOffset) * 100;
  }else{
    percentComplete = (vm.getPosition() - baseOffset)/(controller.getTarget()- baseOffset) * 100;
  }
  percentComplete =  fabs(percentComplete);
  Serial.print(String(controller.getTarget()) +","+String(controller.computeError()) +","+
  String(controller.getLastError())+","+String(vm.getPosition())+","+String(controller.getKp())+","
  +String(controller.getKd())+","+String(percentComplete)+","+String(controller.getPower()) +"\n");
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
  //delay(10);
}

