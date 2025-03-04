// ===================================================================================
// Project:   Fader four (Fad4)
// Version:   v1.0
// Year:      2025
// Author:    Ronald Leenes
// Github:    https://github.com/concept-code-design/FAD4-midi
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//

#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "config.h"
#include "mimuz-ch55x.h"

void onCTLChange(uint8_t ch, uint8_t note, uint8_t vel);
void writeEEPROM();
void readEEPROM();
void PROGBOOT_now();

// hardware
#define INSTRUMENT_TYPE 40 // this is a Fad4
#define FW_VERSION    10

__xdata const uint8_t faderPin[] = {11, 14, 15, 32};
__xdata uint8_t previousValue[] = {0,0,0,0};
__xdata uint8_t sensorValue = 0;
__xdata uint8_t MIDI_CHANNEL = 10;
__xdata uint8_t CC[4];//3, 9, 14, 15};
__xdata const uint8_t hyst = 2; //hysteresis
#define PLAY_MODE 0
#define PROG_MODE 1
#define PROG_DONE 2
__xdata uint8_t currentMode = PLAY_MODE;

void PROGBOOT_now(void){
  USB_CTRL = 0;
  EA = 0;
  TMOD = 0;
  __asm lcall #BOOT_LOAD_ADDR __endasm;
}

void setup() {
  for (int i = 0 ; i < 4; i++) pinMode(faderPin[i],INPUT); 
  for (int i = 0 ; i < 4; i++) previousValue[i] = map(analogRead(faderPin[i]), 0, 255, 0, 127);
  setHdlCtlChange(onCTLChange);
  USBInit();
  readEEPROM();
}

void loop() {
  for (int i = 0 ; i < 4; i++) {
    sensorValue = analogRead(faderPin[i]);
    if ((sensorValue > (previousValue[i] + hyst)) || (sensorValue < (previousValue[i] - hyst))){
      sendCtlChange(MIDI_CHANNEL - 1, CC[i], sensorValue); 
      previousValue[i] = sensorValue;
    }
  }
    processMidiMessage();
}

void readEEPROM(){
  MIDI_CHANNEL = eeprom_read_byte(0);
  for (int i = 0; i < 4; i++) {
    CC[i] = eeprom_read_byte(1+i);
  }
}

void writeEEPROM(){
  eeprom_write_byte(0, MIDI_CHANNEL);
  delay(50);
  for (int i = 0; i < 4; i++) {
    eeprom_write_byte(1+i, CC[i]);
    delay(50);
  }
}

void onCTLChange(uint8_t ch, uint8_t note, uint8_t vel) {
  __xdata uint8_t type = 0;
  __xdata uint8_t key = 0;
   
  ch = getChannel();
  note = getNote();
  vel =  getVel();
  type = note / 10;       // type ranges from 1 – note, 2 - CC_TOGGLE, 3 - CC_MOMENTARY, 4 - ENCODER
  key = (note % 10) - 1;  // we number keys from 1..7 (1..6 are keys, 7 is the encoder) 
if ((ch == 10) && (note == 102)) {
    if (vel > 127)sendNoteOn(3, note, vel);
    switch (vel){
      case 42:
          currentMode = PROG_MODE; // enter configuration mode
          sendCtlChange(10, 102, 42);
          break;
      case 43:
          //currentMode = PROG_DONE;  //configuration done
          writeEEPROM();
          currentMode = PLAY_MODE;
          break;
      case 44:                    // return instrument tyoe
          sendCtlChange(10, 103, INSTRUMENT_TYPE);
          break;
      case 45:                    // return firmware version
          sendCtlChange(10, 104, FW_VERSION);
          break;
      case 46:                    // return current config
        for (int i = 0; i < 4; i++) sendCtlChange(10, i+1, CC[i]);
         break;
      case 48:                // return MIDI channel
        sendCtlChange(10, 106, MIDI_CHANNEL);
        break;
      case 49: // reboot in prog mode                            // update pixels
        PROGBOOT_now();     // jump to bootloader
        break;
      default:
        break;
    }
  }
 
  if (currentMode == PROG_MODE) {
        // handle regular keys
      if ((note > 0) && (note < 4)) CC[note-1] = vel;
        if (note == 5) {
          if ((vel > 0) && (vel < 16))  MIDI_CHANNEL = vel; else MIDI_CHANNEL = 1;
        }
  } 
}