#include <MIDI.h> // Add Midi Library


// Define labels for the 12 pins
#define REW 7
#define FF 6
#define PLAY1 5
#define PLAY2 4
#define STOP 3
#define REC 2

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

const int REVREW= 8;
const int REVFF= 9;
const int REVPLAY= 10;
const int REVSTOP= 11;
const int REVREC= 12;

int buttonstate1 = 0;
int buttonstate2 = 0;
int buttonstate3 = 0;
int buttonstate4 = 0;
int buttonstate5 = 0;

int lastbuttonstate1 = 0;
int lastbuttonstate2 = 0;
int lastbuttonstate3 = 0;
int lastbuttonstate4 = 0;
int lastbuttonstate5 = 0;

//Incoming midi messages to be output pin 7-2 when receiving noteON message with note = 60-65
// Buttons to output notes from Midi Out to be recorded in DAW sequencer.
// Midi Note 60 (Rewind), 61 (FF), 62 (Play), 63 (Stop), 64 (Rec)

void setup() {

  Serial.begin(31250);
  MIDI.begin(16); // Initialize the Midi Library. Respond to notes on channel 16 only.
  MIDI.setHandleNoteOn(Press); 
  MIDI.setHandleNoteOff(Release); 
    
  pinMode (REW, OUTPUT); 
  pinMode (FF, OUTPUT); 
  pinMode (PLAY1, OUTPUT); 
  pinMode (PLAY2, OUTPUT); 
  pinMode (STOP, OUTPUT); 
  pinMode (REC, OUTPUT); 

  pinMode (REVREW, INPUT); 
  pinMode (REVFF, INPUT); 
  pinMode (REVPLAY, INPUT); 
  pinMode (REVSTOP, INPUT); 
  pinMode (REVREC, INPUT); 
  
  pinMode(REVREW, INPUT_PULLUP);
  pinMode(REVFF, INPUT_PULLUP);
  pinMode(REVPLAY, INPUT_PULLUP);
  pinMode(REVSTOP, INPUT_PULLUP);
  pinMode(REVREC, INPUT_PULLUP);// if you are using a pull down resistor then remove it.
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.

  buttonstate1 = digitalRead(REVREW);
  buttonstate2 = digitalRead(REVFF);
  buttonstate3 = digitalRead(REVPLAY);
  buttonstate4 = digitalRead(REVSTOP);
  buttonstate5 = digitalRead(REVREC);


//MIDI Note SEND

if(buttonstate1 != lastbuttonstate1) {
    if (buttonstate1 == LOW){
      //Serial.println("PRESSED");
      MIDI.sendNoteOn(60, 127, 16);
    }
     
    else {
     //Serial.println("RELEASED");
     MIDI.sendNoteOff(60, 0, 16);
    }

  lastbuttonstate1 = buttonstate1;

}
 if(buttonstate2 != lastbuttonstate2) {
    if (buttonstate2 == LOW){
      //Serial.println("PRESSED");
      MIDI.sendNoteOn(61, 127, 16);
    }
     
    else {
     //Serial.println("RELEASED");
     MIDI.sendNoteOff(61, 0, 16);
    }
 
  lastbuttonstate2 = buttonstate2;
 }
 
if(buttonstate3 != lastbuttonstate3) {
    if (buttonstate3 == LOW){
      //Serial.println("PRESSED");
      MIDI.sendNoteOn(62, 127, 16);
    }
     
    else {
     //Serial.println("RELEASED");
     MIDI.sendNoteOff(62, 0, 16);
    }

  lastbuttonstate3 = buttonstate3;
}

if(buttonstate4 != lastbuttonstate4) {
    if (buttonstate4 == LOW){
      //Serial.println("PRESSED");
      MIDI.sendNoteOn(63, 127, 16);
    }
     
    else {
     //Serial.println("RELEASED");
     MIDI.sendNoteOff(63, 0, 16);
    }

  lastbuttonstate4 = buttonstate4;
}

if(buttonstate5 != lastbuttonstate5) {
    if (buttonstate5 == LOW){
      //Serial.println("PRESSED");
      MIDI.sendNoteOn(64, 127, 16);
    }
     
    else {
     //Serial.println("RELEASED");
     MIDI.sendNoteOff(64, 0, 16);
    }

  lastbuttonstate5 = buttonstate5;
}
}
     //---FUNCTIONS--- Do i need this?
 //  plays a MIDI note
 //void NoteOn(int cmd, int pitch, int velocity) {
  //Serial.write(cmd);
  //Serial.write(pitch);
 // Serial.write(velocity);
//  } 


// Press is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity

  void Press (byte channel, byte note, byte velocity){  
  if (note== 60 ){ 
  digitalWrite(REW,HIGH);  // Send on pin 7 
  }
  if (note == 61){
    digitalWrite(FF,HIGH);  // Send on pin 6
  }
   if (note == 62){
    digitalWrite(PLAY1,HIGH); 
    digitalWrite(PLAY2,HIGH);// Send on pin 4 and 5
  }
   if (note == 63){
    digitalWrite(STOP,HIGH);  // Send on pin 4
  }
   if (note == 64){
    digitalWrite(REC,HIGH); 
    digitalWrite(PLAY1,HIGH); 
    digitalWrite(PLAY2,HIGH);// Send on pin 4, and 6
  }
  }

// Release is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity

void Release(byte channel, byte note, byte velocity)
{  
  if (note== 60){
  digitalWrite(REW,LOW);  // Stop send on pin 7
  }
   
    if (note== 61){
  digitalWrite(FF,LOW);  // Stop send on pin 6
    }
    
    if (note == 62){
  digitalWrite(PLAY1,LOW);
  digitalWrite(PLAY2,LOW);// Stop send on pin 4 AND 5
  }
   
    if (note == 63){
  digitalWrite(STOP,LOW);  // Stop send on pin 4
  }
 
    if (note == 64){
  digitalWrite(REC,LOW);
  digitalWrite(PLAY1,LOW);
  digitalWrite(PLAY2,LOW);// Stop send on pin 2 AND 4
  }
 }
