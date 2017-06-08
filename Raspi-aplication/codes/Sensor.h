#ifndef SENSOR_H
#define SENSOR_H

typedef struct 
{
	                         
	int Id;	
		   
	char SensorTip[12];     //sensor type       
	                        
	int PinIn;   //input pin             
	int PinOut;  //outpun pin            

}RpiSensor;

int SensorSayi;  //sensor number


void SetSensorType(RpiSensor* rSensor,int id,char* Stip);     //set sensor id and type

void SetPins(RpiSensor* rsensor, int in, int out);            //set sensor input/output pins  
          
void setSensorNumber(int num);                               //set sensor number        

int getSensorNumber();                        		    //return sensor number
               
int getSensorId(RpiSensor* rSensor);			    //return sensor id that giving sensor

void getSensorType(RpiSensor* rSensor,char* type);          //return sensor type that giving sensor


#endif
