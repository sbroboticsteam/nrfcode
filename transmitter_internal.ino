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

void setup()
{
  Serial.begin(115200);                       //Set up serial to read from the computer (which sends xbox data).
  myRadio.begin();
  myRadio.setChannel(Channel);                //Set the communication channel. 0-125. Transmitter and reciener have to be on the same channel.
  myRadio.setPALevel(PALevel);                //Set the power amplifier level. MIN,LOW,HIGH,MAX. MAX for best range, MIN for less current (to work with shitty +3.3V).
  myRadio.setDataRate(DataRate);              //Set the data rate. 250KBPS, 1MBPS, 2MBPS.
  myRadio.openWritingPipe(addresses[0]);      //Still not sure about the pipe things, but It seems that this is the standard way of doing it.
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
  Serial.flush();                             //Making sure we get to the most recent message.
  while(Serial.available()<SizeOfMessage)     //Waiting for a message to come in.
  {
    myRadio.write(message, SizeOfMessage);    //And while we wait, sending the data we already have.
  }
  while(Serial.read() != 255 || Serial.read() != 255 || Serial.read() != 255 || Serial.read() != 255) //Waiting for data to allign.
  {
    myRadio.write(message, SizeOfMessage);    //And while we wait, sending the data we already have.
  }
  int sum = 0;                                //Setting up a sum variable so we can check if the message is good.
  byte temp[SizeOfMessage-5];                 //Setting up a buffer to read the message into.
  boolean good = true;                        //Setting up a checker to see if the message is good.
  for(int i = 0; i < SizeOfMessage-5; i++)    
  {
    temp[i] = Serial.read();                  //Reading the new data byte by byte.
    sum += temp[i];                           //Adding the data up for the checksum.
    if((i == 10 || i == 11) && temp[i] != 128)//Two more allignment checks (they were extra spots I had, so I used them for that).
    {
      good = false;                           //If the message does not pass the check then it's no good.
    }
  }
  if(sum%255 == Serial.read() && good)        //Checking the checksum and allignments.
  {
    for(int i = 0; i < SizeOfMessage-5; i++)
    {
      message[i+4] = temp[i];                 //Making the message to send to the reciever.
    }
    message[SizeOfMessage-1] = sum%255;       //Adding in the checksum.
  }
  myRadio.write(message, SizeOfMessage);      //This transmits the message to be transmitted (will work with whatever size message we make).
}
