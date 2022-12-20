/*
   ESP8266 relay control interface with PIR sensor trigger

   When motion is detected with the PIR sensor, a relay is closed for a
   certain amount of time.
   This can be used to turn on a light when someone enters an area.

   Target Hardware:  ESP8266 WeMos D1 Mini and relay control pcb:
                     https://github.com/GadgetReboot/PIR_Relay

   Tested with Arduino IDE 1.8.13
               ESP8266 board file 3.0.2

   Gadget Reboot
   https://www.youtube.com/gadgetreboot

*/


#define   relayPin        D5          // relay control output pin   high = on low = off
#define   pirPin          D6          // PIR sensor  high = motion detected
#define   relayOn         1           // turn relay on or off
#define   relayOff        0

unsigned long timer = millis();       // relay on duration timer
uint16_t onTime = 10000;              // relay on-time in mS once triggered
bool pirTriggered = false;            // whether the PIR sensor has detected motion or not


void setup() {
  digitalWrite(relayPin, LOW);        // turn off relay
  pinMode(relayPin, OUTPUT);
  pinMode(pirPin, INPUT);
}

void loop() {

  if (digitalRead(pirPin) == 1) {
    timer = millis();                 // start timer for relay if motion is detected
    pirTriggered = true;
    controlRelay(relayOn);
  }

  if (pirTriggered) {
    if ((unsigned long)(millis() - timer) > onTime) {   // when timer expires, turn off relay
      controlRelay(relayOff);
      pirTriggered = false;
    }
  }


}  // end loop

void controlRelay(int state) {         // turn relay on or off based on "state"
  digitalWrite(relayPin, state);       // relay is active high
}
