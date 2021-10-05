#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <TM1637Display.h>




typedef struct Circuit Circuit;
struct Circuit
{
  char name[10] = "";
  int PinMesureVcc = 0;
  int pinMesureResistance = 0;
  long int Rshunt = 0;
  float Rmesure = 0;
  int distance = 0; // distance de la mesure avec la moyenne pour avoir la fiabilité de la mesure
  int MesureBruteVCC = 0;
  int MesureBruteResistance = 0;
  float MesureVCC = 0;
  float MesureResistance = 0;
  int pinTransistor = 0;
};

Circuit C1;
Circuit C2;
Circuit C3;
Circuit C4;

Circuit *ptrC1 = &C1;
Circuit *ptrC2 = &C2;
Circuit *ptrC3 = &C3;
Circuit *ptrC4 = &C4;

// Déclaration des fonctions
void Mesure(Circuit *);
void Constantes_setup();
void ouvrir_les_circuits(Circuit *, Circuit *, Circuit *, Circuit *);
void debug(char txt[20], int var);
void debugD(char txt[20], float var);
float MesureOptimale (Circuit *C1, Circuit *C2, Circuit *C3, Circuit *C4);
void AffichageEcran(float val);

// Déclaration des variables 
int tps = 10; // temporisation en ms entre les changements d'états des circuits
bool ModeDebug = false;
int pinK = 3; // (led des kilo)

// Pines pour l'ecran
#define CLK 12 //can be any digital pin
#define DIO 10 //can be any digital pin

void setup()
{

  pinMode(pinK, OUTPUT); // led Kilo
  Serial.begin(115200);
  delay(100);

  // SETUP STRUCTURES
  C1.PinMesureVcc = 0;
  C1.pinMesureResistance = 4;
  C1.Rshunt =10;
  C1.pinTransistor = 2;
  strcpy(C1.name, "C1");

  C2.PinMesureVcc = 1;
  C2.pinMesureResistance = 4;
  C2.Rshunt = 330;
  C2.pinTransistor = 5;
  strcpy(C2.name, "C2");

  C3.PinMesureVcc = 2;
  C3.pinMesureResistance = 4;
  C3.Rshunt = 5100;
  C3.pinTransistor = 8;
  strcpy(C3.name, "C3");

  C4.PinMesureVcc = 3;
  C4.pinMesureResistance = 4;
  C4.Rshunt = 1000000;
  C4.pinTransistor = 11;
  strcpy(C4.name, "C4");

  // Pines OUT
  pinMode(C1.pinTransistor, OUTPUT);
  pinMode(C2.pinTransistor, OUTPUT);
  pinMode(C3.pinTransistor, OUTPUT);
  pinMode(C4.pinTransistor, OUTPUT);
  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3, ptrC4);

  // Setup Ecran
  TM1637Display display(CLK, DIO);
  display.setBrightness(7);
}

void loop()
{
  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3, ptrC4);
  digitalWrite(C1.pinTransistor, HIGH);
  delay(tps);
  Mesure(ptrC1);



  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3, ptrC4);
  digitalWrite(C2.pinTransistor, HIGH);
  delay(tps);
  Mesure(ptrC2);

  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3, ptrC4);
  digitalWrite(C3.pinTransistor, HIGH);
  delay(tps);
  Mesure(ptrC3);
  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3, ptrC4);

  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3, ptrC4);
  digitalWrite(C4.pinTransistor, HIGH);
  delay(tps);
  Mesure(ptrC4);
  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3, ptrC4);

  float MesureFinale = MesureOptimale (ptrC1,ptrC2,ptrC3,ptrC4);
  Serial.println(MesureFinale);

  debug("DEBUG LOOP ----------------------------------------------------",0);

  debug("C1.MesureBruteVCC", C1.MesureBruteVCC);
  debug("C1.MesureBruteResistance", C1.MesureResistance);
  debugD("C1.MesureVCC", C1.MesureVCC);
  debugD("C1.MesureResistance", C1.MesureResistance);
  debugD("C1.Rmesure", C1.Rmesure);
  debug("C1.distance", C1.distance);

  debug("C2.MesureBruteVCC", C2.MesureBruteVCC);
  debug("C2.MesureBruteResistance", C2.MesureBruteResistance);
  debugD("C2.MesureVCC", C2.MesureVCC);
  debugD("C2.MesureResistance", C2.MesureResistance);
  debugD("C2.Rmesure", C2.Rmesure);
  debug("C2.distance", C2.distance);

  debug("C3.MesureBruteVCC", C3.MesureBruteVCC);
  debug("C3.MesureBruteResistance", C3.MesureBruteResistance);
  debugD("C3.MesureVCC", C3.MesureVCC);
  debugD("C3.MesureResistance", C3.MesureResistance);
  debugD("C3.Rmesure", C3.Rmesure);
  debug("C3.distance", C3.distance);

  debug("C4.MesureBruteVCC", C4.MesureBruteVCC);
  debug("C4.MesureBruteResistance", C4.MesureBruteResistance);
  debugD("C4.MesureVCC", C4.MesureVCC);
  debugD("C4.MesureResistance", C4.MesureResistance);
  debugD("C4.Rmesure", C4.Rmesure);
  debug("C4.distance", C4.distance);

  debug("///// FIN DEBUG LOOP ----------------------------------------------------",0);

  debugD("MesureFinale", MesureFinale);
  AffichageEcran(MesureFinale);



  delay(2000);
}

