#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX 50
char text[80];

void read2line(char *input){
	while(1){
		read(0, input, 1);
		if(*input=='\n')
			break;
		else
			input++;
	}
}

int main(int argc, char *argv[]){
	int fd[2], pid=0, size=0, status=0;
	char buf[MAX];
	memset(buf, 0x00, MAX);
	
	if(pipe(fd)==-1){
		perror(argv[0]);
		exit(1);
	}
	
	if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		printf("%s", argv[1]);
		fflush(stdout);
		exit(3);
	}
	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		
		size = read(0, buf, MAX);
		execlp(argv[1], buf, (char *)NULL);
		perror("execlp() :");
		exit(0);
	}

	/*if(fork()==0){
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		
		printf("displayed %s\n", argv[1]);
		fflush(stdout);
		
		//size = read(0, buf, MAX);
		//execlp(argv[1], buf, (char *)NULL);
		
		//execl(argv[1], "wow", (char *)0);
		//perror("execl () ");
		exit(3);
	}
	
	if(fork()==0){
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		//read2line(text);
		//printf("heading %s\n", text);
		execl(argv[1], "wow", (char *)0);
		fflush(stdout);
		exit(0);
	}*/
	
	close(fd[0]);
	close(fd[1]);
	while(wait(&status) != -1)
		;
	exit(0);
}
	
