#include <IRremote.h>
#include"nes.h"

#include"Ir_Map.h"

IRsend irsend;

void Send_key(int rawCodes[]){
irsend.sendRaw(rawCodes,sizeof(rawCodes), 38);  
}


void setup() {
  // put your setup code here, to run once:
  // Initialize serial port speed for the serial terminal
  Serial.begin(9600);
  ini_nes();
}



void loop() {
  // put your main code here, to run repeatedly:
  switch(joypad()){
  case J_UP:    Send_key(CANAL_MAS);  Serial.print("UP");break;
  case J_DOWN:  Send_key(CANAL_MENOS);Serial.print("DOWN");break;
  case J_START: Send_key(POWER);      Serial.print("I/O"); break;
  case J_SELECT:Send_key(PODER_DVD);  Serial.print("I/O DVD");break;
  }
}
