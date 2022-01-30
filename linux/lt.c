#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 100

/* �������� ���� �ڽĿ��� ����Ǵ� ��ɾ� ����� �޾� ����Ʈ�Ѵ�. */
int main(int argc, char* argv[]) 
{
    int n, pid, fd[2];
    char line[MAXLINE];
	char op[MAXLINE];
	char *s;

	if(argc != 2){
		printf("usage : ./logintest argv[1] \n");
		exit(0);
	}

	sprintf(op,"who | grep -w %s || echo NOT_LOGIN",argv[1]);

    pipe(fd);  
	pid = fork();
    
	if (pid == 0) {
        close(fd[0]);
        dup2(fd[1],1);         
        close(fd[1]);
		while(1){
			system(op);
			sleep(5);
		}
    } else {                  
        close(fd[1]);
        while ((n = read(fd[0], line, MAXLINE)) > 0){ 
			s=strstr(line,"NOT_LOGIN");
			if(s==NULL){
				printf("Login Success!\n");
				break;
			}
            write(1, line, n); 
		}
    }
    exit(0); 
}

