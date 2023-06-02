// partial copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// parts of this work are licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// Documentation and samples are available at http://www.mathertel.de/Arduino

#include <DMXSerial.h>
#include <SoftwareSerial.h>

const int RedPin =    3;  // PWM output pin for Red Light.
const int rxPin =     7;  // input pin for SoftwareSerial, not used atm.
const int txPin =     8;  // output pin for SoftwareSerial to rpi

const int startChannel = 1;   //set dmx adress here
const int dmxSize = 12;       //

int dmx[dmxSize];
int dmxo[dmxSize];

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

void setup() {
  DMXSerial.init(DMXReceiver);

  // enable pwm outputs
  pinMode(RedPin, OUTPUT); // status led
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  mySerial.begin(115200);

}

void loop() {
  
  // read recent DMX values and set pwm levels
  for (int i = 0; i < dmxSize; i++) {
    dmx[i] = DMXSerial.read(i + startChannel);
    
    if (dmx[i] != dmxo[i]) {
      dmxo[i] = dmx[i];
      analogWrite(RedPin, dmxo[i]);
      
      for (int j = 0; j < dmxSize; j++) {
        mySerial.write(dmxo[j]);
      }
    }
  }
}
