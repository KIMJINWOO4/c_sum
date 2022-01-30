#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLINE 5

void print(int *tmp){
	int i;
	
	printf("Recv data : ");
	for(i = 0; i<MAXLINE; i++){
		printf("%d ",tmp[i]);
	}

	printf("\n");
}

int check(int *tmp){
	int result = 0;
	int i;
	
	for(i = 0; i<MAXLINE; i++){
		if(result < tmp[i]){
			result = tmp[i];
		}
	}
	
	return result;
}

int main(){
	int fd[2];
	int result;
	int response[MAXLINE];

	unlink("ServerPipe");
	mkfifo("ServerPipe",0660);

	fd[0] = open("ServerPipe",O_RDONLY);
	fd[1] = open("ClientPipe",O_WRONLY);

	printf("==== Server ====\n");
	while(read(fd[0],(int*)response,sizeof(response))){
		print(response);
		result = check(response);
		write(fd[1],&result,sizeof(result));
	}

	exit(0);
}
