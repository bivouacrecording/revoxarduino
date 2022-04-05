
#include <MIDI.h> // Add Midi Library

// Define labels for the 12 pins
#define REW 2
#define FF 3
#define PLAY 4
#define STOP 5
#define REC 6

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

//Incoming midi messages to be output pin 2-6 when receiving noteON message with note = 60-65
// Buttons to output notes from Midi Out to be recorded in DAW sequencer.
// Midi Note 60 (Rewind), 61 (FF), 62 (Play), 63 (Stop), 64 (Rec)

void setup() {
  
  pinMode (REW, OUTPUT); 
  pinMode (FF, OUTPUT); 
  pinMode (PLAY, OUTPUT); 
  pinMode (STOP, OUTPUT); 
  pinMode (REC, OUTPUT); 
  
  MIDI.begin(13); // Initialize the Midi Library. Respond to notes on channel 13 only.
  
  MIDI.setHandleNoteOn(Press); 
  MIDI.setHandleNoteOff(Release);  
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.
}

// Press is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity

void Press (byte channel, byte pitch, byte velocity) {  
  if (pitch == 60 ){ 
    digitalWrite(REW,HIGH);  // Send on pin 2 
  }
  if (pitch == 61){
    digitalWrite(FF,HIGH);  // Send on pin 3
  }
  if (pitch == 62){
    digitalWrite(PLAY,HIGH);// Send on pin 4
  }
  if (pitch == 63){
    digitalWrite(STOP,HIGH);  // Send on pin 5
  }
  if (pitch == 64){
    digitalWrite(REC,HIGH); 
    digitalWrite(PLAY,HIGH);// Send on pin 4, 6
  }
}
  
// Release is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity

void Release (byte channel, byte pitch, byte velocity){  
  
  if (pitch== 60){
    digitalWrite(REW,LOW);  // Stop send on pin 2
  }
   if (pitch== 61){
    digitalWrite(FF,LOW);  // Stop send on pin 3
  }
   if (pitch == 62){
    digitalWrite(PLAY,LOW);// Stop send on pin 4
  } 
   if (pitch == 63){
    digitalWrite(STOP,LOW);  // Stop send on pin 5
  }
   if (pitch == 64){
    digitalWrite(REC,LOW);
    digitalWrite(PLAY,LOW);// Stop send on pin 4 AND 6
  }    
}
 
