#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <Arduino.h>






typedef struct Circuit Circuit;
struct Circuit{
    char name[10] = "";
    int PinMesureVcc = 0;
    int pinMesureResistance = 0;
    int Rshunt = 0;
    double Rmesure = 0;
    int distance = 0; // distance de la mesure avec la moyenne pour avoir la fiabilité de la mesure
    int MesureBruteVCC = 0;
    int MesureBruteResistance = 0;
    int pinTransistor = 0;
};

Circuit C1;
Circuit C2;
Circuit C3;

Circuit *ptrC1 = &C1;
Circuit *ptrC2 = &C2;
Circuit *ptrC3 = &C3;


void Mesure(Circuit*);
void Constantes_setup();
void changer_circuit(Circuit*);




void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  Mesure(ptrC1);
  

  /* SETUP STRUCTURES */
  C1.PinMesureVcc = 1;
  C1.pinMesureResistance = 2;
  C1.Rshunt = 220;
  C1.pinTransistor = 3;
  strcpy(C1.name,"C1");

  C2.PinMesureVcc = 3;
  C2.pinMesureResistance = 2;
  C2.Rshunt = 1000;
  C2.pinTransistor = 4;
  strcpy(C2.name,"C2");

  C3.PinMesureVcc = 4;
  C3.pinMesureResistance = 2;
  C3.Rshunt = 100000;
  C3.pinTransistor = 5;
  strcpy(C3.name,"C3");

  /* Pines OUT */
  pinMode(C1.pinTransistor,OUTPUT);
  pinMode(C2.pinTransistor,OUTPUT);
  pinMode(C3.pinTransistor,OUTPUT);

  
}

void loop()
{


  Mesure(ptrC1);
  Mesure(ptrC2);
  Mesure(ptrC3);
  Serial.println(C1.Rmesure);
  Serial.println(C2.Rmesure);
  Serial.println(C3.Rmesure);
  

  

  delay (1000);
}



void Mesure(Circuit* C){

    C->MesureBruteVCC = analogRead(C->PinMesureVcc);
    C->MesureBruteResistance = analogRead(C->pinMesureResistance);
    C->Rmesure = C->MesureBruteResistance / (C->MesureBruteVCC - C->MesureBruteResistance) * C->Rshunt;
    C->distance = abs(1024 - C->MesureBruteResistance);

  return;
}

void changer_circuit(Circuit* C){
  if (not(strcmp(C.name,"C1"))){
    
  }

}

void 








 