/*
Mesure la resistance avec le circuit C
@param Circuit est la structure qui definit le circuit  
*/
void Mesure(Circuit *C){
  
  debug("Entree dans la Fonction mesure",0);

  C->MesureBruteVCC = analogRead(C->PinMesureVcc);                     //Mesures brutes
  C->MesureBruteResistance = analogRead(C->pinMesureResistance);

  C->MesureVCC = (float)C->MesureBruteVCC / 1024 *5;                      //Mesures en V
  C->MesureResistance = (float)C->MesureBruteResistance / 1024 * 5;

  C->Rmesure = (float)C->MesureResistance / (C->MesureVCC - C->MesureResistance) * C->Rshunt;
  C->distance = abs((1024 - C->MesureBruteVCC /2 ) - C->MesureBruteResistance);

  debug(C->name,0);
  debug("C->MesureBruteVCC",C->MesureBruteVCC);
  debug("C->MesureBruteResistance",C->MesureBruteResistance);
  debugD("C->MesureeVCC",C->MesureVCC);
  debugD("C->MesureResistance",C->MesureResistance);
  debugD("C->Rmesure",C->Rmesure);



  if(C->Rmesure < 0){ // possibnle pour les grandes resistances avec un Rshunt petit
    C->distance = 2000;
  }

  debug("Sortie de la Fonction mesure",0);

  return;
}


/*
Cette fonction ouvre les 3 circuits via les transistors 2n2222
@param *C1 *C2 *C3 et *C4 sont les pointeurs des 4 différents circuits
*/
void ouvrir_les_circuits(Circuit *C1, Circuit *C2, Circuit *C3, Circuit *C4){
  digitalWrite(C1->pinTransistor, LOW);
  digitalWrite(C2->pinTransistor, LOW);
  digitalWrite(C3->pinTransistor, LOW);
  digitalWrite(C4->pinTransistor, LOW);
}


/*
Debug pour les int
*/
void debug(char txt[20], int var){
  if (ModeDebug){
    Serial.print(txt);
    Serial.print(" : ");
    Serial.println(var);
  }
  return;
}


/*
Debug pour les nombres float
*/
void debugD(char txt[20], float var){
  if (ModeDebug){
    Serial.print(txt);
    Serial.print(" : ");
    Serial.println(var);
  }
  return;
}

/*
Cette fonction regarde la distance de chaque mesure avec le point central de l'ADC pour déterminer quelle est la mesure l aplus précise.
*/
float MesureOptimale (Circuit *C1, Circuit *C2, Circuit *C3, Circuit *C4){

  debug("---///--- Entree dans la fonction MesureOptimale",0);
  debug("C1->distance",C1->distance);
  debugD("C1->MesureResistance",C1->MesureResistance);
  debug("C2->distance",C2->distance);
  debugD("C2->MesureResistance",C2->MesureResistance);
  debug("C3->distance",C3->distance);
  debugD("C3->MesureResistance",C3->MesureResistance);
  debug("C4->distance",C4->distance);
  debugD("C4->MesureResistance",C4->MesureResistance);
  debug("Sortie de la fonction MesureOptimale",0);

  if (C1->distance <= C2->distance && C1->distance <= C3->distance && C1->distance <= C4->distance){
    Serial.println("Circuit 1");
    debugD("C1->Rmesure",C1->Rmesure);
    return (float)C1->Rmesure;
  }
  else if (C2->distance <= C1->distance && C2->distance <= C3->distance && C2->distance <= C4->distance){
    Serial.println("Circuit 2");
    debugD("C2->Rmesure",C2->Rmesure);
    return (float)C2->Rmesure;
  }
  else if (C3->distance <= C1->distance && C3->distance <= C2->distance && C3->distance <= C4->distance){
    Serial.println("Circuit 3");
    debugD("C3->Rmesure",C3->Rmesure);
    return (float)C3->Rmesure;
  }
  else if (C4->distance <= C1->distance && C4->distance <= C2->distance && C4->distance <= C3->distance){
    Serial.println("Circuit 3");
    debugD("C3->Rmesure",C3->Rmesure);
    return (float)C4->Rmesure;
  }
  else{
    Serial.println("Grosse erreur");
    return 1;
  }
  return 1;
}

/*
Cette fonction gere l'afffichage sur l'ecran.
@param val : valeur numérique de type float qu'on veut afficher
*/
void AffichageEcran(float val){
  TM1637Display display(CLK, DIO);
  display.setBrightness(7);
  if (val<1000){
    debug("Condition 1",0);
    digitalWrite(pinK,LOW);
    display.showNumberDec(val,false,4);

  }
  else if (val < 10000){
    debug("Condition 2",0);
    digitalWrite(pinK,HIGH);
    float valD = (float) val; // val decimale
    valD /= 10;
    display.showNumberDecEx(valD, 0b01000000, false, 4, 0);
  }
  else {
    debug("Condition 3",0);
    digitalWrite(pinK,HIGH);
    val /= 1000;
    display.showNumberDec(val,false,4);
  }

  

  return;
}






















