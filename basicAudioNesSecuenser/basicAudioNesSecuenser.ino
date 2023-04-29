#include"nes.h"
#include"pitches.h"

#define SPK 7

int secuencia[8];
byte pos=0;
byte dur=35;
byte i=0;
byte play_secuencia=HIGH;
int  retoo=35;

void setup() {
  // put your setup code here, to run once:
  DDRB =B00001111;
  PORTB=B11110000;
  delay(2000);
  pinMode(7,OUTPUT);
  ini_nes();
  for(i=0;i<8;i++){secuencia[i]=NOTE_D3;}
  tone(SPK,NOTE_FS4,10);delay(1000);noTone(SPK);
}

void show_pos(){
switch(pos){
case 0x00:PORTB=B10000000;  digitalWrite(8,HIGH);break;
case 0x01:PORTB=B11000000;  digitalWrite(8,HIGH);digitalWrite(9,HIGH);break;
case 0x02:PORTB=B01000000;  digitalWrite(9,HIGH);break;
case 0x03:PORTB=B01100000;  digitalWrite(9,HIGH);digitalWrite(10,HIGH);break; 
case 0x04:PORTB=B00100000;  digitalWrite(10,HIGH);break;
case 0x05:PORTB=B00110000;  digitalWrite(10,HIGH);digitalWrite(11,HIGH);break; 
case 0x06:PORTB=B00010000;  digitalWrite(11,HIGH);break;
case 0x07:PORTB=B00000000;  digitalWrite(8,HIGH);digitalWrite(11,HIGH);break;
}

}

void show_chance(byte dee){
i=pos;
pos=map(dee,0,255,0,7);
show_pos();
pos=i;  
}

void select_funtions(){
  while(joypad()!=0x00){
  switch(joypad()-J_SELECT){
  case J_RIGHT:retoo++;show_chance(retoo);break;
  case J_LEFT: retoo--;show_chance(retoo);break;
  case J_UP:  for(i=0;i<8;i++){secuencia[i]+=2;}break;
  case J_DOWN:for(i=0;i<8;i++){secuencia[i]-=2;}break;
  }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(pos>8){pos=0x00;}
  if(pos<0){pos=0x08;}
  
  if(play_secuencia==HIGH){
  for(i=0;i<8;i++){
  pos=i;show_pos();  
  switch(joypad()){
   case J_A:tone(SPK,secuencia[i]+20,dur);break;
   case J_B:tone(SPK,secuencia[i]-20,dur);break;
   case J_RIGHT:retoo++;break;
   case J_LEFT: retoo--;break;
   case J_UP:   secuencia[i]+=2;break;
   case J_DOWN: secuencia[i]-=2;break;
   case J_START:play_secuencia=!play_secuencia;waitpadup();break;
  }
  if(retoo<0)   {retoo=2000;}
  if(retoo>2000){retoo=0;  }
  
  tone(SPK,secuencia[i],dur); 
  delay(retoo);  
  }  
  }
  else{
  switch(joypad()){
  case J_RIGHT:pos++;show_pos();waitpadup();break;
  case J_LEFT :pos--;show_pos();waitpadup();break;
  case J_UP:  secuencia[pos]+=2;tone(SPK,secuencia[pos],dur);delay(35);break;
  case J_DOWN:secuencia[pos]-=2;tone(SPK,secuencia[pos],dur);delay(35);break;
  case J_START:play_secuencia=!play_secuencia;waitpadup();break;
  case J_A:dur++;show_chance(dur);break;
  case J_B:dur--;show_chance(dur);break;
  case J_SELECT:select_funtions();break;
  case J_A+J_B:        for(i=0;i<8;i++){secuencia[i]=secuencia[pos];}break;
  }  
  }
  noTone(SPK);
}
