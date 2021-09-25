#include "stdio.h"
#include "Arduino.h"
#include "structures.h"


struct Circuit C1;


void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);
  //Serial.begin(19200);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

void Mesurer(Circuit C){


  return;
}
 