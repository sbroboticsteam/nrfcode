//This code is given to you by Moses and his pal Sasha, the Electrical Team Lead. If it ain't working, tell me: I'll fix it.
//                                                                If you ain't using it, I won't fix your shit, so GLHF.

#include <SPI.h>
#include "RF24.h"
#define CEpin 7                               //The CE pin (pin 3) of the nRF24L01 can be connected to any digital pin.
#define CSpin 8                               //The CS pin (pin 4) of the nRF24L01 can be connected to any digital pin.
#define SizeOfMessage 26                      //The size of the message to be sent.
#define Channel 115                           //The channel has to be the same as that of the receiver. 0-125.
#define PALevel RF24_PA_MAX                   //The power amplifier level. Should work fine, but should check that if something isn't working.
#define DataRate RF24_250KBPS                 //The data rate. Only change it if you're doing something really crazy. Receiver has to have the same data rate.
RF24 myRadio(CEpin, CSpin);
byte addresses[][6] = {"0"};                  //This is used to set up the nRF24L01 pipes. I'm not 100% sure what it does, but it seems standard.
byte message[SizeOfMessage];                  //This is where the massage to be transmitted will be stored.

const int leftFrontSpeed = 3;
const int leftFrontDir = 2;
const int leftBackSpeed = 6;
const int leftBackDir = 4;
const int rightFrontSpeed = 9;
const int rightFrontDir = 8;
const int rightBackSpeed = 11;
const int rightBackDir = 12; 
void setup() 
{
  Serial.begin(115200);
  myRadio.begin();
  myRadio.setChannel(Channel);                //Set the communication channel. 0-125. Transmitter and reciener have to be on the same channel.
  myRadio.setPALevel(PALevel);                //Set the power amplifier level. MIN,LOW,HIGH,MAX. MAX for best range, MIN for less current (to work with shitty +3.3V).
  myRadio.setDataRate(DataRate);              //Set the data rate. 250KBPS, 1MBPS, 2MBPS.
  myRadio.openReadingPipe(1, addresses[0]);      //Still not sure about the pipe things, but It seems that this is the standard way of doing it.
  myRadio.startListening();
  message[0] = 255;                           //Setting up the first message so it is valid (so if we don't get data from the computer we can still send an all zero message).
  message[1] = 255;
  message[2] = 255;
  message[3] = 255;
  message[14] = 128;
  message[15] = 128;
  message[20] = 128;
  message[21] = 128;
  message[22] = 128;
  message[23] = 128;
  message[26] = 3;
}

void loop()  
{
  Serial.flush();
  delay(10);                                  //This is to let data get in. Should not have any noticable performace issues.

  if (myRadio.available()) {
    myRadio.read(&message, SizeOfMessage);
  }
  // you will probably have to modify the below code as it is meant for controlling a mars rover
//      Serial.print("Received: ");
//      Serial.print("Left Y: ");
//      Serial.print(message[0]);
//      Serial.print(" Right Y: ");
//      Serial.print(message[1]);
//      Serial.print(" Brake: ");
//      Serial.println(message[2]);

}
