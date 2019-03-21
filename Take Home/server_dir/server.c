#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SERVER_PATH "/home/alan/Desktop/RTOS/assignment_2/trial/DB_engine"
int new;

int read_contents(char str[], char response[]) {
  
  char resp[200];
  char * split_text;
  int fd_read;
  /** Extracting First Word **/
  /*if(new){
    str[strlen(str)-1] = '\0';
    new = 0;
  }*/
  split_text = strtok (str," ,.-");
  if(strcmp(split_text,"GET")==0){
    /**Extracting file name **/
    split_text = strtok (NULL," ,-");
  fd_read=open(split_text,O_RDONLY);
  if(fd_read>=0){
    read(fd_read,&resp,200);
    close(fd_read);
    strcpy(response,resp);
    return 0;
  }
  else{
    return -2;
  }
  }
  else{
    return -1;
  }
}


int main(){
	int server_fd, client_fd, n, len_c;
	struct sockaddr_in server,client;
	char buf[200],buff_resp[200];
  int ret_value;
  int opt = 1;
  int n_buff;
  int addrlen = sizeof(client);

	server_fd = socket(AF_INET,SOCK_STREAM,0);
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
    listen(server_fd, 5);
    len_c = sizeof(client);
    n_buff = sizeof(buff_resp);
    
    while(1){
      client_fd = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&addrlen);
      new = 1;
      if(fork()==0){
    	while((n=read(client_fd, buf, sizeof(buf)))>0){
    		ret_value = read_contents(buf,buff_resp);
      if(ret_value==0)
        send(client_fd, buff_resp, n_buff, 0);     
      else if(ret_value==-1){
        strcpy(buff_resp,"Invalid Operation");
        send(client_fd, buff_resp, n_buff, 0);
      }
      else if(ret_value==-2){
        strcpy(buff_resp,"Data Not Found");
        send(client_fd, buff_resp, n_buff, 0);
      }
      }
    }
  }
}
