#include <stdio.h>
#include "string.h"
#include <stdlib.h>


int coroutine(char *str){
	static int state = 0;
	static char prefix[100];
	char * split_text;
	char  temp_text[100];
	strcpy(temp_text,str);
	switch (state){
	case 0:
		state = 1;
		if(strcmp(temp_text,"Dear")==0){
			strcpy(prefix,temp_text);
			return 0;
			}
		return 1;
	case 1:
		split_text = strtok (temp_text," ,.-");
		if(strcmp(split_text,prefix)==0){
			split_text = strtok (NULL," ,-");
			printf("%s\n",split_text );
		}
	}
}

int main(){
	int i=0;
	i = coroutine("Dear");
	i = coroutine("Dear Alan");
	i = coroutine("Dear Allah");
	i = coroutine("Deeer Alan");
	//coroutine("Dear Alan");
}
