const int A_BUTTON         = 0;
const int B_BUTTON         = 1;
const int SELECT_BUTTON    = 2;
const int START_BUTTON     = 3;
const int UP_BUTTON        = 4;
const int DOWN_BUTTON      = 5;
const int LEFT_BUTTON      = 6;
const int RIGHT_BUTTON     = 7;

byte nesRegister  = 0;

int nesData       = 4;    // The data pin for the NES controller

//Outputs:
int nesClock      = 2;    // The clock pin for the NES controller
int nesLatch      = 3;    // The latch pin for the NES controller


byte SECUENCIA[20];
byte i=0;byte k=0;

void setup() 
{
  // Initialize serial port speed for the serial terminal
  Serial.begin(9600);
  //Keyboard.begin();
  // Set appropriate pins to inputs
  pinMode(nesData, INPUT);
  
  // Set appropriate pins to outputs
  pinMode(nesClock, OUTPUT);
  pinMode(nesLatch, OUTPUT);
  
  // Set initial states
  digitalWrite(nesClock, LOW);
  digitalWrite(nesLatch, LOW);

  pinMode(8,OUTPUT);pinMode(9,OUTPUT);pinMode(10,OUTPUT);pinMode(11,OUTPUT);
  for(i=0;i<20;i++){
  SECUENCIA[i]=rand()%4;  
  }  
}

void show_LED(byte U){
switch(U){
case 0x00:digitalWrite(8,HIGH);break;
case 0x01:digitalWrite(9,HIGH);break;
case 0x02:digitalWrite(10,HIGH);break; 
case 0x03:digitalWrite(11,HIGH);break;
default :digitalWrite(8,LOW);digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
}
}

byte joypad() 
{
 
//void loop(){
byte joy_pad=4;  
nesRegister = readNesController();
delay(180);
  if (bitRead(nesRegister, A_BUTTON) == 0)
  //joy_pad=A_BUTTON;
  joy_pad=0x04;
  if (bitRead(nesRegister, B_BUTTON) == 0)
  //joy_pad=B_BUTTON;
  joy_pad=0x02;
  if (bitRead(nesRegister, UP_BUTTON) == 0)
        joy_pad=0x02;
  if (bitRead(nesRegister, DOWN_BUTTON) == 0)
        joy_pad=0x01;
  if (bitRead(nesRegister, LEFT_BUTTON) == 0)
       joy_pad=0x03;
  if (bitRead(nesRegister, RIGHT_BUTTON) == 0)
       joy_pad=0x00;

show_LED(joy_pad);  
return joy_pad;  
}

byte readNesController() 
{  
  int tempData = 255; 
  
  digitalWrite(nesLatch, HIGH);
  digitalWrite(nesLatch, LOW);
  
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, A_BUTTON);
      digitalWrite(nesClock, HIGH);
      
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, B_BUTTON);

  // Select button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, SELECT_BUTTON);

  // Start button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, START_BUTTON);

  // Up button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, UP_BUTTON);
    
  // Down button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, DOWN_BUTTON);

  // Left button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, LEFT_BUTTON);  
    
  // Right button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, RIGHT_BUTTON);
return tempData;
}

void loop() {
  // put your main code here, to run repeatedly:

  for(i=1;i<20;i++){

    Serial.print("mostrando");
    for(k=0;k<i;k++){
    //Serial.print(SECUENCIA[k],DEC);Serial.print(k,DEC);
    show_LED(SECUENCIA[k]);delay(1000);show_LED(4);delay(1000);
    }
    for(k=0;k<i;k++){
    Serial.print("leendo");
    while(joypad()==0x04){delay(10);}
    if(joypad()!=SECUENCIA[k]){i=20;break;}
    while(joypad()!=0x04){delay(10);}
    show_LED(4);delay(2000);
    }

    
    }

  digitalWrite(8,HIGH);digitalWrite(9,HIGH);digitalWrite(10,HIGH);digitalWrite(11,HIGH);
  delay(1000);
  for(i=0;i<20;i++){
  SECUENCIA[i]=rand()%4;  
  } 
  show_LED(4);delay(1000);
}
