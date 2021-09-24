

/*
 * VARIABLES
 */

// Pines
int 1_pinmesureVCC = A1; // Pines d'entree
int 2_pinmesureVCC = A3;
int 3_pinmesureVCC = A4;

int 123_pinmesureResistance = A2;

int pinT1 = 3; // Pines de sortie -> controle des 2n2222
int pinT2 = 4;
int pinT3 = 5;

int pinK = 6; // Pin controle LED K-Ohms


// Variables globales
double 1_Rshunt = 220;
double 2_Rshunt = 1000;
double 3_Rshunt = 100000;

int tpsDelay = 100; // en ms


/*
 * Configurations Ecran
 */

 
#include <TM1637Display.h>
#define CLK 9 
#define DIO 8

/*
 * Déclarations
 */
 
 void afficher(String chaine, double valeur); // Pour le debug




void setup() {

  // Ecran
  TM1637Display display(CLK, DIO);
  display.setBrightness(7);

  
  pinMode(1_pinmesureVCC,INPUT);
  pinMode(2_pinmesureVCC,INPUT);
  pinMode(3_pinmesureVCC,INPUT);
  pinMode(123_pinmesureResistance,INPUT);

  pinMode(pinT1,OUTPUT);
  pinMode(pinT2,OUTPUT);
  pinMode(pinT3,OUTPUT);
  pinMode(6,OUTPUT);
  

  Serial.begin(19200);

}

void loop() {

  /*
   * Circuit 1
   */

  digitalWrite(pinT2,LOW);
  digitalWrite(pinT3,LOW);
  digitalWrite(pinT1,HIGH);
  delay(tpsDelay);
  
  
  int MesureBrute1VCC = analogRead(pinmesureVCC);
  mesureVCC = double(MesureBrute1VCC)/1023*5;
 
  int MesureBrute1Resistance = analogRead(pinmesureResistance);
  mesureResistance = double(MesureBrute1Resistance)/1023*5;
  dV = mesureVCC - mesureResistance;
  double m1 = (mesureResistance*Rshunt/dV);
  double d1 = abs(1024/2 - MesureBrute1Resistance); // distance pour connaitre la fiabilité de la mesure



//
//  if (d2<d1 && d2<d3){
//    Serial.print("Résistance 2 : ");
//    Serial.println(m2);
//    Serial.println(d2);
//    mesureFinale = int(m2);
//  }
//  else if(d1<d2 && d1<d3){
//    Serial.print("Résistance 1 : ");
//    Serial.println(m1);  
//    Serial.println(d1);
//    mesureFinale = int(m1);
//  }
//  else if(d3<d2 && d3<d1){
//    Serial.print("Résistance 3 : ");
//    Serial.println(m3);  
//    Serial.println(d3);
//    mesureFinale = m3;
//    Serial.println(mesureFinale);
//  }
//  else{
//    Serial.println("ERREUR"); 
//    Serial.println(m1); 
//    Serial.println(m2); 
//    Serial.println(m3);
//    Serial.println(d1); 
//    Serial.println(d2); 
//    Serial.println(d3);  
//  }

//Serial.println("DEBUG -------------------");
//    Serial.print("m1 : ");
//    Serial.println(m1); 
//    Serial.print("m2 : ");
//    Serial.println(m2); 
//    Serial.print("m3 : ");
//    Serial.println(m3);
//    Serial.print("d1 : ");
//    Serial.println(d1); 
//    Serial.print("d2 : ");
//    Serial.println(d2); 
//    Serial.print("d3 : ");
//    Serial.println(d3); 
//    Serial.print("Mesure Brute 111 : ");
//    Serial.println(MesureBrute1);
//    Serial.print("Mesure Brute 222 : ");
//    Serial.println(MesureBrute2);
//    Serial.print("Mesure Brute 333 : ");
//    Serial.println(MesureBrute3);
//
//    Serial.print("Mesure BruteVCC 111 : ");
//    Serial.println(MesureBrute1VCC);
//    Serial.print("Mesure BruteVCC 222 : ");
//    Serial.println(MesureBrute2VCC);
//    Serial.print("Mesure BruteVCC 333 : ");
//    Serial.println(MesureBrute3VCC);
//
//Serial.println("FIN ------------------------------------------------");



  digitalWrite(pinK,LOW);
  


  if (mesureFinale >9999){
    mesureFinale /= 1000;
    digitalWrite(pinK,HIGH);
  }
TM1637Display display(CLK, DIO);
display.setBrightness(7);
display.showNumberDec(mesureFinale,false);



delay(1000);
}






void afficher(String chaine, double valeur){
  Serial.print(chaine);
  Serial.print("  : ");
  Serial.println(valeur);
  return;
}
