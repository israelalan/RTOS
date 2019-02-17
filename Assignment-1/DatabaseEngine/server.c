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

#define SERVER_PATH "/home/alan/Desktop/RTOS/assignment_1/trial/file_reading/server_dir"
#define PROJECT_ID 10

struct message_text {
    int qid;
    char buf [200];
};

struct message {
    long message_type;
    struct message_text message_text;
};

int read_contents(char str[], char response[]) {
  
  char resp[200];
  char * split_text;
  int fd_read;
  /** Extracting First Word **/
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
	struct message request_message,response_message;
	int ret_value;

	server_key = ftok(SERVER_PATH,PROJECT_ID);
	server_msqid = msgget(server_key,IPC_CREAT | 0666);

	request_message.message_type = 1;
	response_message.message_type = 1;

	while(1){
		/*********** Servicing requests from clients ***********/
		if(msgrcv(server_msqid, (void *) &request_message, sizeof(struct message_text), 0,
                      MSG_NOERROR | IPC_NOWAIT) >= 0){
			client_msqid = request_message.message_text.qid;
			//convert_string(request_message.message_text.buf);
			ret_value = read_contents(request_message.message_text.buf,response_message.message_text.buf);
			if(ret_value==0)
				msgsnd(client_msqid, (void *) &response_message,sizeof (struct message_text),IPC_NOWAIT);			
			else if(ret_value==-1){
				//request_message.message_text.buf = "Invalid Operation";
				strcpy(response_message.message_text.buf,"Invalid Operation");
				msgsnd(client_msqid, (void *) &response_message,sizeof (struct message_text),IPC_NOWAIT);			
			}
			else if(ret_value==-2){
				//request_message.message_text.buf = "Data Not Found";
				strcpy(response_message.message_text.buf,"Data Not Found");
				msgsnd(client_msqid, (void *) &response_message,sizeof (struct message_text),IPC_NOWAIT);			
			}
		}
	}
}
