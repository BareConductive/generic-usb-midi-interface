/*******************************************************************************

 Bare Conductive Touch and Proximity USB MIDI interface
 ------------------------------------------------------

 Midi_interface_generic.ino - USB MIDI touch and proximity example

 Allows the mapping of each electrode to a key or control modulator in a
 (relatively) simple manner. See the comments for details and experiment
 for best results.

 Remember to select Bare Conductive Touch Board (USB MIDI, iPad compatible)
 in the Tools -> Board menu

 Bare Conductive code written by Stefan Dzisiewski-Smith, Pascal Loose, Szymon
 Kaliski.

 This work is licensed under a MIT license https://opensource.org/licenses/MIT

 Copyright (c) 2016, Bare Conductive

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*******************************************************************************/

// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <MPR121_Datastream.h>
#include <Wire.h>

// MIDI includes
#include "Midi_object.h"

// touch constants
const uint32_t BAUD_RATE = 115200;
const uint8_t MPR121_ADDR = 0x5C;
const uint8_t MPR121_INT = 4;

// MPR121 datastream behaviour constants
const bool MPR121_DATASTREAM_ENABLE = false;

// MIDI instantiation
MIDIEvent e;

// MIDI variable
midi_object_type MIDIobjects[12];  // create an array of MIDI objects to use (one for each electrode)

