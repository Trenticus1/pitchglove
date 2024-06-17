#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 11, 12);

int lastMidiNote = 0;
int lastPlayState = 0;

void setup()
{
    Serial.begin(115200);	  // Debugging only
    Serial.println("initialising...");
    if (!driver.init())
         Serial.println("init failed");
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}

void loop()
{
    uint8_t buf[8];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      buf[buflen] = '\0';   

      String message = buf;
      String note = message.substring(1,3);
      String play = message.substring(3);

      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.print((char*)buf);
      Serial.print("\tNote: ");
      Serial.print(note);
      Serial.print("\tPlay: ");
      Serial.println(play);  
      
      int midiNote;
      int playState;

      switch (note.toInt()) {
        case 1:
          midiNote = 44; // G#
          break;
        case 2:
          midiNote = 45; // A
          break;
        case 3:
          midiNote = 47; // B
          break;
        case 4:
          midiNote = 49; // C#
          break;
        case 5:
          midiNote = 50; // D
          break;
        case 6:
          midiNote = 52; // E
          break;
        case 7:
          midiNote = 54; // F#
          break;
        case 8:
          midiNote = 56; // g#
          break;
        case 9:
          midiNote = 57; // a
          break;
        case 10:
          midiNote = 59; // b
          break;
      }

      if (play == "p") playState = 1;
      else playState = 0;

      if ((midiNote != lastMidiNote) || (playState != lastPlayState))
      {
        if (playState) {
          if (midiNote != lastMidiNote) {
            noteOff(0, lastMidiNote, 0);
            noteOn(0, midiNote, 100);
          }
          if (playState != lastPlayState){
            noteOn(0, midiNote, 100);
          }
        }
        else {
          noteOff(0, lastMidiNote, 64);
        }
      }

      lastMidiNote = midiNote;
      lastPlayState = playState;

    }

    //delay(50);
    //Serial.println("Loop"); 
}
