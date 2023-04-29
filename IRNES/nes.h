const int A_BUTTON         = 0;
const int B_BUTTON         = 1;
const int SELECT_BUTTON    = 2;
const int START_BUTTON     = 3;
const int UP_BUTTON        = 4;
const int DOWN_BUTTON      = 5;
const int LEFT_BUTTON      = 6;
const int RIGHT_BUTTON     = 7;

#define J_START      0x80U
#define J_SELECT     0x40U
#define J_B          0x20U
#define J_A          0x10U
#define J_DOWN       0x08U
#define J_UP         0x04U
#define J_LEFT       0x02U
#define J_RIGHT      0x01U

byte nesRegister  = 0;

int nesData       = 10;    // The data pin for the NES controller

//Outputs:
int nesClock      = 8;    // The clock pin for the NES controller
int nesLatch      = 9;    // The latch pin for the NES controller

void ini_nes(){
  // Set appropriate pins to inputs
  pinMode(nesData, INPUT);
  
  // Set appropriate pins to outputs
  pinMode(nesClock, OUTPUT);
  pinMode(nesLatch, OUTPUT);
  
  // Set initial states
  digitalWrite(nesClock, LOW);
  digitalWrite(nesLatch, LOW);
  
}


byte readNesController();

byte joypad() 
{
byte joy_pad=0x00;  
nesRegister = readNesController();
delay(180);
  if (bitRead(nesRegister, A_BUTTON) == 0)
        joy_pad+=J_A;
  if (bitRead(nesRegister, B_BUTTON) == 0)
        joy_pad+=J_B;
  if (bitRead(nesRegister, SELECT_BUTTON) == 0)
        joy_pad+=J_SELECT;
  if (bitRead(nesRegister, START_BUTTON) == 0)
        joy_pad+=J_START;
  if (bitRead(nesRegister, UP_BUTTON) == 0)
        joy_pad+=J_UP;
  if (bitRead(nesRegister, DOWN_BUTTON) == 0)
        joy_pad+=J_DOWN;
  if (bitRead(nesRegister, LEFT_BUTTON) == 0)
       joy_pad+=J_LEFT;
  if (bitRead(nesRegister, RIGHT_BUTTON) == 0)
       joy_pad+=J_RIGHT; 
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
