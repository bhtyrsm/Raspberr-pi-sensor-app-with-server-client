#include "Sensor.h"
#include "Message.h"
#include "Surucu.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include<stdlib.h>
#include <stdio.h>





	



int main(){

	int server_fd,client_fd;
	struct sockaddr_in caddr,saddr;

         //initialize //

	char *ip="10.42.0.39";   //server ip
	char msg[100];         //gelen mesaj
	char msgSend[100]="";  //gönderilecek mesaj

     	char tip1[12]="MagnetikAln";
	char tip2[12]="flashflying";
	int id;   // id ye göre tip sorgulamak için
         

	
        
  
         RpiSensor rsensor1;         //initialize rsensor1

	 SetSensorType(&rsensor1,0,tip1);
         SetPins(&rsensor1,17,27);

	 RpiSensor rsensor2;        //initalize rsensor2

	 SetSensorType(&rsensor2,1,tip2);
	 SetPins(&rsensor2,23,22); 

         setSensorNumber(2);       //set sensor number
	
	       

	//Server Socket Address
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(7776);

	saddr.sin_addr.s_addr=htonl(INADDR_ANY);

	//Create server socket
	server_fd=socket(PF_INET,SOCK_STREAM,0);
	if(server_fd == -1){
		printf("Error on socket creation [%s] \n",strerror(errno));
		return (-1); 
	}

	//Bind the address to server socket
	if(bind(server_fd,(struct sockaddr *)&saddr, sizeof(struct sockaddr))==-1){
		printf("Error socket bind [%s] \n",strerror(errno));
		return (-1); 
	}

	//Listen for a connection request
	if(listen(server_fd,1)){
		printf("Error socket listen [%s] \n",strerror(errno));
		return (-1); 
	}


	//Accept connection request and connect
	socklen_t addrSize=sizeof(caddr);	
	if((client_fd=accept(server_fd,(struct sockaddr*)&caddr,&addrSize))==-1){
		printf("Error socket accept [%s] \n",strerror(errno));
		close(server_fd);
		return (-1); 
	}
	printf("Server new connecton has been established [%s/%d]\n",inet_ntoa(caddr.sin_addr),caddr.sin_port);


	int size;
	int client=0;
	int ind=0;

	while(!client){
			//read and write maeesages
			if((size=read(client_fd,msg,sizeof(msg)))==-1){
				printf("Error reading [%s] \n",strerror(errno));
 			}
			else{
				msg[size]='\0';
				printf("Read data [%s]\n",msg);
                             
			       
				if(strncmp(msg,"sensorDurum:",13)==0){
        		 
				SendSensorState(msgSend); 

       				

				} //end sensorDurum
   

   				else if(strncmp(msg,"surucuDurum:0",14)==0||strncmp(msg,"surucuDurum:1",14)==0){
        			
				UpdateRelay(msg,msgSend) ;

    			   	

				}//end surucuDurum
			

				else if(strncmp(msg,"surucuDurum:",13)==0){
        
    			   	SendRelayState(msgSend);

				}//end surucuDurum
				


   				else if(strncmp(msg,"sensorSayi:",11)==0){
                
				SendSensorNumber(msgSend);

				}//end sensorSayi


				else if(strncmp(msg,"sensorList:",12)==0){
        
    			   	SendSensorList(&rsensor1,&rsensor2,msgSend);

				}//end sensorList
				
		


    			        else if(strncmp(msg,"sensorTip:0",12)==0||strncmp(msg,"sensorTip:1",12)==0){

				char type[12];

				SendTipId(msg,&id);	        //find id 0/1 (SendTipId function in Message.c)
                             
				if(id==getSensorId(&rsensor1))  // getSensorId/getSensorType function in Sensor.c
				getSensorType(&rsensor1,type);  

				else if(id==getSensorId(&rsensor2))
				getSensorType(&rsensor2,type);
				 
                                 strncpy(msgSend,type,12);	 //copy sensor type to msgSend		
		
				}//end sensorTip

  
     				else if(strncmp(msg,"quit",5)==0){
        
     				 strncpy(msgSend,"Cikis yapiliyor.....",21);}

   
				else{
 				strncpy(msgSend,"Yanlis format",14);}

 
				//
				
				if(write(client_fd,msgSend,strlen(msgSend))!=-1){   //send msgSend to client
				printf("Sent data [%s] \n",msgSend);
			       
		         	}

		      		else{
				 printf("Error writing [%s] \n",strerror(errno));
		    		}

			    strncpy(msgSend,"",100);
				          
			  }
			
				if(!strncmp(msg,"quit",4)){
				close(client);
				client=1;
				}

			}

	//Close connections
	close(server_fd);
	return 0;
}











