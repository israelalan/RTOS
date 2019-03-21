#include <sys/types.h>         
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h> 
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define SERVER_PATH "/home/alan/Desktop/RTOS/assignment_2/trial/DB_engine"

int main(){
	int client_fd, len_c, n, check;
	struct sockaddr_in server;
    char buf[200];
    int con_check;
    clock_t t;
    struct timeval start, stop;
    time_t rawtime;
  	struct tm * timeinfo;
  	char times[50];
  	char *split_text;

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(8000);
	memset(server.sin_zero, '\0', sizeof server.sin_zero);

	con_check = connect(client_fd,(struct sockaddr *)&server, sizeof(server));

	char ch_arr[5][20] = {
                             "GET sensor1.txt",
                             "GET sensor2.txt",
                             "GET sensor3.txt",
                             "GET sensor4.txt",
                             "GET sensor5.txt"
                         };
    int i = 0;
    int j = 0;
    char temp_text[20];
    int fd_read;
    //fd_read=open("data.csv",O_RDWR);
    char  time_stamp[8];

    FILE *fr;
    fr = fopen("data.csv", "w");
    int k = 0;
    while(k<10){
    	k = k+1;
    	j = 1;
		sleep(2);
		time (&rawtime);
	    timeinfo = localtime (&rawtime);
	    strcpy(times,asctime(timeinfo));
	    split_text = strtok (times," ,.-");
	    split_text = strtok (NULL," ,.-");
	    split_text = strtok (NULL," ,.-");
	    split_text = strtok (NULL," ,.-");

		fprintf(fr, "%s,", split_text);	    
		
		
		while((j%6)!=0){
		i = i%5;
		printf("Enter while\n");

		strcpy(buf,ch_arr[i]);
		printf("%s\n",buf );
		if(send(client_fd, buf,strlen(buf), 0)>0){
			n = recv(client_fd, buf, 200, 0);
			printf("%s\n", buf);
			if(i!=4)
				fprintf(fr, "%s,", buf);
			else
				fprintf(fr, "%s\n", buf);
			j = j+1;
		}
		i = i+1;
		}
	}
}
