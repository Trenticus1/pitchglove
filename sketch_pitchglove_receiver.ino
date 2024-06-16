#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 11, 12);

void setup()
{
    Serial.begin(115200);	  // Debugging only
    Serial.println("initialising...");
    if (!driver.init())
         Serial.println("init failed");
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
  



    }



     //delay(50);
     //Serial.println("Loop"); 
}

