#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>  
#include <stdlib.h>         
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "string.h"

#define SERVER_PATH "/home/alan/Desktop/RTOS/assignment_1/trial/six_queues"
#define PROJECT_ID 10

struct message_text {
    int qid;
    char buf [200];
};

struct message {
    long message_type;
    struct message_text message_text;
};

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

int main()
{
	/*** Message Queue maintained by server ***/
	int server_key;
	int server_msqid,client_msqid; 
	struct message request_message;

	server_key = ftok(SERVER_PATH,PROJECT_ID);
	server_msqid = msgget(server_key,IPC_CREAT | 0666);

	request_message.message_type = 1;

	while(1){
		/*********** Servicing requests from clients ***********/
		if(msgrcv(server_msqid, (void *) &request_message, sizeof(struct message_text), 0,
                      MSG_NOERROR | IPC_NOWAIT) >= 0){
			client_msqid = request_message.message_text.qid;
			convert_string(request_message.message_text.buf);
			msgsnd(client_msqid, (void *) &request_message,sizeof (struct message_text),IPC_NOWAIT);			
		}
	}
}
