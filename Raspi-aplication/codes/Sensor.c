#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "Sensor.h"


void SetSensorType(RpiSensor* rSensor,  int id, char* Stip) {  // set sensor id and type
	
       rSensor->Id=id;
       strncpy(rSensor->SensorTip,Stip,12);

}  



void SetPins(RpiSensor* rsensor, int in, int out) {  //set sensor input and output pins

	rsensor->PinIn=in;
	rsensor->PinOut=out;
	
}

void setSensorNumber(int num) {  //set sensor number

	SensorSayi = num;

} 

int getSensorId(RpiSensor* rSensor){  //return sensor id

return rSensor->Id;
}

int getSensorNumber()     //return sensor number
{
	return SensorSayi;

}

void getSensorType(RpiSensor* rSensor,char* type){  //return sensor type

strncpy(type,rSensor->SensorTip,12);

}