// MIDI behaviour constants
const uint8_t CHANNEL = 0;  // edit to change the channel number
const bool SET_MIDI_CONTROL = true;  // set to false to set up electrodes as touch sensitive keys

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);

  if (!MPR121.begin(MPR121_ADDR)) {
    Serial.println("error setting up MPR121");
    switch (MPR121.getError()) {
      case NO_ERROR:
        Serial.println("no error");
        break;
      case ADDRESS_UNKNOWN:
        Serial.println("incorrect address");
        break;
      case READBACK_FAIL:
        Serial.println("readback failure");
        break;
      case OVERCURRENT_FLAG:
        Serial.println("overcurrent on REXT pin");
        break;
      case OUT_OF_RANGE:
        Serial.println("electrode out of range");
        break;
      case NOT_INITED:
        Serial.println("not initialised");
        break;
      default:
        Serial.println("unknown error");
        break;
    }
    while (1);
  }

  MPR121.setInterruptPin(MPR121_INT);

  if (SET_MIDI_CONTROL) {
    // set up electrode 0 as a proxmity mapped controller attached to controller 102
    MIDIobjects[0].type = MIDI_CONTROL;
    MIDIobjects[0].controllerNumber = 102;  // 102..119 are undefined in the MIDI specification
    MIDIobjects[0].inputMin = 520;   // note than inputMin is greater than inputMax here
                                     // this means that the closer your hand is to the sensor
                                     // the higher the output value will be
                                     // to reverse the mapping, make inputMax greater than inputMin
    MIDIobjects[0].inputMax = 480;   // the further apart the inputMin and inputMax are from each other
                                     // the larger of a range the sensor will work over
    MIDIobjects[0].outputMin = 0;    // minimum output to controller - smallest valid value is 0
    MIDIobjects[0].outputMax = 127;  // maximum output to controller - largest valid value is 127


    // set up electrode 1 as a proxmity mapped controller attached to controller 103
    MIDIobjects[1].type = MIDI_CONTROL;
    MIDIobjects[1].controllerNumber = 103;
    MIDIobjects[1].inputMin = 520;
    MIDIobjects[1].inputMax = 480;
    MIDIobjects[1].outputMin = 0;
    MIDIobjects[1].outputMax = 127;

    // set up electrode 2 as a proxmity mapped controller attached to controller 104
    MIDIobjects[2].type = MIDI_CONTROL;
    MIDIobjects[2].controllerNumber = 104;
    MIDIobjects[2].inputMin = 520;
    MIDIobjects[2].inputMax = 480;
    MIDIobjects[2].outputMin = 0;
    MIDIobjects[2].outputMax = 127;

    // set up electrode 3 as a proxmity mapped controller attached to controller 105
    MIDIobjects[3].type = MIDI_CONTROL;
    MIDIobjects[3].controllerNumber = 105;
    MIDIobjects[3].inputMin = 520;
    MIDIobjects[3].inputMax = 480;
    MIDIobjects[3].outputMin = 0;
    MIDIobjects[3].outputMax = 127;

    // set up electrode 4 as a proxmity mapped controller attached to controller 106
    MIDIobjects[4].type = MIDI_CONTROL;
    MIDIobjects[4].controllerNumber = 106;
    MIDIobjects[4].inputMin = 520;
    MIDIobjects[4].inputMax = 480;
    MIDIobjects[4].outputMin = 0;
    MIDIobjects[4].outputMax = 127;

    // set up electrode 5 as a proxmity mapped controller attached to controller 107
    MIDIobjects[5].type = MIDI_CONTROL;
    MIDIobjects[5].controllerNumber = 107;
    MIDIobjects[5].inputMin = 520;
    MIDIobjects[5].inputMax = 480;
    MIDIobjects[5].outputMin = 0;
    MIDIobjects[5].outputMax = 127;

    // set up electrode 6 as a proxmity mapped controller attached to controller 108
    MIDIobjects[6].type = MIDI_CONTROL;
    MIDIobjects[6].controllerNumber = 108;
    MIDIobjects[6].inputMin = 520;
    MIDIobjects[6].inputMax = 480;
    MIDIobjects[6].outputMin = 0;
    MIDIobjects[6].outputMax = 127;

    // set up electrode 7 as a proxmity mapped controller attached to controller 109
    MIDIobjects[7].type = MIDI_CONTROL;
    MIDIobjects[7].controllerNumber = 109;
    MIDIobjects[7].inputMin = 520;
    MIDIobjects[7].inputMax = 480;
    MIDIobjects[7].outputMin = 0;
    MIDIobjects[7].outputMax = 127;

    // set up electrode 8 as a proxmity mapped controller attached to controller 110
    MIDIobjects[8].type = MIDI_CONTROL;
    MIDIobjects[8].controllerNumber = 110;
    MIDIobjects[8].inputMin = 520;
    MIDIobjects[8].inputMax = 480;
    MIDIobjects[8].outputMin = 0;
    MIDIobjects[8].outputMax = 127;

    // set up electrode 9 as a proxmity mapped controller attached to controller 111
    MIDIobjects[9].type = MIDI_CONTROL;
    MIDIobjects[9].controllerNumber = 111;
    MIDIobjects[9].inputMin = 520;
    MIDIobjects[9].inputMax = 480;
    MIDIobjects[9].outputMin = 0;
    MIDIobjects[9].outputMax = 127;

    // set up electrode 10 as a proxmity mapped controller attached to controller 112
    MIDIobjects[10].type = MIDI_CONTROL;
    MIDIobjects[10].controllerNumber = 112;
    MIDIobjects[10].inputMin = 520;
    MIDIobjects[10].inputMax = 480;
    MIDIobjects[10].outputMin = 0;
    MIDIobjects[10].outputMax = 127;

    // set up electrode 11 as a proxmity mapped controller attached to controller 113
    MIDIobjects[11].type = MIDI_CONTROL;
    MIDIobjects[11].controllerNumber = 113;
    MIDIobjects[11].inputMin = 520;
    MIDIobjects[11].inputMax = 480;
    MIDIobjects[11].outputMin = 0;
    MIDIobjects[11].outputMax = 127;
  } else {
    // set up electrode 0 as a touch sensitive key attached to note 60
    MIDIobjects[0].type = MIDI_NOTE;
    MIDIobjects[0].noteNumber = 60;  // middle C

    // set up electrode 1 as a touch sensitive key attached to note 61
    MIDIobjects[1].type = MIDI_NOTE;
    MIDIobjects[1].noteNumber = 61;

    // set up electrode 2 as a touch sensitive key attached to note 62
    MIDIobjects[2].type = MIDI_NOTE;
    MIDIobjects[2].noteNumber = 62;

    // set up electrode 3 as a touch sensitive key attached to note 63
    MIDIobjects[3].type = MIDI_NOTE;
    MIDIobjects[3].noteNumber = 63;

    // set up electrode 4 as a touch sensitive key attached to note 64
    MIDIobjects[4].type = MIDI_NOTE;
    MIDIobjects[4].noteNumber = 64;

    // set up electrode 5 as a touch sensitive key attached to note 65
    MIDIobjects[5].type = MIDI_NOTE;
    MIDIobjects[5].noteNumber = 65;

    // set up electrode 6 as a touch sensitive key attached to note 66
    MIDIobjects[6].type = MIDI_NOTE;
    MIDIobjects[6].noteNumber = 66;

    // set up electrode 7 as a touch sensitive key attached to note 67
    MIDIobjects[7].type = MIDI_NOTE;
    MIDIobjects[7].noteNumber = 67;

    // set up electrode 8 as a touch sensitive key attached to note 68
    MIDIobjects[8].type = MIDI_NOTE;
    MIDIobjects[8].noteNumber = 68;

    // set up electrode 9 as a touch sensitive key attached to note 69
    MIDIobjects[9].type = MIDI_NOTE;
    MIDIobjects[9].noteNumber = 69;

    // set up electrode 10 as a touch sensitive key attached to note 70
    MIDIobjects[10].type = MIDI_NOTE;
    MIDIobjects[10].noteNumber = 70;

    // set up electrode 11 as a touch sensitive key attached to note 71
    MIDIobjects[11].type = MIDI_NOTE;
    MIDIobjects[11].noteNumber = 71;
  }

  MPR121.updateAll();

  if (MPR121_DATASTREAM_ENABLE) {
    MPR121.restoreSavedThresholds();
    MPR121_Datastream.begin(&Serial);
  } else {
    MPR121.setTouchThreshold(40);
    MPR121.setReleaseThreshold(20);
  }

  MPR121.setFFI(FFI_10);
  MPR121.setSFI(SFI_10);
  MPR121.setGlobalCDT(CDT_4US);  // reasonable for larger capacitances
  
  digitalWrite(LED_BUILTIN, HIGH);  // switch on user LED while auto calibrating electrodes
  delay(1000);
  MPR121.autoSetElectrodes();  // autoset all electrode settings
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  MPR121.updateAll();

  // check note electrodes
  for (int i = 0; i < 12; i++) {
    if (MIDIobjects[i].type == MIDI_NOTE) {
      e.type = 0x08;
      e.m2 = MIDIobjects[i].noteNumber;  // set note number
      e.m3 = 127;  // maximum volume

      if (MPR121.isNewTouch(i)) {
        // if we have a new touch, turn on the onboard LED and
        // send a "note on" message with the appropriate note set
        digitalWrite(LED_BUILTIN, HIGH);
        e.m1 = uint8_t(0x9 << 4 | CHANNEL);
      } else if (MPR121.isNewRelease(i)) {
        // if we have a new release, turn off the onboard LED and
        // send a "note off" message
        digitalWrite(LED_BUILTIN, LOW);
        e.m1 = uint8_t(0x8 << 4 | CHANNEL);
      } else {
        // else set a flag to do nothing...
        e.m1 = uint8_t(0x0 << 4 | CHANNEL);
      }

      // only send a USB MIDI message if we need to
      if (e.m1 != 0x00) {
        MIDIUSB.write(e);
      }
    }
  }

  // check controller electrodes
  for (int i = 0; i < 12; i++) {
    if (MIDIobjects[i].type == MIDI_CONTROL) {  // if we have a control type object...
      Serial.print("E");
      Serial.print(i);
      Serial.print(":");  // this prints some Serial debug data for ease of mapping
      Serial.println(MPR121.getFilteredData(i));  // e.g. E11:567 means E11 has value 567 (this is the input data)

      // output the correctly mapped value from the input
      e.m3 = (unsigned char)constrain(map(MPR121.getFilteredData(i), MIDIobjects[i].inputMin, MIDIobjects[i].inputMax, MIDIobjects[i].outputMin, MIDIobjects[i].outputMax), 0, 127);

      if (e.m3 != MIDIobjects[i].lastOutput) {  // only output a new controller value if it has changed since last time
        MIDIobjects[i].lastOutput = e.m3;
        e.type = 0x08;
        e.m1 = uint8_t(0xB << 4 | CHANNEL);
        e.m2 = MIDIobjects[i].controllerNumber;  // select the correct controller number - you should use numbers
                                                // between 102 and 119 unless you know what you are doing
        MIDIUSB.write(e);
      }
    }
  }

  MIDIUSB.flush();  // flush USB buffer to ensure all notes are sent

  if (MPR121_DATASTREAM_ENABLE) {
    MPR121_Datastream.update();
  }

  delay(10);  // 10ms delay to give the USB MIDI target time to catch up
}
