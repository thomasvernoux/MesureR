#include "stdio.h"
#include <Arduino.h>





class circuit{
  int PinMesureVCC;
  int PinMesureResistance;
  int Vshunt;

  void mesure(){
    int a;

    return;
    
  }


  
};

void setup() {

  pinMode(LED_BUILTIN,OUTPUT);
  

}

void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
  delay(100);
  

}
