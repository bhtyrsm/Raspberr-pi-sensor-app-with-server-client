#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>



void printInfo(char* temp){

	if(strncmp("Relay:ON",temp,8)==0){

  	printf("Relay durumunu -OFF- yapmak için -surucuDurum:0- mesajını giriniz\n");

	}else if(strncmp("Relay:OFF",temp,9)==0){
	
	printf("Relay durumunu -ON- yapmak için -surucuDurum:1- mesajını giriniz\n");
	
	}



} //end of func

int main(){
       
	

	int socket_fd;
	struct sockaddr_in caddr;
	char *ip="10.42.0.39";
 
	 char msg[100];
         char msgComing[50];


 	
      
	
	//Socket Address
	caddr.sin_family=AF_INET;
	caddr.sin_port=htons(7776);
	if(inet_aton(ip,&caddr.sin_addr)==0){
		return (-1);
	}
	
	//Create socket
	socket_fd=socket(PF_INET,SOCK_STREAM,0);
	if(socket_fd == -1){
		printf("Error on socket creation [%s] \n",strerror(errno));
		return (-1); 
	}
	
	//Establish connection
	if(connect(socket_fd, (const struct sockaddr *)&caddr,sizeof(struct sockaddr))== -1){
		printf("Error on socket connect [%s] \n",strerror(errno));
		return (-1);
	}

	//Read and write data

    int size;



 		printf("\n\n--> Mesaj Giris formati <---\n");
		printf("sensorDurum:\n");
		printf("sensorSayi:\n");
		printf("surucuDurum:\n");
		printf("sensorList:\n");
		printf("\n-> Kontrol Mesajlari formati <---\n");
		printf("surucuDurum:0\n");
		printf("surucuDurum:1\n");
		printf("sensorTip:0\n");
		printf("sensorTip:1\n");

                printf("\ncıkmak icin -quit- yazınız\n");
                printf("Lutfen dogru formatta giriniz ve bosluk bırakmayınız:\n\n");


	while(strncmp(msg,"quit",4)){

		printf("\nMesaj : ");
		scanf("%s",msg);

		if(write(socket_fd,msg,sizeof(msg))!=sizeof(msg)){
			printf("Error writing [%s] \n",strerror(errno));
		}
		else{
			printf("Sent data [%s] \n",msg);
		}

                      
                if((size=read(socket_fd,msgComing,sizeof(msgComing)))==-1){
				printf("Error reading [%s] \n",strerror(errno));
 		 }
		 else{
			msg[size]='\0';
			printf("Read data [%s]\n",msgComing);
		 }

		printInfo(msgComing);
		strncpy(msgComing,"",50);	

	}



	//Close the connection
	close(socket_fd);
	return 0;

}
