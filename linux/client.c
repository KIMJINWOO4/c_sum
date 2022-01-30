#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define MAXLINE 5

void print(int *tmp){
	int i;
	
	printf("Create Numbers: ");
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
	int i;
	int message[MAXLINE], response;

	srand(time(NULL));

	do{
		fd[0] = open("ServerPipe",O_WRONLY);
		if (fd[0] == -1){
			sleep(1);
		}
	}while(fd[0] == -1);

	do{
		fd[1] = open("ClientPipe",O_RDONLY);
		if (fd[1] == -1){
			sleep(1);
		}
	}while(fd[1] == -1);
		
	for(i = 0; i < MAXLINE; i++){
		message[i] = rand()%100;
	}

	print(message);

	write(fd[0],message,sizeof(message));

	read(fd[1],(int*)&response,sizeof(response));
	
	printf("Recv MAX : %d\n",response);
	
	if(response == check(message)){
		printf("SUCCESS\n");
	}else{
		printf("FAIL\n");
	}
	exit(0);
}
