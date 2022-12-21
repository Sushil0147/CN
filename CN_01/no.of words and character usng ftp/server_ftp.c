#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
char ch;
int characters, words, lines;
 
void write_file(int sockfd){
    
    int n;
    FILE *fp;
    char *filename = "message2.txt";
    char buffer[SIZE];
 
    fp = fopen("message2.txt","r");
    characters = words = lines = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;
        if (ch == '\n' || ch == '\0')
            lines++;

        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;
    }
    if (characters > 0)
    {
        words++;
        lines++;
    }
    while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
    }
    
  return;
}
 
int main(){
  char *ip = "192.168.20.161";
  int port = 8080;
  int e;
 
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("Error in socket");
    exit(1);
  }
  printf("Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("Error in bind");
    exit(1);
  }
  printf("Binding successfull.\n");
 
  if(listen(sockfd, 10) == 0){
 printf("Listening....\n");
 }else{
 perror("Error in listening");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  printf("Data written in the file successfully.\n");
  printf("No. of characters : %d\nNo. of words: %d\n",characters,words);
 
  return 0;
}
