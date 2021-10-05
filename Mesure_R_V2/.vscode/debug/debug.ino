#include<Arduino.h>
#include <TM1637Display.h>

// Pines pour l'ecran
#define CLK 12 //can be any digital pin
#define DIO 10 //can be any digital pin



void setup(){
    pinMode(4,OUTPUT);
    digitalWrite(4,HIGH);

    TM1637Display display(CLK, DIO);
    display.setBrightness(7);

    display.showNumberDec(123,false,4);


}

void loop(){
    

}
