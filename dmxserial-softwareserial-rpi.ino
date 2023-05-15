// - - - - -
// DmxSerial - A hardware supported interface to DMX.
// DmxSerialRecv.ino: Sample DMX application for retrieving 3 DMX values:
// address 1 (red) -> PWM Port 9
// address 2 (green) -> PWM Port 6
// address 3 (blue) -> PWM Port 5
//
// Copyright (c) 2011-2015 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
//
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 25.07.2011 creation of the DmxSerial library.
// 10.09.2011 fully control the serial hardware register
//            without using the Arduino Serial (HardwareSerial) class to avoid ISR implementation conflicts.
// 01.12.2011 include file and extension changed to work with the Arduino 1.0 environment
// 28.12.2011 changed to channels 1..3 (RGB) for compatibility with the DmxSerialSend sample.
// 10.05.2012 added some lines to loop to show how to fall back to a default color when no data was received since some time.
// - - - - -

#include <DMXSerial.h>
#include <SoftwareSerial.h>


// Constants for demo program

const int RedPin =    3;  // PWM output pin for Red Light.
const int rxPin =     7;
const int txPin =     8;


const int startChannel = 1;
const int dmxSize = 12;

int dmx[dmxSize];
int dmxo[dmxSize];

int dmxtmp = 2;

#define RedDefaultLevel   200

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
  // Calculate how long no data bucket was received
  //unsigned long lastPacket = DMXSerial.noDataSince();


  // read recent DMX values and set pwm levels
  for (int i = 0; i < dmxSize; i++) {
    dmx[i] = DMXSerial.read(i + startChannel);
    
    if (dmx[i] != dmxo[i]) {
      dmxo[i] = dmx[i];
      analogWrite(RedPin, dmxo[i]);
      
      for (int j = 0; j < dmxSize; j++) {
        //mySerial.write(j);
        //mySerial.write(' ');
        mySerial.write(dmxo[j]);
      }
      
      //mySerial.write(' ');
      
    }
  }
}
  
  /*
  if (dmxtest != dmxtesto) {

    dmxtesto = dmxtest;
    analogWrite(RedPin,   dmxtesto);
    mySerial.write(dmxtesto);
    */
    

// End.
