// Final Project
// C++ code
//

const char LEDPins[5] = {'A5', 'A4', 'A3', 'A2', 'A1'};
const int buzzerPin = 7;

enum DSTATE {INIT, DG1, DG2, DG3, DG4, DG5, RG} driveState = INIT;
enum ALARM {OFF, ON} maxRPM = OFF;
char shiftUpBtn = 0, shiftDownBtn = 0, ledCount = 0, throttle = 0, gear = 0, gearRec = 0;

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
}

void loop(){

  onLEDs();
  onBuzzer();
  delay(200);
  offLEDs();
  offBuzzer();
  delay(200);

}