#include <sys/types.h>         
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define SERVER_PATH "/home/alan/Desktop/RTOS/assignment_2/trial/single_client"

int main(){
	int client_fd, len_c, n, check;
	struct sockaddr_in server;
    char buf[200];
    int con_check;
    clock_t t;
    struct timeval start, stop;

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(8000);
	memset(server.sin_zero, '\0', sizeof server.sin_zero);

	con_check = connect(client_fd,(struct sockaddr *)&server, sizeof(server));

    while(1){
    	
		scanf(" %[^\n]",buf);
		if(send(client_fd, buf,strlen(buf), 0)>0){
			gettimeofday(&start, NULL);
			n = recv(client_fd, buf, 200, 0);
			gettimeofday(&stop, NULL);
			if(n<=0){
				printf("Nothing received\n");
			}
			else{
				printf("%s\n",buf );
			}
			printf("%lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
		}
	}
}
