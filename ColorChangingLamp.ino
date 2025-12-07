#include <IRremote.h>
#include <EEPROM.h>
#define IRPin 4
#define B0 22
#define B1 12
#define B2 24
#define B3 94
#define B4 8
#define B5 28
#define B6 90
#define INCREASE 21
#define DECREASE 7
#define RED 9
#define GREEN 5
#define BLUE 10
#define REPEAT 0xFFFFFFFF
int intensity;
int color;
int lastCommand = EEPROM.read(198);
void setRed(){
  analogWrite(RED, intensity);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
}
void setGreen(){
  analogWrite(RED, 0);
  analogWrite(GREEN, intensity);
  analogWrite(BLUE, 0);
}
void setBlue(){
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, intensity);
}
void setYellow(){
  analogWrite(RED, intensity);
  analogWrite(GREEN, intensity);
  analogWrite(BLUE, 0);
}
void setCyan(){
  analogWrite(RED, 0);
  analogWrite(GREEN, intensity);
  analogWrite(BLUE, intensity);
}
void setMagenta(){
  analogWrite(RED, intensity);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, intensity);
}
void setWhite(){
  analogWrite(RED, intensity);
  analogWrite(GREEN, intensity);
  analogWrite(BLUE, intensity);
}
void setColor(int c){
  switch(c) {
    case 0: {
      setWhite();
      break;
    }
    case 1: {
      setRed();
      break;
    }
    case 2: {
      setYellow();
      break;
    }
    case 3: {
      setGreen();
      break;
    }
    case 4: {
      setCyan();
      break;
    }
    case 5: {
      setBlue();
      break;
    }
    case 6: {
      setMagenta();
      break;
    }
  }
}

void setup() {
  IrReceiver.begin(IRPin);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  intensity = EEPROM.read(190);
  if(intensity == 0xFF || intensity == 0) intensity = 225;
  color = EEPROM.read(194);
  if(color > 6 || color == 0xFF) color = 0;
  lastCommand = EEPROM.read(198);
  if(lastCommand == 0xFF) lastCommand = B0;
  setColor(color);
}

void loop() {
  if(IrReceiver.decode()){
    int command = IrReceiver.decodedIRData.command;
    if (command == REPEAT) {
      command = lastCommand;
    } else {
      lastCommand = command;
      EEPROM.write(198, lastCommand);
    }
    switch(command){
      case B0: {
        color = 0;
        EEPROM.write(194, color);
        break;
      }
      case B1: {
        color = 1;
        EEPROM.write(194, color);
        break;
      }
      case B2: {
        color = 2;
        EEPROM.write(194, color);
        break;
      }
      case B3: {
        color = 3;
        EEPROM.write(194, color);
        break;
      }
      case B4: {
        color = 4;
        EEPROM.write(194, color);
        break;
      }
      case B5: {
        color = 5;
        EEPROM.write(194, color);
        break;
      }
      case B6: {
        color = 6;
        EEPROM.write(194, color);
        break;
      }
      case DECREASE: {
        int newIntensity = intensity - 16;
        if(newIntensity <= 0) intensity = 1;
        else intensity = newIntensity;
        EEPROM.write(190, intensity);
        break;
      }
      case INCREASE: {
        int newIntensity = intensity + 16;
        if(newIntensity >= 255) intensity = 255;
        else intensity = newIntensity;
        EEPROM.write(190, intensity);
        break;
      }
    }
    setColor(color);
    IrReceiver.resume();
  }
}
