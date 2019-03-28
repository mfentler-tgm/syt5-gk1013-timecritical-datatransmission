#include "SPI.h"
volatile boolean received;
volatile byte Slavereceived,Slavesend;

ISR (SPI_STC_vect)
{
  Slavereceived = SPDR;                  
  received = true;                       
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(MISO,OUTPUT);   
  SPCR |= _BV(SPE); 
  
  SPI.attachInterrupt();        
    

}

void loop() {
  // put your main code here, to run repeatedly:
  if (received) {
    if (Slavereceived) {
      
    }
  }
}
