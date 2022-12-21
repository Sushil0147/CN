
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256],choice[256],x[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   portno = 5001;

/* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

// ---Configure settings of the server address structure-----
//Initialize socket structure elements to zero
   bzero((char *) &serv_addr, sizeof(serv_addr));
//Set Address family = Internet
   serv_addr.sin_family = AF_INET;
//Set IP address to localhost
   //serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//Set port number, using htons function to use proper byte order
   serv_addr.sin_port = htons(portno);

/* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }

/* Now start listening for the clients, here process will
go in sleep mode and will wait for the incoming connection
*/

   listen(sockfd,5); // Listen on the socket, with 5 max connection requests queued
   printf("Server Listening\n");
   clilen = sizeof(cli_addr);

/* Accept actual connection from the client */

newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr,(socklen_t*) &clilen);

   if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }

/* If connection is established then start communicating */
	while(1){
	bzero(choice,256);
   	n=read(newsockfd,choice,255);
   	bzero(buffer,256);
   	n=read( newsockfd,buffer,255 );
   	printf("Client's string: %s\n",buffer);
   	printf("Client's option: %s\n",choice);
	if(choice[0]=='4') break;
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   switch(choice[0]){
		case '1': {
				int i,n=strlen(buffer);
				for(i=0;i<n/2;i++){
					char temp=buffer[i];
					buffer[i]=buffer[n-i-1];
					buffer[n-i-1]=temp;
				}
			}
			break;
		case '2': {
				int i=0;
				while(buffer[i]!='\0')
				{
					if(buffer[i] >= 'a' && buffer[i] <= 'z') {
					 buffer[i] = buffer[i] -32;
				      }
					i++;
				}
			}
			break;
		case '3':{

	           bzero(x,256);
   				n=read(newsockfd,x,255);
				int i=0,j=0;
				while(buffer[i]!='\0' && x[j]!='\0')
				{
					if(buffer[i++]==x[j]) j++;
					else j=0;
				}
				if(j==strlen(x)) n = write(newsockfd,"The given substring is present",31);
				else write(newsockfd,"The given substring is absent",30);
				break;
		}
		case '4': break;
	}

/* Write a response to the client */
   n = write(newsockfd,buffer,strlen(buffer));
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
}


   return 0;
}

