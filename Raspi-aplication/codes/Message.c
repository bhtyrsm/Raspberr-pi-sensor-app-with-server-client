#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "Message.h"

#define LOW 0
#define HIGH 1

#define SENSOR 17  //first sensor input (magneticarea gpio17)
#define RELAY 27   //first sensor output sensor -gpio27
#define SENSOR2 23  //second sensor input(flashlight-gpio23)
#define RELAY2 22  //second  sensor output -gpio22




void SendSensorNumber(char* gidenMesaj) {  //send sensor number as message packet

		char temp[2];
		int value=getSensorNumber();
        char temp2[17]="sensor sayisi : ";

        sprintf(temp,"%d",value);       //integer to char/char array
        strcat(temp2,temp);            
        strncpy(gidenMesaj,temp2,18); 

} //end func SendSesnorNumber()


void SendTipId(char* gelen, int* id){  //find id
  
        if(strcmp("sensorTip:0",gelen)==0)
		*id=0;
        if(strcmp("sensorTip:1",gelen)==0)
		*id=1;
		

}//end func SendType

void SendSensorList(RpiSensor* r1,RpiSensor* r2, char* giden){

  	char id1[2];
	char id2[2];


	char tip1[12];
	char tip2[12];
  	

	char msg1[38]="";
	char msg2[17];

	sprintf(id1,"%d",r1->Id);  //integer to char/char array
	sprintf(id2,"%d",r2->Id);  //integer to char/char array
       
	strncpy(tip1,r1->SensorTip,12); 
	strncpy(tip2,r2->SensorTip,12);

    strcat(msg1,"id:");  //msg1=id:
	strcat(msg1,id1);    //msg1=id:0
	strcat(msg1," ");
	strcat(msg1,tip1);	//msg1=id:0 flashlight
    strcat(msg1,"-");
    strcat(msg2,"id:");	//msg1=id:0 flashlight id:
	strcat(msg2,id2);	//msg1=id:0 flashlight id:1
 	strcat(msg2," ");
	strcat(msg2,tip2);	//msg1=id:0 flashlight id:1 MagnetikAln
      
	strncpy(giden,msg1,strlen(msg1));       

} //end func SendSensorList()



void SendRelayState(char *gidenMesaj) {      //It will send the current relay status. 
	                                         //
            
					     
	if (LOW == GPIORead(SENSOR)&&LOW == GPIORead(SENSOR2)){   
	strncpy(gidenMesaj,"Relay:OFF",10);
	
	}else{
 	strncpy(gidenMesaj,"Relay:ON",9);
	}
      
	
					

	
} //end func SendRelayState()


void SendSensorState(char* gidenMesaj){  // send sensor status

       char state[35]="";

	

 
   if(HIGH == GPIORead(SENSOR)){

     strcat(state,"MagnetikAln:ON "); 
    }
    
    if(LOW == GPIORead(SENSOR)){

     strcat(state,"MagnetikAln:OFF "); 
    }

   if(HIGH == GPIORead(SENSOR2)){

	strcat(state,"flashlight:ON ");
    }

   if(LOW == GPIORead(SENSOR2)){

	strcat(state,"flashlight:OFF ");
    }

  strncpy(gidenMesaj,state,strlen(state));

 
} //end func SendSensorState()




void UpdateRelay(char* gelen,char* gidenMesaj) {    // relay on or off

	if(strncmp(gelen,"surucuDurum:0",13)==0){  //Both sensor output pins must be set to zero so that the driver can be off
       
  
		if(0==GPIOWrite(RELAY, LOW)&&0==GPIOWrite(RELAY2, LOW)){  

		strncpy(gidenMesaj,"succes",6);

		}
		else{

		strncpy(gidenMesaj,"error",5);

		}
			

	}
	else if(strncmp(gelen,"surucuDurum:1",13)==0){ //Both sensor output pins must be set to one so that the driver can be on
      


		if(0==GPIOWrite(RELAY, HIGH)&&0==GPIOWrite(RELAY2, HIGH)){  

		strncpy(gidenMesaj,"succes",6);

		}
		else{

		strncpy(gidenMesaj,"error",5);

		}
	} //end elseif


}//end func updateRelay()





