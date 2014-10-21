/*******************************************************************************

 Bare Conductive Touch and Proximity USB MIDI interface
 ------------------------------------------------------
 
 Midi_interface_generic.ino - USB MIDI touch and proximity example

 Allows the mapping of each electrode to a key or control modulator in a 
 (relatively) simple manner. See the comments for details and experiment
 for best results.
 
 Requires Arduino 1.5.6+ or greater and ARCore Hardware Cores 
 https://github.com/rkistner/arcore - remember to select 
 Bare Conductive Touch Board (arcore, iPad compatible) in the Tools -> Board menu
 
 Bare Conductive code written by Stefan Dzisiewski-Smith.
 
 This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 
 Unported License (CC BY-SA 3.0) http://creativecommons.org/licenses/by-sa/3.0/
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*******************************************************************************/

#include <MPR121.h>
#include <Wire.h>
#include "Midi_object.h"
#include "Compiler_Errors.h"
MIDIEvent e;

#define numElectrodes 12
midi_object_t MIDIobjects[numElectrodes]; // create an array of MIDI objects to use (one for each electrode)

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  MPR121.begin(0x5C);
  MPR121.setInterruptPin(4);

  // set up electrode 0 as a very sensitive proxmity key attached to note 50
  MIDIobjects[0].type = MIDI_NOTE;
  MIDIobjects[0].noteNumber = 50;
  MIDIobjects[0].touchThreshold = 4;    // always make sure that the touch threshold is
  MIDIobjects[0].releaseThreshold = 2;  // larger than the release threshold

  // set up electrode 1 as a touch key attached to note 51
  MIDIobjects[1].type = MIDI_NOTE;
  MIDIobjects[1].noteNumber = 51;
  MIDIobjects[1].touchThreshold = 40;   // higher values = less sensitivity = trigger by touch, not proximity
  MIDIobjects[1].releaseThreshold = 20;  

  // set up electrode 2 as a touch key attached to note 52
  MIDIobjects[2].type = MIDI_NOTE;
  MIDIobjects[2].noteNumber = 52;
  MIDIobjects[2].touchThreshold = 40;
  MIDIobjects[2].releaseThreshold = 20;   

  // set up electrode 3 as a touch key attached to note 53
  MIDIobjects[3].type = MIDI_NOTE;
  MIDIobjects[3].noteNumber = 53;
  MIDIobjects[3].touchThreshold = 40;
  MIDIobjects[3].releaseThreshold = 20;   

  // set up electrode 4 as a very sensitive proxmity key attached to note 54
  MIDIobjects[4].type = MIDI_NOTE;
  MIDIobjects[4].noteNumber = 54;
  MIDIobjects[4].touchThreshold = 20;    // note lower values here mean more sensitivity
  MIDIobjects[4].releaseThreshold = 10;  // i.e. trigger by proximity, not touch  

  // set up electrode 5 as a proxmity mapped controller attached to controller 102
  MIDIobjects[5].type = MIDI_CONTROL;
  MIDIobjects[5].controllerNumber = 102; // 102..119 are undefined and so very useful for this
  MIDIobjects[5].inputMin = 490;  // minimum input from Touch Board - see Serial monitor for these values
                                  // to help in setting sensible min and max with / without hand in place
  MIDIobjects[5].inputMax = 530;  // maximum input from Touch Board
  MIDIobjects[5].outputMin = 0;   // minimum output to controller - smallest valid value is 0
  MIDIobjects[5].outputMax = 127; // minimum output to controller - largest valid value is 127

  // set up electrode 6 as a proxmity mapped controller attached to controller 103
  MIDIobjects[6].type = MIDI_CONTROL;
  MIDIobjects[6].controllerNumber = 103;
  MIDIobjects[6].inputMin = 520;  // note than min is greater than max here - that means that the direction is reversed
  MIDIobjects[6].inputMax = 480;  // i.e. closer hand is higher value, not lower
  MIDIobjects[6].outputMin = 0;
  MIDIobjects[6].outputMax = 127; 

  // skip out electrodes 7..10

  // set up electrode 11 as a proxmity mapped controller attached to controller 104
  MIDIobjects[11].type = MIDI_CONTROL;
  MIDIobjects[11].controllerNumber = 104;
  MIDIobjects[11].inputMin = 490;
  MIDIobjects[11].inputMax = 570;
  MIDIobjects[11].outputMin = 0;
  MIDIobjects[11].outputMax = 127; 

  // set touch and release thresholds for electrodes that require it
  for(int i=0; i<numElectrodes; i++){
    if(MIDIobjects[i].type == MIDI_NOTE){
      MPR121.setTouchThreshold(i, MIDIobjects[i].touchThreshold);
      MPR121.setReleaseThreshold(i, MIDIobjects[i].releaseThreshold);
    }
  }     

  // start with fresh data
  MPR121.updateAll();
}

void loop() {
  // check note electrodes
  if(MPR121.touchStatusChanged()){
    MPR121.updateTouchData();
    for(int i=0; i<numElectrodes; i++){
      if(MIDIobjects[i].type==MIDI_NOTE){ // if this is a note type object...
        e.type = 0x08;
        e.m2 = MIDIobjects[i].noteNumber; // set note number
        e.m3 = 127;  // maximum volume
        if(MPR121.isNewTouch(i)){
          // if we have a new touch, turn on the onboard LED and
          // send a "note on" message with the appropriate note set
          digitalWrite(LED_BUILTIN, HIGH);
          e.m1 = 0x90; 
        } else if(MPR121.isNewRelease(i)){
          // if we have a new release, turn off the onboard LED and
          // send a "note off" message
          digitalWrite(LED_BUILTIN, LOW);
          e.m1 = 0x80;
        } else {
          // else set a flag to do nothing...
          e.m1 = 0x00;  
        }
        // only send a USB MIDI message if we need to
        if(e.m1 != 0x00){
          MIDIUSB.write(e);
        }
      }
    }
  }

  MPR121.updateFilteredData();

  // now check controller electrodes
  for(int i=0; i<numElectrodes; i++){
    if(MIDIobjects[i].type==MIDI_CONTROL){ // if we have a control type object...
      Serial.print("E");
      Serial.print(i);
      Serial.print(":");                          // this prints some Serial debug data for ease of mapping
      Serial.println(MPR121.getFilteredData(i));  // e.g. E11:567 means E11 has value 567 (this is the input data)

      e.type = 0x08;
      e.m1 = 0xB0; // control change message
      e.m2 = MIDIobjects[i].controllerNumber;     // select the correct controller number - you should use numbers
                                                  // between 102 and 119 unless you know what you are doing
      // output the correctly mapped value from the input
      e.m3 = (unsigned char)constrain(map(MPR121.getFilteredData(i), MIDIobjects[i].inputMin, MIDIobjects[i].inputMax, MIDIobjects[i].outputMin, MIDIobjects[i].outputMax), 0, 127);
      MIDIUSB.write(e);
    }
  }

  // flush USB buffer to ensure all notes are sent
  MIDIUSB.flush(); 

  delay(10); // 10ms delay to give the USB MIDI target time to catch up

}