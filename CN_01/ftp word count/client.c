#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
   int sockfd, newsockfd,portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[1024];
   FILE *fp;
   
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
   
   //Now ask for a message from the user, this message will be read by server
   fp=fopen("text1.txt","w");
   int wc=1,cc=0;;
   bzero(buffer,1024);
   while(1){
	n = read( sockfd,buffer,1023 );
wc++;
	if(n==0) break;
	int i=0;
	while(buffer[i]!='\0'){
	if(buffer[i]!=' ') cc++;
	else wc++;
	i++;
}
	//printf("in client ");
   
}
   printf("File received successfully\n");
   printf("New file created with name as text1.txt\n");
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   fprintf(fp,"Words: %d ",wc);
	fprintf(fp,"Characters: %d",cc);
   // Now read server response
   bzero(buffer,256);
   n = read(sockfd, buffer, 256);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
	
   printf("%s\n",buffer);
   printf("\n");
   return 0;
}
