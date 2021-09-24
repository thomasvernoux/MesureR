int pinmesureVCC;
int pinmesureResistance;
double Rshunt;
double mesureVCC;
double mesureVshunt;
double dV;
double i;
double Rmesure;
double mesureResistance;
double mesureFinale;

// Config ecran

#include <TM1637Display.h>
#define CLK 9 //can be any digital pin
#define DIO 8 //can be any digital pin

void afficher(String chaine, double valeur);



int pinT1 = 3;
int pinT2 = 4;
int pinT3 = 5;


int pinmesureCA1 = 1;
int pinmesureCA2 = 4;

int pinK = 6;

int MesureBrute1;
int MesureBrute2;
int MesureBrute3;
int MesureBrute1VCC;
int MesureBrute2VCC;
int MesureBrute3VCC;

int tpsDelay = 1000;

void setup() {

  // Ecran
  TM1637Display display(CLK, DIO);
  display.setBrightness(7);
  
  
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);

  pinMode(pinT1,OUTPUT);
  pinMode(pinT2,OUTPUT);
  pinMode(pinT3,OUTPUT);
  pinMode(6,OUTPUT);
  

  Serial.begin(19200);

}

void loop() {

  



// Phase 3
  digitalWrite(pinT1,LOW);
  digitalWrite(pinT2,LOW);
  digitalWrite(pinT3,HIGH);
  
  delay(tpsDelay);
  pinmesureVCC = 4;
  Rshunt = 100000;
  pinmesureResistance = 2;
  MesureBrute3VCC = analogRead(pinmesureVCC);
  mesureVCC = double(MesureBrute3VCC)/1023*5;
  
  MesureBrute3 = analogRead(pinmesureResistance);
  mesureResistance = double(MesureBrute3)/1023*5;
  dV = mesureVCC - mesureResistance;
  //i = dV/Rshunt;

  
  Rmesure = (mesureResistance*Rshunt/dV);

  double m3 = Rmesure;
  double d3 = abs(1024/2 - analogRead(pinmesureResistance));
  afficher("MesureBruteVCC3",(double)MesureBrute3VCC);
  afficher("MesureBrute3",(double)MesureBrute3);

  afficher("MesureVCC3",(double)mesureVCC);
  afficher("MesureResistance",(double)mesureResistance);

  afficher("dV",(double)dV);
  afficher("Rmesuré",(double)Rmesure);

  Serial.println();
  
  
  





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
