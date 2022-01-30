#include <sys/types.h> 
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*);

/* 디렉토리 내용을 자세히 리스트한다. */
int main(int argc, char **argv) 
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int filenum = 0;
    char names[BUFSIZ+1][255];
    if (argc == 1) 
        dir = ".";
    else dir = argv[1];

    if ((dp = opendir(dir)) == NULL)  // 디렉토리 열기 
        perror(dir);

    while ((d = readdir(dp)) != NULL) { // 디렉토리 내의 각 파일에 대해 
        strcpy(names[filenum],d->d_name);
        filenum++;
    }
    for(int step = 0; step < filenum - 1;step++){
        for(int i = 0; i < filenum - 1 - step;i++){
            if(strcmp(names[i],names[i+1])>0){
                char temp[255];
                strcpy(temp,names[i]);
                strcpy(names[i],names[i+1]);
                strcpy(names[i+1],temp);
            }
        }
    }
    for(int i=0;i<filenum;i++){
        if(names[i][0] != '.'){
            sprintf(path, "%s/%s", dir, names[i]); // 파일 경로명 만들기 
        if (lstat(path, &st) < 0)   // 파일 상태 정보 가져오기  
            perror(path);
        printStat(path, names[i], &st);  // 상태 정보 출력
        }
        
    }
    closedir(dp);
    exit(0);
    }


/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st) {
    if(!S_ISDIR(st->st_mode)){
        printf("%-18s", file);
        printf("%-13s", perm(st->st_mode));
        printf("%9ld ", st->st_size);
        printf("%-10s", getpwuid(st->st_uid)->pw_name);
        //printf("%3ld ", st->st_nlink);
        //printf("%-7ld ", st->st_blocks);
        printf("%.24s\n", ctime(&st->st_mtime));
    }
}

/* 파일 타입을 리턴 */
char type(mode_t mode) {

    if (S_ISREG(mode)) 
        return('-');
    if (S_ISDIR(mode)) 
        return('d');
    if (S_ISCHR(mode)) 
        return('c');
    if (S_ISBLK(mode)) 
        return('b');
    if (S_ISLNK(mode)) 
        return('l');
    if (S_ISFIFO(mode)) 
        return('p');
    if (S_ISSOCK(mode)) 
        return('s');
}

/* 파일 허가권을 리턴 */
char* perm(mode_t mode) {
    int i;
    static char perms[10]; 

    strcpy(perms, "---------");

    for (i=0; i < 3; i++) {
        if (mode & (S_IREAD >> i*3)) 
            perms[i*3] = 'r';
        if (mode & (S_IWRITE >> i*3)) 
            perms[i*3+1] = 'w';
        if (mode & (S_IEXEC >> i*3)) 
            perms[i*3+2] = 'x';
    }
   return(perms);
}
