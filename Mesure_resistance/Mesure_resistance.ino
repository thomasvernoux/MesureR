#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <Arduino.h>

typedef struct Circuit Circuit;
struct Circuit
{
  char name[10] = "";
  int PinMesureVcc = 0;
  int pinMesureResistance = 0;
  int Rshunt = 0;
  double Rmesure = 0;
  int distance = 0; // distance de la mesure avec la moyenne pour avoir la fiabilité de la mesure
  int MesureBruteVCC = 0;
  int MesureBruteResistance = 0;
  double MesureeVCC = 0;
  double MesureResistance = 0;
  int pinTransistor = 0;
};

Circuit C1;
Circuit C2;
Circuit C3;

Circuit *ptrC1 = &C1;
Circuit *ptrC2 = &C2;
Circuit *ptrC3 = &C3;

/* Déclaration des fonctions */
void Mesure(Circuit *);
void Constantes_setup();
void changer_circuit(Circuit *);
void ouvrir_les_circuits(Circuit *, Circuit *, Circuit *);
void debug(char txt[20], int var);
void debugD(char txt[20], double var);
int MesureOptimale (Circuit *C1, Circuit *C2, Circuit *C3);

/* Déclaration des variables */
int tps = 10; // temporisation en ms entre les changements d'états des circuits
bool ModeDebug = 1;

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
  strcpy(C1.name, "C1");

  C2.PinMesureVcc = 3;
  C2.pinMesureResistance = 2;
  C2.Rshunt = 1000;
  C2.pinTransistor = 4;
  strcpy(C2.name, "C2");

  C3.PinMesureVcc = 4;
  C3.pinMesureResistance = 2;
  C3.Rshunt = 100000;
  C3.pinTransistor = 5;
  strcpy(C3.name, "C3");

  /* Pines OUT */
  pinMode(C1.pinTransistor, OUTPUT);
  pinMode(C2.pinTransistor, OUTPUT);
  pinMode(C3.pinTransistor, OUTPUT);
  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3);
}

void loop()
{

  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3);
  digitalWrite(C1.pinTransistor, HIGH);
  delay(tps);
  Mesure(ptrC1);

  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3);
  digitalWrite(C2.pinTransistor, HIGH);
  delay(tps);
  Mesure(ptrC2);

  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3);
  digitalWrite(C3.pinTransistor, HIGH);
  delay(tps);
  Mesure(ptrC3);
  ouvrir_les_circuits(ptrC1, ptrC2, ptrC3);

  int MesureFinale = MesureOptimale (ptrC1,ptrC2,ptrC3);

  debug("C1.MesureBruteVCC", C1.MesureBruteVCC);
  debug("C1.MesureBruteResistance", C1.MesureBruteResistance);
  debugD("C1.Rmesure", C1.Rmesure);
  debug("C1.distance", C1.distance);

  debug("C2.MesureBruteVCC", C2.MesureBruteVCC);
  debug("C2.MesureBruteResistance", C2.MesureBruteResistance);
  debugD("C2.Rmesure", C2.Rmesure);
  debug("C2.distance", C2.distance);

  debug("C3.MesureBruteVCC", C3.MesureBruteVCC);
  debug("C3.MesureBruteResistance", C3.MesureBruteResistance);
  debugD("C3.Rmesure", C3.Rmesure);
  debug("C3.distance", C3.distance);

  debugD("MesureFinale", MesureFinale);

  delay(1000);
}

/*
Mesure la resistance avec le circuit C
*/
void Mesure(Circuit *C)
{
  debug("Entree dans la Fonction mesure",0);

  C->MesureBruteVCC = analogRead(C->PinMesureVcc);                     //Mesures brutes
  C->MesureBruteResistance = analogRead(C->pinMesureResistance);

  C->MesureeVCC = (double)C->MesureBruteVCC / 1024 *5;                      //Mesures en V
  C->MesureResistance = (double)C->MesureBruteResistance / 1024 * 5;

  C->Rmesure = C->MesureResistance / (C->MesureeVCC - C->MesureResistance) * C->Rshunt;
  C->distance = abs(1024 - C->MesureBruteResistance);

  debugD("C->MesureeVCC",C->MesureeVCC);
  debugD("C->MesureResistance",C->MesureResistance);
  debugD("C->Rmesure",C->Rmesure);

  debug("Sortie de la Fonction mesure",0);

  return;
}

/*
Pas finie
*/
void changer_circuit(Circuit *C)
{
  if (!strcmp(C->name, "C1"))
  {
    //ouvrir_les_circuits(C1,C2,C3);
    digitalWrite(C->pinTransistor, LOW);
  }
}

/*
Cette fonction ouvre les 3 circuits via les transistors 2n2222
*/
void ouvrir_les_circuits(Circuit *C1, Circuit *C2, Circuit *C3)
{
  digitalWrite(C1->pinTransistor, LOW);
  digitalWrite(C2->pinTransistor, LOW);
  digitalWrite(C3->pinTransistor, LOW);
}


/*
Debug pour les int
*/
void debug(char txt[20], int var)
{

  if (ModeDebug)
  {
    Serial.print(txt);
    Serial.print(" : ");
    Serial.println(var);
  }

  return;
}


/*
Debug pour les nombres doubles
*/
void debugD(char txt[20], double var)
{

  if (ModeDebug)
  {
    Serial.print(txt);
    Serial.print(" : ");
    Serial.println(var);
  }

  return;
}

int MesureOptimale (Circuit *C1, Circuit *C2, Circuit *C3){

  debug("---///--- Entree dans la fonction MesureOptimale",0);
  debug("C1->distance",C1->distance);
  debugD("C1->MesureResistance",C1->MesureResistance);
  debug("C2->distance",C2->distance);
  debugD("C2->MesureResistance",C2->MesureResistance);
  debug("C3->distance",C3->distance);
  debugD("C3->MesureResistance",C3->MesureResistance);
  debug("Sortie de la fonction MesureOptimale",0);

  if (C1->distance <= C2->distance && C1->distance <= C3->distance){
    return (int)C1->Rmesure;
  }
  else if (C2->distance <= C1->distance && C2->distance <= C3->distance){
    return (int)C2->Rmesure;
  }
  else if (C3->distance <= C1->distance && C3->distance <= C2->distance){
    return (int)C3->Rmesure;
  }
  return -1;
}


















