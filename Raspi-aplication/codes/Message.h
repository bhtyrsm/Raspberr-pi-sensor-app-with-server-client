#ifndef MESSAGE_H
#define MESSAGE_H
#include "Sensor.h"
#include "Surucu.h"







void SendSensorNumber(char* gidenMesaj);  //send sensor number as message paket

void SendTipId(char* gelen,int *id);    // Will find an id according to the incoming message.

void SendSensorList(RpiSensor* r1,RpiSensor* r, char* giden); //send two sensor info

void SendRelayState(char *gidenMesaj);      //It will send the current driver status.

void SendSensorState(char* gidenMesaj);   //send sensor status.

void UpdateRelay(char* gelen,char* gidenMesaj);    // relay on or off

#endif
