#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[256],buffer2[256];
   portno = 5001;
   //Create a socket point
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   // ----Configure settings of the server address struct----
   // Initialize socket structure elements to zero
   bzero((char *) &serv_addr, sizeof(serv_addr));
   // Address family = Internet
   serv_addr.sin_family = AF_INET;
   // Set port number, using htons function to use proper byte order
   serv_addr.sin_port = htons(portno);
   // Set IP address to localhost
   //serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

   // Now connect to the server 
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
int cnt=1;
   while(cnt){
  	  //Now ask for a message from the user, this message will be read by server
	   printf("Please enter the message: ");
	   bzero(buffer,256);
	   fgets(buffer,256,stdin);
	   
	   //Send message to the server
	   n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) {
	      perror("ERROR writing to socket");
	      exit(1);
	   }
	printf("%s\n",buffer);
	   printf("To continue enter 1 else 0\n");
		bzero(buffer2,256);
	   fgets(buffer2,256,stdin);
	if(buffer2[0]=='0') break;
	n=write(sockfd, buffer2, strlen(buffer2));
		if (n < 0) {
		      perror("ERROR writing to socket");
		      exit(1);
		   }								
   }
	
   
   return 0;
}
