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
#include <time.h>

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

int main()
{
	clock_t t;
	int server_key,client_key;
	int server_msqid, myqid;
	struct message request_message,response_message;

	/*** Server Message Queue Credentials ***/
	server_key = ftok(SERVER_PATH,PROJECT_ID);
	server_msqid = msgget(server_key,0);

	request_message.message_type = 1;
	response_message.message_type = 1;

	/*** Client Message Queue Credentials ***/
	client_key = 1111;
	myqid = msgget(client_key, 0660 | IPC_CREAT);
	request_message.message_text.qid = myqid;

	while(1){
		scanf(" %[^\n]",request_message.message_text.buf);
		if (msgsnd(server_msqid, (void *) &request_message, sizeof(struct message_text),
                       IPC_NOWAIT) >= 0){
			t = clock();
			msgrcv(myqid, (void *) &response_message, sizeof(struct message_text), 0,MSG_NOERROR);
			t = clock()-t;
			printf("Time taken for servicing request: %f\n",((double)t)/CLOCKS_PER_SEC );
			printf("%s\n",response_message.message_text.buf );
		}
	}
}
