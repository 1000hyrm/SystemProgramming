#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 256
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[]){
	int i;
	char buf[MAX];
	int size=0;
	int s; //=char s;
	char line[256];
	char *path[MAX];
	char allpath[512];
	char option[MAX];
	int fd;
	
	for(i=0; i<argc; i++){
		printf("argv[%d]=[%s]\n", i, argv[i]);
		path[i] = argv[i];
		printf("path[%d]=[%s]\n", i, path[i]);
	}
	printf("i=%d\n", i);
	//strcat(allpath, "\"");
	strcpy(allpath, argv[1]);
	//strcat(allpath, "\"");
	printf("%s\n", allpath);
	
	for(int k=2; k<i-1; k++){
		strcpy(option, argv[k]);
	}
	printf("%s\n", option);
	
	printf("i=%d\n", i);
	//execl(allpath, "cmd", option, (char *)0);
	
	close(1);
	if(open(argv[i-1], O_WRONLY | O_CREAT | O_TRUNC, 0655)==-1){
		perror(argv[i-1]);
		exit(1);
	}
	close(2);
	if(dup(1) == -1){
		perror(argv[0]);
		exit(2);
	}
	printf("here\n");
	
	if(i < 4){
		execl(allpath, "cmd", (char *)0);
	}
	else
		execl(allpath, "cmd", option, (char *)0);
	//close(fd);
	exit(1);
}
