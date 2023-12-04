// Final Project
// C++ code
//

// LED Pin Array
const char LEDPins[] = {'A5', 'A4', 'A3', 'A2', 'A1'};

// Buzzer Pin
const int buzzerPin = 7;

#pragma region LEDDisplayJunk
/*
    comm        SYMBOL  BINARY-MASK DECIMAL HEXA
 g f | a b        0     11111100    252     0xFC 
 | | | | |        1     01100000     96     0x60 
 ---------        2     11011010    218     0xDA
10 9 8 7 6|       3     11110010    242     0xF2
|   -A-   |       4     01100110    102     0x66
| F|   |B |       5     10110110    182     0xB6
|   -G-   |       6     10111110    190     0xBE
| E|   |C |       7     11100000    224     0xE0
|   -D- * |       8     11111110    254     0xFE
|1 2 3 4 5|       9     11110110    246     0xF6
|_________|            
 | | | | |             
 e d | c dp            
    comm  
*/
// From: https://www.tinkercad.com/embed/89liBdhK3we?editbtn=1
#pragma endregion

// TINKERCAD MODEL: Cathode (Connected to negative rail)
// LED Pin Array:      a,  b, c, d, e,  f,  g, dp
byte LEDDisplay[] = {12, 13, 4, 5, 6, 11, 10, 3};
byte digits[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};

enum DSTATE {INIT, DG1, DG2, DG3, DG4, DG5, RG} driveState = INIT;
enum ALARM {OFF, ON} maxRPM = OFF;
char shiftUpBtn = 0, shiftDownBtn = 0, ledCount = 0, throttle = 0, gear = 0, gearRec = 0, gearUpFlag = 0, gearDownFlag = 0;

#pragma region OPRFUNCS

void onLEDs(){
  for(char pin : LEDPins){
    digitalWrite(pin, HIGH);
  }
}

void offLEDs(){
  for(char pin : LEDPins){
    digitalWrite(pin, LOW);
  }
}

void onBuzzer(){
  tone(buzzerPin, 200, 1000);
}

void offBuzzer(){
  noTone(buzzerPin);
}

void displayDigit(byte digit){
  byte iter = 0, mask = 0b10000000;
  while(iter < 8){
    digitalWrite(LEDDisplay[iter++], mask & digits[digit]);
    mask >>= 1;
  }
}

#pragma endregion

void tick(void) {
  
  // transitions
  switch (maxRPM){
    case OFF:
      if(!(throttle % 100)){
        maxRPM = ON;
        gearRec = gear;
      }
    break;

    case ON:
      if(gearRec != gear){
        maxRPM = OFF;
      }
  }

  switch (driveState) {
    case INIT:
      if(shiftUpBtn){
        driveState = DG1;
        gear++;
      }

      if(shiftDownBtn){
        driveState = RG;
        gear--;
      }
    break;
    
    case DG1:
      if(shiftUpBtn){
        driveState = DG2;
        gear++;
      }

      if(shiftDownBtn){
        driveState = INIT;
        gear--;
      }
    break;

    case DG2:
      if(shiftUpBtn){
        driveState = DG3;
        gear++;
      }

      if(shiftDownBtn){
        driveState = DG1;
        gear--;
      }
    break;

    case DG3:
      if(shiftDownBtn){
        driveState = DG2;
        gear--;
      }
    break;

    case RG:
      if(shiftUpBtn){
        driveState = INIT;
        gear++;
      }
    break;
  }
  
  // actions
  switch (driveState) {
    case INIT:
    break;
  }
}

void setup(){

  // LED Setup
  for(char pin : LEDPins){
    pinMode(pin, OUTPUT);
  }
  
  // Buzzer Setup
  pinMode(buzzerPin, OUTPUT);

  // LED Display Setup
  for(byte pin : LEDDisplay){
    pinMode(pin, OUTPUT);
  }
}

void loop(){

  onLEDs();
  //onBuzzer();
  //displayDigit(5);
  delay(1000);
  offLEDs();
  //offBuzzer();
  //displayDigit(8);
  delay(1000);

}