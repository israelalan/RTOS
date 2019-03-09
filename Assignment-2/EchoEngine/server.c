#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SERVER_PATH "/home/alan/Desktop/RTOS/assignment_2/trial/single_client"

void convert_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      else if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

int main(){
	int server_fd, client_fd, n, len_c;
	struct sockaddr_in server,client;
	char buf[200];
  int opt = 1;
  int addrlen = sizeof(client);

	server_fd = socket(AF_INET,SOCK_STREAM,0);
	printf("Descriptor = %d\n",server_fd );

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(8000);
   memset(server.sin_zero, '\0', sizeof server.sin_zero);

    int bind_check = bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    printf("Bind check = %d\n", bind_check);
    listen(server_fd, 5);
    len_c = sizeof(client);
    
    
    while(1){
      client_fd = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&addrlen);
      if(fork()==0){
    	while((n=read(client_fd, buf, sizeof(buf)))>0){
    		convert_string(buf);
    		send(client_fd, buf, n, 0);
      }
    }
  }
}
