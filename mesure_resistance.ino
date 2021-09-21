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

int tpsDelay = 100;

void setup() {

  // Ecran
  TM1637Display display(CLK, DIO);
  display.setBrightness(7);
  
  
  pinMode(pinmesureVCC,INPUT);
  pinMode(pinmesureResistance,INPUT);

  pinMode(pinT1,OUTPUT);
  pinMode(pinT2,OUTPUT);
  pinMode(6,OUTPUT);
  

  Serial.begin(19200);

}

void loop() {

  digitalWrite(pinT2,LOW);
  digitalWrite(pinT3,LOW);
  digitalWrite(pinT1,HIGH);
  
  delay(tpsDelay);
  pinmesureVCC = 1;
  Rshunt = 220;
  pinmesureResistance = 2;
  MesureBrute1VCC = analogRead(pinmesureVCC);
  mesureVCC = double(MesureBrute1VCC)/1023*5;
 
  MesureBrute1 = analogRead(pinmesureResistance);
  mesureResistance = double(MesureBrute1)/1023*5;
  dV = mesureVCC - mesureResistance;
  i = dV/Rshunt;

  
  Rmesure = (mesureResistance*Rshunt/dV);

//  Serial.print("pinmesureResistance 111: ");
//  Serial.println(mesureResistance);
//
//  Serial.print("pinmesureVcce 111: ");
//  Serial.println(mesureVCC);
//
//
//
//  Serial.print("Résistance 111 : ");
//  Serial.println(Rmesure);
  double m1 = Rmesure;
  double d1 = abs(1024/2 - analogRead(pinmesureResistance));



  // Phase 2
  digitalWrite(pinT1,LOW);
  digitalWrite(pinT3,LOW);
  digitalWrite(pinT2,HIGH);

  delay(tpsDelay);
  
  pinmesureVCC = 3;
  Rshunt = 1000;
  pinmesureResistance = 2;
  MesureBrute2VCC = analogRead(pinmesureVCC);
  mesureVCC = double(MesureBrute2VCC)/1023*5;
  
  MesureBrute2 = analogRead(pinmesureResistance);
  mesureResistance = double(MesureBrute2)/1023*5;
  dV = mesureVCC - mesureResistance;
  i = dV/Rshunt;

  
  Rmesure = (mesureResistance*Rshunt/dV);

//  Serial.print("pinmesureResistance 222: ");
//  Serial.println(mesureResistance);
//
//  Serial.print("pinmesureVcce 222: ");
//  Serial.println(mesureVCC);
//
//
//
//  Serial.print("Résistance 222 : ");
//  Serial.println(Rmesure);
  double m2 = Rmesure;
  double d2 = abs(1024/2 - analogRead(pinmesureResistance));



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

  digitalWrite(pinT1,LOW);
  digitalWrite(pinT2,LOW);
  digitalWrite(pinT3,LOW);

//  Serial.print("mesureResistance 333: ");
//  Serial.println(mesureResistance);
//
//  Serial.print("pinmesureVcce 333: ");
//  Serial.println(mesureVCC);
//
//  Serial.print("dV 333: ");
//  Serial.println(dV);
//
//  Serial.print("i 333: ");
//  Serial.println(i);
//
//
//
//
//  Serial.print("Résistance 333 : ");
//  Serial.println(Rmesure);


  if (d2<d1 && d2<d3){
    Serial.print("Résistance 2 : ");
    Serial.println(m2);
    Serial.println(d2);
    mesureFinale = int(m2);
  }
  else if(d1<d2 && d1<d3){
    Serial.print("Résistance 1 : ");
    Serial.println(m1);  
    Serial.println(d1);
    mesureFinale = int(m1);
  }
  else if(d3<d2 && d3<d1){
    Serial.print("Résistance 3 : ");
    Serial.println(m3);  
    Serial.println(d3);
    mesureFinale = m3;
    Serial.println(mesureFinale);
  }
  else{
    Serial.println("ERREUR"); 
    Serial.println(m1); 
    Serial.println(m2); 
    Serial.println(m3);
    Serial.println(d1); 
    Serial.println(d2); 
    Serial.println(d3);  
  }

Serial.println("DEBUG -------------------");
    Serial.print("m1 : ");
    Serial.println(m1); 
    Serial.print("m2 : ");
    Serial.println(m2); 
    Serial.print("m3 : ");
    Serial.println(m3);
    Serial.print("d1 : ");
    Serial.println(d1); 
    Serial.print("d2 : ");
    Serial.println(d2); 
    Serial.print("d3 : ");
    Serial.println(d3); 
    Serial.print("Mesure Brute 111 : ");
    Serial.println(MesureBrute1);
    Serial.print("Mesure Brute 222 : ");
    Serial.println(MesureBrute2);
    Serial.print("Mesure Brute 333 : ");
    Serial.println(MesureBrute3);

    Serial.print("Mesure BruteVCC 111 : ");
    Serial.println(MesureBrute1VCC);
    Serial.print("Mesure BruteVCC 222 : ");
    Serial.println(MesureBrute2VCC);
    Serial.print("Mesure BruteVCC 333 : ");
    Serial.println(MesureBrute3VCC);

Serial.println("FIN ------------------------------------------------");



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
